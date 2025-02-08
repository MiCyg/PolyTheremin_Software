#include "aquisition.h"
#include "hardware/dma.h"

// use dma as buffer data from gpios registers
int dma_channel;
dma_channel_config dma_config;
uint32_t aquisition_buffer[AQUISITION_BUFFER_SIZE];
uint32_t bulbul = 12345;


void dma_overload_irq()
{
	gpio_toggle(GPIO_TEST);
	dma_hw->ints0 = 1u << dma_channel;

    dma_channel_configure(
        dma_channel,
        &dma_config,
        &aquisition_buffer,     // Write to one buffer
        &bulbul,       // Read all gpios
        AQUISITION_BUFFER_SIZE, 
        false                    
    );
	dma_channel_set_read_addr(dma_channel, &bulbul, true);

}

int aquisition_init()
{
	logg(AQUISITION, "Aquisition init\n");
	// gpio_toggle(GPIO_TEST);

	int dma_timer = dma_claim_unused_timer(false);
	if(dma_timer == -1)
	{
		loge(AQUISITION, "Cannot claim timer for DDS.\n");	
		return -1;
	}

	logg(AQUISITION, "Calm dma timer: %d\n", dma_timer);

	dma_timer_set_fraction(dma_timer, AQUISITION_TIMER_X_FRACTION, AQUISITION_TIMER_Y_FRACTION);


    dma_channel = dma_claim_unused_channel(false);
	if(dma_channel == -1)
	{
		loge(AQUISITION, "Cannot claim dma channel DDS.\n");	
		return -1;
	}
	logg(AQUISITION, "Calm dma channel: %d\n", dma_channel);

    dma_config = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&dma_config, DMA_SIZE_32);
    channel_config_set_read_increment(&dma_config, false);
    // channel_config_set_write_increment(&dma_config, true);

	channel_config_set_dreq(&dma_config, dma_get_timer_dreq(dma_timer));
	
    // Register an interrupt for DMA
    irq_set_exclusive_handler(DMA_IRQ_0, dma_overload_irq);
    irq_set_enabled(DMA_IRQ_0, true);


    dma_channel_configure(
        dma_channel,
        &dma_config,
        &aquisition_buffer,     // Write to one buffer
        &bulbul,       // Read all gpios
        AQUISITION_BUFFER_SIZE, 
        true                    
    );


	return 0;
}

void aquisition_deinit()
{
	logg(AQUISITION, "Aquisition deinit\n");
}
