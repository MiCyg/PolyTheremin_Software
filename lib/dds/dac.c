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
	if(baud != DAC_SPI_CLK_SPEED)
	{
		logg(DAC, "SPI set speed: %d, real speed: %d\n", DAC_SPI_CLK_SPEED, baud);
	}

	dac_put(0, 65536>>1);
	dac_put(1, 65536>>1);
	dac_put(2, 65536>>1);
	dac_put(3, 65536>>1);


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
