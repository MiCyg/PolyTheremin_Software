
#include "freq_meas.h"

// ============== STATIC FUNCTIONS ==============

freq_meas_channel_t freq_det_vars[CHANNEL_NB] = {
	{.gpio=GPIO_DET_MEAS1},
	{.gpio=GPIO_DET_MEAS2},
	{.gpio=GPIO_DET_MEAS3},
	{.gpio=GPIO_DET_MEAS4}
};

int freq_meas_timer_channel;
static void (*dma_wrap_cb)() = NULL;

static inline void common_gpio_cb(uint gpio, uint32_t event_mask)
{
	for (freq_meas_channel_num_e chan = 0; chan < CHANNEL_NB; chan++)
	{
		if (gpio == freq_det_vars[chan].gpio)
		{
			if(freq_det_vars[chan].gpio == GPIO_DET_MEAS1){
				gpio_put(GPIO_DET_MEAS_TEST, 1);
			}
			freq_det_vars[chan].det_freq_count = pwm_get_counter(freq_det_vars[chan].pwm_slice);
			pwm_set_counter(freq_det_vars[chan].pwm_slice, 0);
			pwm_set_enabled(freq_det_vars[chan].pwm_slice, true);
			if(freq_det_vars[chan].gpio == GPIO_DET_MEAS1){
				gpio_put(GPIO_DET_MEAS_TEST, 0);
				// logg(FREQ_DET, "det: %d\n", freq_det_vars[chan].dma_buff[0]);
			}
			break;
		}
	}
	
}

void freq_chans_init(){

	for (freq_meas_channel_num_e chan = 0; chan < CHANNEL_NB; chan++)
	{

		freq_det_vars[chan].pwm_slice = pwm_gpio_to_slice_num(freq_det_vars[chan].gpio);

		pwm_set_wrap(freq_det_vars[chan].pwm_slice, 0xffff);
		pwm_set_counter(freq_det_vars[chan].pwm_slice, 0);
		pwm_set_enabled(freq_det_vars[chan].pwm_slice, true);

		gpio_set_irq_enabled_with_callback(freq_det_vars[chan].gpio, GPIO_IRQ_EDGE_FALL, true, common_gpio_cb);
		freq_det_vars[chan].dma_chan = dma_claim_unused_channel(false);
		if(freq_det_vars[chan].dma_chan == -1){
			logg(FREQ_DET, "Cannot claim dma hardware. Frequency detector channel %d.\n", chan);
		}

		freq_det_vars[chan].dma_config = dma_channel_get_default_config(freq_det_vars[chan].dma_chan);
		channel_config_set_transfer_data_size(&freq_det_vars[chan].dma_config, DMA_SIZE_16);
		channel_config_set_read_increment(&freq_det_vars[chan].dma_config, false);
		channel_config_set_write_increment(&freq_det_vars[chan].dma_config, true);
		channel_config_set_dreq(&freq_det_vars[chan].dma_config, dma_get_timer_dreq(freq_meas_timer_channel));

		dma_channel_set_irq0_enabled(freq_det_vars[chan].dma_chan, true);

		dma_channel_configure(
			freq_det_vars[chan].dma_chan, 
			&freq_det_vars[chan].dma_config, 
			freq_det_vars[chan].dma_buff, 
			&freq_det_vars[chan].det_freq_count, 
			FREQ_DET_DMA_BUFFER_NUM, 
			false
		);
		

	}

}

void freq_chans_deinit(){
	for (freq_meas_channel_num_e chan = 0; chan < CHANNEL_NB; chan++)
	{
		gpio_init(freq_det_vars[chan].gpio);
		gpio_set_dir(freq_det_vars[chan].gpio, false);

		dma_channel_set_irq0_enabled(freq_det_vars[chan].dma_chan, false);
		dma_channel_unclaim(freq_det_vars[chan].dma_chan);
		gpio_set_irq_enabled(freq_det_vars[chan].gpio, GPIO_IRQ_EDGE_FALL, false);
		pwm_set_enabled(freq_det_vars[chan].pwm_slice, false);
	}
}

int timer_dma_init(){

	// (X/Y)*sys_clk, where X is the first 16 bytes and Y is the second
	freq_meas_timer_channel = dma_claim_unused_timer(false);
	
	if(freq_meas_timer_channel == -1){
		loge(FREQ_DET, "Cannot claim timer for DDS.\n");	
		return -1;
	}
	logg(FREQ_DET, "Calm dma timer: %d\n", freq_meas_timer_channel);
	dma_timer_set_fraction(freq_meas_timer_channel, FREQ_DET_TIMER_X_FRACTION, FREQ_DET_TIMER_Y_FRACTION);
	return 0;
}

int timer_dma_deinit(){
	// dma_timer_unclaim(freq_meas_timer_channel);
	return 0 ;
}

void channels_dma_trigger(){

	uint32_t val = 0;
	for (freq_meas_channel_num_e chan = 0; chan < CHANNEL_NB; chan++)
	{
		val |= (1<<freq_det_vars[chan].dma_chan);
	}
	dma_hw->multi_channel_trigger = val;

}

volatile static uint8_t _dma_interrupts = 0x00;
void dma_wrap_handler(){


	for (uint8_t chan = 0; chan < CHANNEL_NB; chan++)
	{
		if(dma_hw->intr & (1u<<freq_det_vars[chan].dma_chan)){
			dma_hw->ints0 = 1u << freq_det_vars[chan].dma_chan;
			_dma_interrupts |= (1<<chan);
		}
	}

	// synchronised data from all dma channels
	if( (_dma_interrupts&0b00001111) == 0b00001111){
		_dma_interrupts = 0;

		gpio_put(GPIO_DET_MEAS_TEST2, !gpio_get(GPIO_DET_MEAS_TEST2));

		if(dma_wrap_cb) dma_wrap_cb();


		for (freq_meas_channel_num_e chan = 0; chan < CHANNEL_NB; chan++)
		{
			dma_channel_configure(
				freq_det_vars[chan].dma_chan, 
				&freq_det_vars[chan].dma_config, 
				freq_det_vars[chan].dma_buff, 
				&freq_det_vars[chan].det_freq_count, 
				FREQ_DET_DMA_BUFFER_NUM, 
				false
			);

			dma_channel_set_irq0_enabled(freq_det_vars[chan].dma_chan, true);

		}

		channels_dma_trigger();
	}
}


// ============== EXTERNAL FUNCTIONS ==============
void freq_meas_init(){
	gpio_init(GPIO_DET_MEAS_TEST);
	gpio_set_dir(GPIO_DET_MEAS_TEST, true);
	gpio_put(GPIO_DET_MEAS_TEST, 0);
	
	gpio_init(GPIO_DET_MEAS_TEST2);
	gpio_set_dir(GPIO_DET_MEAS_TEST2, true);
	gpio_put(GPIO_DET_MEAS_TEST2, 1);

	timer_dma_init();

	freq_chans_init();

	irq_add_shared_handler(DMA_IRQ_0, dma_wrap_handler, PICO_HIGHEST_IRQ_PRIORITY-1);
	irq_set_enabled(DMA_IRQ_0, true);

	channels_dma_trigger();

}

void freq_meas_deinit(){
	freq_chans_deinit();
	irq_set_enabled(DMA_IRQ_0, false);
	timer_dma_deinit();
	freq_meas_set_wrap_cb(NULL);
}

uint16_t* freq_meas_dma_buffer(freq_meas_channel_num_e chan){
	return freq_det_vars[chan].dma_buff;
}

void freq_meas_set_wrap_cb(void (*function)()){
	dma_wrap_cb = function;
}

