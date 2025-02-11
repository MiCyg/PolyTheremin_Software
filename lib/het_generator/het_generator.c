
#include "het_generator.h"
#include "het_generator.pio.h"

static uint16_t pio_program_offset;
static PIO pio = HET_GEN_PIO_INSTANCE;


// returns real frequency of signal
float het_generator_program_init(PIO pio, uint sm, uint pin, float freq) {

    pio_sm_config c = het_generator_program_get_default_config(pio_program_offset);
    pio_gpio_init(pio, pin);
    sm_config_set_set_pins(&c, pin, 1);
    pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);
    
	uint16_t div_int;
    uint8_t div_frac;
	
	float fract = (float)(clock_get_hz(clk_sys))/(freq*2);
    pio_calculate_clkdiv_from_float(fract, &div_int, &div_frac);
    sm_config_set_clkdiv_int_frac(&c, div_int, div_frac);

    pio_sm_init(pio, sm, pio_program_offset, &c);
    pio_sm_set_enabled(pio, sm, true);

	return (float)(clock_get_hz(clk_sys))/((float)div_int+(float)div_int/255.0)/2;
}



// ======================= EXTERNAL =====================

void het_generator_init(){

    pio_program_offset = pio_add_program(pio, &het_generator_program);
	logg(HET_GEN, "Loaded program at address: 0x%04X\n", pio_program_offset);


	float real_freq0 = het_generator_program_init(pio, 0, HET_GEN0_GPIO, HET_GEN0_FREQ);
	if((uint32_t)real_freq0 != (uint32_t)HET_GEN0_FREQ) logg(HET_GEN, "Generator[0] freq was changed -> Set: %dHz, Real: %.0fHz\n", HET_GEN0_FREQ, real_freq0);

	float real_freq1 = het_generator_program_init(pio, 1, HET_GEN1_GPIO, HET_GEN1_FREQ);
	if((uint32_t)real_freq1 != (uint32_t)HET_GEN1_FREQ) logg(HET_GEN, "Generator[1] freq was changed -> Set: %dHz, Real: %.0fHz\n", HET_GEN1_FREQ, real_freq1);

	float real_freq2 = het_generator_program_init(pio, 2, HET_GEN2_GPIO, HET_GEN2_FREQ);
	if((uint32_t)real_freq2 != (uint32_t)HET_GEN2_FREQ) logg(HET_GEN, "Generator[2] freq was changed -> Set: %dHz, Real: %.0fHz\n", HET_GEN2_FREQ, real_freq2);

	float real_freq3 = het_generator_program_init(pio, 3, HET_GEN3_GPIO, HET_GEN3_FREQ);
	if((uint32_t)real_freq3 != (uint32_t)HET_GEN3_FREQ) logg(HET_GEN, "Generator[3] freq was changed -> Set: %dHz, Real: %.0fHz\n", HET_GEN3_FREQ, real_freq3);

}

void het_generator_deinit(){
	for (size_t i = 0; i < 4; i++)
		pio_sm_set_enabled(pio, i, false);

	pio_remove_program(pio, &het_generator_program, 0);

}

