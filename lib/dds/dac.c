#include "dac.h"


// static int dac_dma_chan;

// #define DAC_BUFFER_SIZE 125
// static uint16_t dac_buffer[DAC_BUFFER_SIZE];

static const struct {uint cs_pin; uint16_t masker; } 
	dacInfo[DAC_CHAN_NB] = {
		{.cs_pin=GPIO_DAC_CS1, .masker=0b0111000000000000},
		{.cs_pin=GPIO_DAC_CS1, .masker=0b1111000000000000},
		{.cs_pin=GPIO_DAC_CS2, .masker=0b0111000000000000},
		{.cs_pin=GPIO_DAC_CS2, .masker=0b1111000000000000},
};


void cs_select(uint cs_pin){
	gpio_put(cs_pin, 0); 
}

void cs_deselect(uint cs_pin){
	gpio_put(cs_pin, 1); 
}


void _spi_write16(uint cs_pin, uint16_t value){
	cs_select(cs_pin);
	spi_write_blocking(DAC_SPI_INST, (uint8_t*)&value+1, 1);
	spi_write_blocking(DAC_SPI_INST, (uint8_t*)&value, 1);
	cs_deselect(cs_pin);

}


// ===================== EXTERNAL FUNCTION =====================
void dac_init(){

	// init spi
	gpio_init(GPIO_DAC_LDAC);
	gpio_set_dir(GPIO_DAC_LDAC, GPIO_OUT);
	gpio_put(GPIO_DAC_LDAC, 0);

	gpio_set_function(GPIO_DAC_CLK, GPIO_FUNC_SPI);
	gpio_set_function(GPIO_DAC_TX, GPIO_FUNC_SPI);
	gpio_set_function(GPIO_DAC_CS1, GPIO_FUNC_SPI);
	// gpio_set_function(GPIO_DAC_CS2, GPIO_FUNC_SPI);


	// spi_get_hw(DAC_SPI_INST).
	uint baud = spi_init(DAC_SPI_INST, DAC_SPI_CLK_SPEED);
	spi_set_format(DAC_SPI_INST, 16, SPI_CPOL_0, SPI_CPHA_0, SPI_LSB_FIRST);
	spi_set_slave(DAC_SPI_INST, false);
	logg(DAC, "Init spi clock speed: %d, actual speed is: %d\n", DAC_SPI_CLK_SPEED, baud);



	// init spi device
	// spi_write_blocking(DAC_SPI_INST, dacInfo[0].masker, 16);
	// spi_write_blocking(DAC_SPI_INST, dacInfo[1].masker, 16);

	// init dma for stream
	// dac_dma_chan = dma_claim_unused_channel(true);
	// dma_channel_config conf = dma_channel_get_default_config(dac_dma_chan);
	// channel_config_set_transfer_data_size(&conf, DMA_SIZE_16);
	// int timer_chan = dma_claim_unused_timer(true);
	// dma_timer_set_fraction(timer_chan, 256, 64000); // for 50000Hz aquisition
	// channel_config_set_dreq(&conf, dma_get_timer_dreq(timer_chan));
	
	// dma_channel_configure(
	// 	dac_dma_chan,               
	// 	&conf,                      
	// 	&spi_get_hw(DAC_SPI_INST)->dr,  // write address (SPI data register)
	// 	dac_buffer,                   // The initial read address
	// 	DAC_BUFFER_SIZE,            // Number of transfers
	// 	false                       // Don't start immediately.
	// );



}

void dac_deinit(){
	spi_deinit(DAC_SPI_INST);

	gpio_set_function(GPIO_DAC_CLK, GPIO_FUNC_NULL);
	gpio_set_function(GPIO_DAC_TX, GPIO_FUNC_NULL);
	gpio_deinit(GPIO_DAC_CS2);
	gpio_deinit(GPIO_DAC_CS1);
	gpio_deinit(GPIO_DAC_LDAC);
}


void dac_put(dac_chan_e chan, uint16_t value ){
	_spi_write16(dacInfo[chan].cs_pin, value|dacInfo[chan].masker);
}

void dac_put_buffer(dac_chan_e chan, uint16_t *value, uint16_t len){

}

void dac_set_wrap_buffer_callback(void (*callback)()){


}

