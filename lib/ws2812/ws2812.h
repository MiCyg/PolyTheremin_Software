#ifndef __WS2812__
#define __WS2812__


#include "comlib.h"
#include "hardware/pio.h"

typedef union color_t {
	struct {
		uint8_t blue;
		uint8_t red;
		uint8_t green;
		uint8_t __alignment;
	} colors;

	uint32_t raw;
}color_t;

int ws2812_init();
int ws2812_deinit();
void ws2812_put(color_t pixel_grb);
#endif // __WS2812__