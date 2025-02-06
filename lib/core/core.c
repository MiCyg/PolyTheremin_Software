#include "core.h"
#include "led_anim.h"
#include "het_generator.h"
#include "freq_meas.h"
// #include "cmsis.h"


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




uint16_t *buffer[CHANNEL_NB];
void buffer_analysis()
{

	// TODO send queue
	
	buffer[0] = freq_meas_dma_buffer(CHANNEL1);
	buffer[1] = freq_meas_dma_buffer(CHANNEL2);
	buffer[2] = freq_meas_dma_buffer(CHANNEL3);
	buffer[3] = freq_meas_dma_buffer(CHANNEL4);
	

}

QueueHandle_t xQueue;
void core_run()
{
	welcome_message();

	led_init();
	led_set_anim(LED_ANIM_HEART);

	het_generator_init();

	xQueue = xQueueCreate(16, sizeof(uint16_t*));
	
	freq_meas_init();
	freq_meas_set_wrap_cb(buffer_analysis);



	vTaskDelete(NULL);
}