#include "aquisition.h"
#include "hardware/pwm.h"
#include "cmsis.h"


// create folding buffer
#define BUFFER_FOLD_NUM 2 //? I think this can't be a settable parameter
static uint32_t buffer_actual_idx = 0;
static uint32_t buffer[BUFFER_FOLD_NUM][AQUISITION_BUFFER_SIZE];

static uint aquisition_slice_num;
static SemaphoreHandle_t wrap_sempahore;

static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
void get_gpios_irq()
{
	// TODO change to dma
	static uint32_t tmp_gpio_all;
	static uint32_t idx = 0;

	pwm_clear_irq(aquisition_slice_num);
	tmp_gpio_all = gpio_get_all();
	buffer[buffer_actual_idx][idx] = tmp_gpio_all & ( (1<<GPIO_AQUISITION_INPUT_0) |
																 (1<<GPIO_AQUISITION_INPUT_1) |
																 (1<<GPIO_AQUISITION_INPUT_2) |
																 (1<<GPIO_AQUISITION_INPUT_3) );
	
	idx++;
	idx &= AQUISITION_BUFFER_SIZE_MASK;

	if(!idx) 
	{
		buffer_actual_idx++;
		buffer_actual_idx &= 0x01;
		// pwm_set_enabled(aquisition_slice_num, false);
		xSemaphoreGiveFromISR(wrap_sempahore, &xHigherPriorityTaskWoken);
	}

}

static inline uint32_t *buffer_to_analyse()
{
	return buffer[(buffer_actual_idx-1) & 0x01];
}




void setup_pwm_clock() {

	logg(AQUISITION, "Set aquisition clock out to gpio %d\n", GPIO_AQUISITION_CLOCK_OUT);
    gpio_set_function(GPIO_AQUISITION_CLOCK_OUT, GPIO_FUNC_PWM);

    aquisition_slice_num = pwm_gpio_to_slice_num(GPIO_AQUISITION_CLOCK_OUT);
	uint pwm_channel = pwm_gpio_to_channel(GPIO_AQUISITION_CLOCK_OUT);

    uint32_t sys_clk_hz = clock_get_hz(clk_sys);
    uint32_t wrap_value = (uint32_t)((float)sys_clk_hz / (float)AQUISITION_FS);
	float real_sample_rate = (float)clock_get_hz(clk_sys)/(float)wrap_value;
	logg(AQUISITION, "Sample rates: set: %.2f[Hz], real: %.2f[Hz]\n", (float)AQUISITION_FS, real_sample_rate);


    pwm_set_wrap(aquisition_slice_num, wrap_value);
    pwm_set_clkdiv(aquisition_slice_num, 1.0f);
	// pwm_set_gpio_level(GPIO_AQUISITION_CLOCK_OUT, wrap_value>>1);
    pwm_set_enabled(aquisition_slice_num, true);


	pwm_set_irq_enabled(aquisition_slice_num, true);
	irq_add_shared_handler(PWM_IRQ_WRAP, get_gpios_irq, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
	irq_set_enabled(PWM_IRQ_WRAP, true);


}


static float32_t analyse_buffer[4][AQUISITION_BUFFER_SIZE];
static float32_t means[4];
void analyse_task()
{
	setup_pwm_clock();
	wrap_sempahore = xSemaphoreCreateBinary();
	int i =  0;
	while(1)
	{
		if(xSemaphoreTake( wrap_sempahore, 100 ) == pdTRUE)
		{

			if(i%10 == 0)
			{
				gpio_toggle(GPIO_TEST);
				for (uint16_t i = 0; i < AQUISITION_BUFFER_SIZE; i++)		
				{
					analyse_buffer[0][i] = (buffer_to_analyse()[i] & (1<<GPIO_AQUISITION_INPUT_0) ) >> GPIO_AQUISITION_INPUT_0;
					analyse_buffer[1][i] = (buffer_to_analyse()[i] & (1<<GPIO_AQUISITION_INPUT_1) ) >> GPIO_AQUISITION_INPUT_1;
					analyse_buffer[2][i] = (buffer_to_analyse()[i] & (1<<GPIO_AQUISITION_INPUT_2) ) >> GPIO_AQUISITION_INPUT_2;
					analyse_buffer[3][i] = (buffer_to_analyse()[i] & (1<<GPIO_AQUISITION_INPUT_3) ) >> GPIO_AQUISITION_INPUT_3;
				}


			
				for (uint32_t i = 0; i < CHAN_NUM; i++)
				{
					arm_mean_f32(analyse_buffer[i], AQUISITION_BUFFER_SIZE, &means[i]);	
				}
			


				// logg(AQUISITION, "avgs: %.2f, %.2f, %.2f, %.2f\n", means[0], means[1], means[2], means[3]);
				gpio_toggle(GPIO_TEST);
			}


			i++;
		}
	}

	vTaskDelete(NULL);
}


int aquisition_init()
{
	logg(AQUISITION, "Init\n");

	xTaskCreate(analyse_task, "analyse", 4*1024, NULL, 1, NULL);
	
	return 0;
}

void aquisition_deinit()
{
	logg(AQUISITION, "Deinit\n");
	// TODO
}
