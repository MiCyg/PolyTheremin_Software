
#include "ws2812.h"
#include "ws2812.pio.h"
#include "hardware/clocks.h"

static PIO ws2812_pio = WS2812_PIO_INSTANCE;
static uint ws2812_offset;
static int ws2812_sm;


static inline void ws2812_program_init(PIO pio, uint sm, uint offset, uint pin, float freq, bool rgbw) {
	int err;
    pio_gpio_init(pio, pin);
    err = pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);
	panic_check(err != 0, "Cannot set pindirs");

    pio_sm_config c = ws2812_program_get_default_config(offset);
    sm_config_set_sideset_pins(&c, pin);
    sm_config_set_out_shift(&c, false, true, rgbw ? 32 : 24);
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    int cycles_per_bit = ws2812_T1 + ws2812_T2 + ws2812_T3;
    float div = clock_get_hz(clk_sys) / (freq * cycles_per_bit);
    sm_config_set_clkdiv(&c, div);

    err = pio_sm_init(pio, sm, offset, &c);
	panic_check(err != 0, "Cannot init state machine");
    pio_sm_set_enabled(pio, sm, true);
}

static inline void ws2812_program_deinit(PIO pio, uint sm, uint offset) {
	pio_sm_set_enabled(pio, sm, false);
	pio_sm_unclaim(pio, sm);

}

// ======================= EXTERNAL =======================

int ws2812_init(){

	ws2812_sm = pio_claim_unused_sm(ws2812_pio,false);
	panic_check(ws2812_sm == -1, "Cannot claim unused sm");

    ws2812_offset = pio_add_program(ws2812_pio, &ws2812_program);
	panic_check(ws2812_sm == -1, "Cannot add program");

	logg(LED, "Claim sm: %d, offset: %d", ws2812_sm, ws2812_offset);
    ws2812_program_init(ws2812_pio, ws2812_sm, ws2812_offset, GPIO_UI_LED, WS2812_SPEED, WS2812_IS_RGBW);
	return 0;
}

int ws2812_deinit(){
	ws2812_program_deinit(ws2812_pio, ws2812_sm, ws2812_offset);
	pio_remove_program(ws2812_pio, &ws2812_program, ws2812_offset);
	return 0;
}

void ws2812_put(color_t pixel_grb){
	pio_sm_put_blocking(ws2812_pio, 0, pixel_grb.raw << 8u);
}






