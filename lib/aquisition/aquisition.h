#ifndef __AQUISITION__
#define __AQUISITION__

#include "comlib.h"


typedef enum channel_e
{
	CHAN0,
	CHAN1,
	CHAN2,
	CHAN3,
	CHAN_NUM
}channel_e;


int aquisition_init();
void aquisition_deinit();
void start_dma();


#endif // __AQUISITION__