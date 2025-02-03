
#include "ws2812.h"
#include "ws2812.pio.h"
#include "hardware/clocks.h"




static inline void ws2812_program_init(PIO pio, uint sm, uint offset, uint pin, float freq, bool rgbw) {

    pio_gpio_init(pio, pin);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);

    pio_sm_config c = ws2812_program_get_default_config(offset);
    sm_config_set_sideset_pins(&c, pin);
    sm_config_set_out_shift(&c, false, true, rgbw ? 32 : 24);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    int cycles_per_bit = ws2812_T1 + ws2812_T2 + ws2812_T3;
    float div = clock_get_hz(clk_sys) / (freq * cycles_per_bit);
    sm_config_set_clkdiv(&c, div);

    pio_sm_init(pio, sm, offset, &c);
    pio_sm_set_enabled(pio, sm, true);
}

static inline void ws2812_program_deinit(PIO pio, uint sm, uint offset) {
	pio_sm_set_enabled(pio, sm, false);
	pio_sm_unclaim(pio, sm);

}

// ======================= EXTERNAL =======================

PIO pio;
uint offset;
int sm = 0;
int ws2812_init(){
	pio = WS2812_PIO_INSTANCE;

	// sm = pio_claim_unused_sm(pio,false);
	// if(sm == -1) return -1;

    offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, GPIO_UI_LED, WS2812_SPEED, WS2812_IS_RGBW);
	return 0;
}

int ws2812_deinit(){
	ws2812_program_deinit(pio, sm, offset);
	pio_remove_program(pio, &ws2812_program, offset);
	return 0;
}

void ws2812_put(color_t pixel_grb){
	pio_sm_put_blocking(pio, 0, pixel_grb.raw << 8u);
}






