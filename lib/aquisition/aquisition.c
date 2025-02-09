#include "aquisition.h"
#include "hardware/pwm.h"


// use folding buffer
uint8_t buffer_actual_idx = 0;
uint32_t buffer[2][AQUISITION_BUFFER_SIZE];

static uint aquisition_slice_num;
SemaphoreHandle_t wrap_sempahore;

BaseType_t xHigherPriorityTaskWoken = pdFALSE;
uint32_t tmp_gpio_all;
void get_gpios_irq()
{
	// TODO change to dma
	gpio_toggle(GPIO_TEST);
	static uint32_t aquisition_idx = 0;
	pwm_clear_irq(aquisition_slice_num);
	tmp_gpio_all = gpio_get_all();
	buffer[buffer_actual_idx][aquisition_idx] = tmp_gpio_all & ((1<<GPIO_AQUISITION_INPUT_0) |
																(1<<GPIO_AQUISITION_INPUT_1) |
																(1<<GPIO_AQUISITION_INPUT_2) |
																(1<<GPIO_AQUISITION_INPUT_3));
	
	aquisition_idx++;
	aquisition_idx &= (AQUISITION_BUFFER_SIZE - 1);
	

	if(!aquisition_idx) 
	{
		buffer_actual_idx++;
		buffer_actual_idx &=  0x01;
		// pwm_set_enabled(aquisition_slice_num, false);
		xSemaphoreGiveFromISR(wrap_sempahore, &xHigherPriorityTaskWoken);
	}
	gpio_toggle(GPIO_TEST);

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


/* arch

	void setup_pio()
	{
		int err;

		uint offset = pio_add_program(aquisition_pio, &aquisition_program);
		panic_check(offset == -1, "Cannot add program to PIO");

		uint sm = pio_claim_unused_sm(aquisition_pio, false);
		aquisition_sm = sm;
		panic_check(sm == -1, "Cannot claim unused state machine");

		logg(AQUISITION, "Claim sm: %d, offset: %d\n", sm, offset);


		pio_sm_config config = aquisition_program_get_default_config(offset);

		// Set the IN base pin to the provided `pin` parameter. This is the data
		// pin, and the next-numbered GPIO is used as the clock pin.
		sm_config_set_in_pins(&config, GPIO_AQUISITION_CLOCK_OUT);

		// Set the pin directions to input at the PIO
		err = pio_sm_set_consecutive_pindirs(aquisition_pio, sm, AQUISITION_GPIO_BASE, AQUISITION_GPIO_COUNT, false);
		panic_check(err != 0, "err1");
		// Connect these GPIOs to this PIO block

		for (uint16_t idx = 0; idx < AQUISITION_GPIO_COUNT; idx++)
		{
			pio_gpio_init(aquisition_pio, AQUISITION_GPIO_BASE+idx);
		}
		

		// Shifting to left matches the customary MSB-first ordering of SPI.
		sm_config_set_in_shift(
			&config,
			false, // Shift-to-right = false (i.e. shift to left)
			true,  // Autopush enabled
			1      // Autopush threshold = 8
		);

		// We only receive, so disable the TX FIFO to make the RX FIFO deeper.
		sm_config_set_fifo_join(&config, PIO_FIFO_JOIN_RX);

		// Load our configuration, and start the program from the beginning
		err = pio_sm_init(aquisition_pio, sm, offset, &config);
		panic_check(err != 0, "err2");
		pio_sm_set_enabled(aquisition_pio, sm, true);


	}

	void dma_irq()
	{
		dma_hw->ints0 = 1u << dma_channel1;
		gpio_toggle(GPIO_TEST);
		dma_channel_configure(
			dma_channel1,
			&dma_config1,
			&aquisition_buffer,                  // Write to one buffer
			&aquisition_pio->rxf[aquisition_sm], // Read data from PIO FIFO
			AQUISITION_BUFFER_SIZE, 
			true                    
		);

	}

	void setup_dma(bool oneshoot)
	{
			
		dma_channel1 = dma_claim_unused_channel(false);
		panic_check(dma_channel1 == -1, "Cannot claim dma1");

		// set dma1
		dma_config1 = dma_channel_get_default_config(dma_channel1);
		channel_config_set_transfer_data_size(&dma_config1, DMA_SIZE_8);
		channel_config_set_read_increment(&dma_config1, false);
		channel_config_set_write_increment(&dma_config1, true);

		channel_config_set_dreq(&dma_config1, pio_get_dreq(aquisition_pio, aquisition_sm, false));

		if(!oneshoot)
		{
			// Interrupt on end
			dma_channel_set_irq0_enabled(dma_channel1, true);
			irq_set_exclusive_handler(DMA_IRQ_0, dma_irq);
			irq_set_enabled(DMA_IRQ_0, true);
		}

		// channel_config_set_chain_to(&dma_config1, dma_channel2);

		dma_channel_configure(
			dma_channel1,
			&dma_config1,
			&aquisition_buffer,                  // Write to one buffer
			&aquisition_pio->rxf[aquisition_sm], // Read data from PIO FIFO
			AQUISITION_BUFFER_SIZE, 
			true                    
		);

	}
// */


void aquisition_task()
{
	setup_pwm_clock();
	wrap_sempahore = xSemaphoreCreateBinary();
	int i =  0;
	while(1)
	{
		if(xSemaphoreTake( wrap_sempahore, 100 ) == pdTRUE)
		{

			if(i < 4)
			{

				printf("\n");
				for (uint32_t idx = 0; idx < AQUISITION_BUFFER_SIZE; idx++)
				{
					// if(idx % 32 == 0) printf("\n");
					printf("%1d ", (buffer[!buffer_actual_idx][idx] & (1 << GPIO_AQUISITION_INPUT_3)) >> GPIO_AQUISITION_INPUT_3);
				}
				printf("\n");
				i++;
			}
		}
	}

	vTaskDelete(NULL);
}


int aquisition_init()
{
	logg(AQUISITION, "Init\n");

	xTaskCreate(aquisition_task, "aquisition", 4*1024, NULL, 1, NULL);
	
	return 0;
}

void aquisition_deinit()
{
	logg(AQUISITION, "Deinit\n");
	// TODO
}
