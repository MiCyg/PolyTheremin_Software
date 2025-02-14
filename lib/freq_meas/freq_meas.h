#ifndef __FREQ_MEAS__
#define __FREQ_MEAS__

#include "comlib.h"

#include "hardware/dma.h"
#include "hardware/pwm.h"

typedef enum freq_meas_channel_num_e
{
	CHANNEL1,
	CHANNEL2,
	CHANNEL3,
	CHANNEL4,
	CHANNEL_NB,
} freq_meas_channel_num_e;

typedef struct freq_meas_channel_t
{
	const uint16_t gpio;

	uint16_t pwm_slice;
	int dma_chan;
	uint16_t det_freq_count;
	uint16_t dma_buff[FREQ_DET_DMA_BUFFER_NUM];
	dma_channel_config dma_config;

} freq_meas_channel_t;

void freq_meas_init();
void freq_meas_deinit();

uint16_t *freq_meas_dma_buffer(freq_meas_channel_num_e chan);
void freq_meas_set_wrap_cb(void (*function)());

#endif // __FREQ_MEAS__