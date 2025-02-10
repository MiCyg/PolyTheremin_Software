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

static inline uint32_t *gpio_buffer()
{
	return buffer[(buffer_actual_idx-1) & 0x01];
}




void setup_pwm_clock() {

	logg(AQUISITION, "Set aquisition clock out to gpio %d\n", GPIO_AQUISITION_CLOCK_OUT);
    gpio_set_function(GPIO_AQUISITION_CLOCK_OUT, GPIO_FUNC_PWM);

    aquisition_slice_num = pwm_gpio_to_slice_num(GPIO_AQUISITION_CLOCK_OUT);
	// uint pwm_channel = pwm_gpio_to_channel(GPIO_AQUISITION_CLOCK_OUT);

    uint32_t sys_clk_hz = clock_get_hz(clk_sys);
    uint32_t wrap_value = (uint32_t)((float)sys_clk_hz / (float)AQUISITION_FS);
	float real_sample_rate = (float)clock_get_hz(clk_sys)/(float)wrap_value;
	logg(AQUISITION, "Sample rates: set: %.2f[Hz], real: %.2f[Hz]\n", (double)AQUISITION_FS, (double)real_sample_rate);


    pwm_set_wrap(aquisition_slice_num, wrap_value);
    pwm_set_clkdiv(aquisition_slice_num, 1.0f);
	// pwm_set_gpio_level(GPIO_AQUISITION_CLOCK_OUT, wrap_value>>1);
    pwm_set_enabled(aquisition_slice_num, true);


	pwm_set_irq_enabled(aquisition_slice_num, true);
	irq_add_shared_handler(PWM_IRQ_WRAP, get_gpios_irq, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
	irq_set_enabled(PWM_IRQ_WRAP, true);


}


arm_rfft_fast_instance_f32 fft;
void analyse_task()
{
	setup_pwm_clock();
	arm_status _status = arm_rfft_fast_init_f32(&fft, AQUISITION_BUFFER_SIZE);
	panic_check(_status != ARM_MATH_SUCCESS, "Cannot claim fft function.");

	float32_t signal_in[AQUISITION_BUFFER_SIZE];
	float32_t signal_fft_cmplx[AQUISITION_BUFFER_SIZE];
	float32_t signal_fft_mag[AQUISITION_BUFFER_SIZE];
	float32_t max_bin;
	uint32_t max_bin_index;


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
					signal_in[i] = (gpio_buffer()[i] & (1<<GPIO_AQUISITION_INPUT_1) ) >> GPIO_AQUISITION_INPUT_1;
				}
				arm_copy_f32(signal_in, signal_fft_cmplx, AQUISITION_BUFFER_SIZE);
				arm_rfft_fast_f32(&fft, signal_fft_cmplx, signal_fft_mag, 0);
				arm_cmplx_mag_f32(signal_fft_mag, signal_fft_mag, AQUISITION_BUFFER_SIZE>>1);
				arm_max_f32(signal_fft_mag+1, (AQUISITION_BUFFER_SIZE>>1)-1, &max_bin, &max_bin_index);
				gpio_toggle(GPIO_TEST);

				// logg(AQUISITION, "max_bin: %.0f on index %.0f, f: %fHz\n", (double)max_bin, (double)max_bin_index, (double)max_bin_index*AQUISITION_FS/AQUISITION_BUFFER_SIZE); //! hardfa ult

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
