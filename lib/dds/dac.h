#ifndef __DAC__
#define __DAC__

#include "comlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"

typedef enum dac_chan_e{
	DAC_CHAN0,
	DAC_CHAN1,
	DAC_CHAN2,
	DAC_CHAN3,

	DAC_CHAN_NB,
}dac_chan_e;



void dac_init();
void dac_deinit();

void dac_put(dac_chan_e chan, uint16_t value );
void dac_put_buffer(dac_chan_e chan, uint16_t *value, uint16_t len);



#endif // __DAC__