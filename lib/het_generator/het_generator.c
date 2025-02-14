
#include "het_generator.h"
#include "het_generator.pio.h"

#define NUMBER_OF_PIO_INSTRUCTIONS 2
static uint16_t pio_program_offset;

struct het_gen_t
{
	uint gpio;
	uint32_t frequency;
} het_gens[4] = {
	{.gpio = HET_GEN0_GPIO, .frequency = HET_GEN0_FREQ},
	{.gpio = HET_GEN1_GPIO, .frequency = HET_GEN1_FREQ},
	{.gpio = HET_GEN2_GPIO, .frequency = HET_GEN2_FREQ},
	{.gpio = HET_GEN3_GPIO, .frequency = HET_GEN3_FREQ}};

// returns real frequency of signal
float het_generator_program_init(PIO pio, uint sm, uint pin, float freq)
{

	pio_sm_config c = het_generator_program_get_default_config(pio_program_offset);
	pio_gpio_init(pio, pin);
	sm_config_set_set_pins(&c, pin, 1);
	pio_sm_set_consecutive_pindirs(pio, sm, pin, 1, true);

	uint16_t div_int;
	uint8_t div_frac;

	float fract = (float)(clock_get_hz(clk_sys)) / (freq * 2);
	pio_calculate_clkdiv_from_float(fract, &div_int, &div_frac);
	sm_config_set_clkdiv_int_frac(&c, div_int, div_frac);

	pio_sm_init(pio, sm, pio_program_offset, &c);
	pio_sm_set_enabled(pio, sm, true);

	return (float)(clock_get_hz(clk_sys)) / ((float)div_int + (float)div_int / 255.0) / NUMBER_OF_PIO_INSTRUCTIONS;
}

// ======================= EXTERNAL =====================
void het_generator_init()
{

	pio_program_offset = pio_add_program(HET_GEN_PIO_INSTANCE, &het_generator_program);
	logi(HET_GEN, "Loaded program at address: 0x%04X", pio_program_offset);

	for (uint sm = 0; sm < 4; sm++)
	{
		float real_freq = het_generator_program_init(HET_GEN_PIO_INSTANCE, sm, het_gens[sm].gpio, het_gens[sm].frequency);
		if ((uint32_t)real_freq != (uint32_t)het_gens[sm].frequency)
			logw(HET_GEN, "Het_gen%d set: %dHz, real: %.0fHz", sm, het_gens[sm].frequency, real_freq);
	}
}

void het_generator_deinit()
{
	for (size_t sm = 0; sm < 4; sm++)
		pio_sm_set_enabled(HET_GEN_PIO_INSTANCE, sm, false);

	pio_remove_program(HET_GEN_PIO_INSTANCE, &het_generator_program, 0);
}
