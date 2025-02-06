#include "core.h"
#include "led_anim.h"
#include "het_generator.h"
#include "freq_meas.h"
#include "dds.h"


void welcome_message(){
	logc(CORE, COLOR_PURPLE, "\n");
	logc(CORE, COLOR_PURPLE, "-----------------------------------------\n");
	logc(CORE, COLOR_PURPLE, "|             BOOT SUCCESS!             |\n");
	logc(CORE, COLOR_PURPLE, "-----------------------------------------\n");
	logc(CORE, COLOR_GREEN, "Project name:   \'%s\'\n",   PROJECT_NAME );
	logc(CORE, COLOR_GREEN, "Meas sys clock:  %.2fMHz\n",   (float)(clock_get_hz(clk_sys))/1000000.0);
	logc(CORE, COLOR_GREEN, "Version:         %s\n",      PROJECT_VERSION);
	logc(CORE, COLOR_GREEN, "Describe:       \'%s\'\n",   PROJECT_VERSION_DESCRIBE);
}



// one tick -> 500us
// Ftimer = Fsys * FREQ_DET_TIMER_X_FRACTION / FREQ_DET_TIMER_Y_FRACTION
float ticks_to_frequency(float ticks)
{
	return  ( clock_get_hz(clk_sys) * FREQ_DET_TIMER_X_FRACTION ) / ( ticks * FREQ_DET_TIMER_Y_FRACTION );
}


uint16_t *buffer[CHANNEL_NB];
float means[CHANNEL_NB];
void buffer_analysis()
{

	// TODO send queue
	
	// for (uint8_t channel = 0; channel < CHANNEL_NB; channel++)
	// {
	// 	buffer[channel] = freq_meas_dma_buffer(channel);
		
	// 	means[channel] = 0;
	// 	for (uint32_t idx = 0; idx < FREQ_DET_DMA_BUFFER_NUM; idx++) 
	// 	{
	// 		means[channel] += (float)(*(buffer[channel]+idx));
	// 	}
	// 	means[channel] = means[channel] / FREQ_DET_DMA_BUFFER_NUM;

	// 	dds_set_freq(channel, float2fix32(ticks_to_frequency(means[channel])));
	// }



}

void core_run()
{
	welcome_message();

	led_init();
	led_set_anim(LED_ANIM_HEART);

	het_generator_init();

	
	freq_meas_init();
	freq_meas_set_wrap_cb(buffer_analysis);

	dds_init();



	vTaskDelete(NULL);
}