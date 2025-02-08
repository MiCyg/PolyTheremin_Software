#include "dds.h"

static dds_t oscillators[DAC_CHAN_NB];
static uint16_t dds_samples_buff[DDS_BUFF_SIZE];

int dds_timer_channel;

static int dma_data_chan;
#define DMA_CHANNEL_SETUP_SIZE 16
static uint32_t dma_channel_hw_data[DMA_CHANNEL_SETUP_SIZE];

static int dma_ctr_chan;

// for interrupt
volatile bool oveload = false;
static uint16_t sample_idx;
static uint16_t osc_idx;

fix32_t dds_fs_fix32 = int2fix32(DDS_FS);
// fix32_t tousand = int2fix32(1000);

TaskHandle_t dds_task_handle;


void osc_init(dds_t *osc){
	osc->one_sample		= 0;
	osc->phase_accum	= float2fix32(0.0);
	osc->phase_incr		= float2fix32(1.0);
}

void irq_dma_handler() {
	if(dma_hw->ints0 & (1u << dma_data_chan)){
		dma_hw->ints0 = (1u << dma_data_chan);
		oveload = true;
		vTaskNotifyGiveFromISR(dds_task_handle, pdFALSE);
	}
}


int dma_init(){
	
	// CHANNELS AND TIMER CLAIM

	// (X/Y)*sys_clk, where X is the first 16 bytes and Y is the second
	dds_timer_channel = dma_claim_unused_timer(false);

	if(dds_timer_channel == -1){
		loge(DDS, "Cannot claim timer for DDS.\n");	
		return -1;
	}
	logg(DDS, "calm dma timer: %d\n", dds_timer_channel);
	dma_timer_set_fraction(dds_timer_channel, DDS_TIMER_X_FRACTION, DDS_TIMER_Y_FRACTION);


	// claim dma channels
	dma_ctr_chan = dma_claim_unused_channel(false);
	if(dma_ctr_chan == -1){
		loge(DDS, "Cannot claim free dma");
		return -2;
	}
	
	dma_data_chan = dma_claim_unused_channel(false);
	if(dma_data_chan == -1){
		loge(DDS, "Cannot claim free dma\n");
		return -3;
	}
	
	// SETUP DMA_CONTROL
	dma_channel_config cconfig = dma_channel_get_default_config(dma_ctr_chan);
	channel_config_set_transfer_data_size(&cconfig, DMA_SIZE_32);
	channel_config_set_read_increment(&cconfig, false);
	channel_config_set_write_increment(&cconfig, false);
	channel_config_set_chain_to(&cconfig, dma_data_chan);


    dma_channel_configure(
        dma_ctr_chan,
        &cconfig,
		&dma_hw->ch[dma_data_chan],
        dma_channel_hw_data,
        DMA_CHANNEL_SETUP_SIZE,
        false
    );

	// SETUP DMA_DATA
    dma_channel_config dconfig = dma_channel_get_default_config(dma_data_chan);
    channel_config_set_transfer_data_size(&dconfig, DMA_SIZE_16);
    channel_config_set_read_increment(&dconfig, true);
    channel_config_set_write_increment(&dconfig, false);
	channel_config_set_dreq(&dconfig, dma_get_timer_dreq(dds_timer_channel));
    channel_config_set_chain_to(&dconfig, dma_ctr_chan);


    dma_channel_configure(
        dma_data_chan,
        &dconfig,
        &spi_get_hw(DAC_SPI_INST)->dr,
        dds_samples_buff,
        DDS_BUFF_SIZE,
        false
    );

	memcpy(dma_channel_hw_data, (uint32_t*)&dma_hw->ch[dma_data_chan], DMA_CHANNEL_SETUP_SIZE);
	
	dma_channel_set_irq0_enabled(dma_data_chan, true);
	irq_add_shared_handler(DMA_IRQ_0, irq_dma_handler, PICO_HIGHEST_IRQ_PRIORITY-1);
	irq_set_enabled(DMA_IRQ_0, true);

	dma_channel_start(dma_ctr_chan);

	return 0;
}

int dma_deinit(){

	// unclaim irq
	irq_set_enabled(DMA_IRQ_0, false);
	dma_channel_set_irq0_enabled(dma_data_chan, false);
	
	// unclaim dma channels
	dma_channel_unclaim(dma_data_chan);
	dma_channel_unclaim(dma_ctr_chan);
	
	// unclaim timer
	dma_timer_unclaim(dds_timer_channel);

	return 0;
}


void dds_task()
{

	while (1)
	{
		
		xTaskNotifyWait( 0, 0x00, NULL, portMAX_DELAY);

		// gpio_put(GPIO_DDS_TEST, !gpio_get(GPIO_DDS_TEST));
		memset(dds_samples_buff, 0x00, sizeof(dds_samples_buff));
		
		osc_idx=0;
		for (sample_idx = 0; sample_idx < DDS_BUFF_SIZE; sample_idx++)
		{

			for (osc_idx = 0; osc_idx < DAC_CHAN_NB; osc_idx++)
			{
				oscillators[osc_idx].one_sample = *( oscillators[osc_idx].sound->data + ( fix2int32(oscillators[osc_idx].phase_accum) ) );

				dds_samples_buff[sample_idx] += oscillators[osc_idx].one_sample>>2;

				oscillators[osc_idx].phase_accum += oscillators[osc_idx].phase_incr;
				while (oscillators[osc_idx].phase_accum >= int2fix32(oscillators[osc_idx].sound->len)) oscillators[osc_idx].phase_accum -= int2fix32(oscillators[osc_idx].sound->len);
				while (oscillators[osc_idx].phase_accum < int2fix32(0)) oscillators[osc_idx].phase_accum += int2fix32(oscillators[osc_idx].phase_incr);

			}

			dds_samples_buff[sample_idx] &= 0b0000111111111111;
			dds_samples_buff[sample_idx] |= 0b0111000000000000;

		}
		// gpio_put(GPIO_DDS_TEST, !gpio_get(GPIO_DDS_TEST));

		// logg(DDS, "phase incr %f\n", fix322float(oscillators[osc_idx].phase_incr));
		// log_hex(DDS, oscillators[0].sound->data, 16);
	}

	vTaskDelete(NULL);

}



// ============================================================
// ========================= EXTERNAL =========================
// dds library uses two dma's for write data to spi register. timer1 for dma is used for aquisition. 
// Every BUFF_LEN/AUDIO_FS second interrupt data buffer depend by frequency table.

int dds_init()
{

	gpio_init(GPIO_DDS_TEST);
	gpio_set_dir(GPIO_DDS_TEST, true);
	gpio_put(GPIO_DDS_TEST, 0);
	
	memset(dds_samples_buff, 0x00, sizeof(dds_samples_buff));
	
	// set sound
	for (uint8_t ii = 0; ii < DAC_CHAN_NB; ii++)
	{
		osc_init(&oscillators[ii]);
		dds_set_sound(ii, 0);
		dds_set_freq(ii, int2fix32(440));
		dds_set_amp(ii, int2fix32(1));
	}
	
	dac_init();
	dma_init();

	xTaskCreate(dds_task, "dds_task", 6*1024, NULL, 1, &dds_task_handle);

	return 0;
}



int dds_deinit()
{

	vTaskDelete(dds_task_handle);

	dma_channel_unclaim(dma_data_chan);
	dma_channel_unclaim(dma_ctr_chan);
	// irq_set_enabled(TIMER_IRQ_0, false);
	return 0;
}


int dds_write_buff(uint8_t buff, uint16_t size){

	return 0;
}

int dds_set_sound(uint8_t chan_num, uint8_t sound_idx){
	
	if(sound_idx >= SOUND_COUNT) return -1;
	oscillators[chan_num].sound = &sound_list[sound_idx];
	oscillators[chan_num].freq_to_incr	= divfix32(int2fix32(oscillators[chan_num].sound->len), int2fix32(DDS_FS));

	logg(DDS, "Change sound to \'%s\', sound size: %d\n", oscillators[chan_num].sound->sound_name, oscillators[chan_num].sound->len);
	return 0;
}


void dds_set_incr(uint8_t osc_num, fix32_t incr)
{
	oscillators[osc_num].phase_incr = incr;
}


void dds_set_freq(uint8_t osc_num, fix32_t freq)
{
	oscillators[osc_num].phase_incr = multfix32(freq, oscillators[osc_num].freq_to_incr);

	// logg(DDS, "set osc%d frequency: %f, incr: %f\n", osc_num, fix322float(freq), fix322float(oscillators[osc_num].phase_incr));
}

void dds_set_amp(uint8_t osc_num, fix32_t amp)
{
	oscillators[osc_num].amp = amp;
}

