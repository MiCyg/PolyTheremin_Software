#ifndef __DDS__
#define __DDS__

#include "comlib.h"
#include "audio.h"
#include "dac.h"
#include "hardware/dma.h"
#include "fixfloat.h"





typedef struct dds_t{
	audio_t *sound;
	fix32_t phase_accum;
	fix32_t phase_incr;
	fix32_t freq_to_incr;
	fix32_t amp;
	uint16_t one_sample;
}dds_t;

int dds_init();
int dds_perform();
int dds_deinit();

int dds_set_sound(uint8_t osc_num, uint8_t sound_idx);
void dds_set_freq(uint8_t osc_num, fix32_t freq);
void dds_set_incr(uint8_t osc_num, fix32_t incr);
void dds_set_amp(uint8_t osc_num, fix32_t amp);
int dds_write_buff(uint8_t buff, uint16_t size);

#endif // __DDS__