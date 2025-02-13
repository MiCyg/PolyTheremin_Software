#include "core.h"
#include "led_anim.h"
#include "het_generator.h"
#include "aquisition.h"
#include "dds.h"


void welcome_message(){


	gpio_init(GPIO_TEST);
	gpio_set_dir(GPIO_TEST, true);
	gpio_put(GPIO_TEST, 0);
	vTaskDelay(pdMS_TO_TICKS(10));
	gpio_put(GPIO_TEST, 1);
	vTaskDelay(pdMS_TO_TICKS(10));
	gpio_put(GPIO_TEST, 0);


	logc(CORE, COLOR_PURPLE, "");
	logc(CORE, COLOR_PURPLE, "-----------------------------------------");
	logc(CORE, COLOR_PURPLE, "|             BOOT SUCCESS!             |");
	logc(CORE, COLOR_PURPLE, "-----------------------------------------");
	logc(CORE, COLOR_GREEN, "Project name:   \'%s\'",   PROJECT_NAME );
	logc(CORE, COLOR_GREEN, "Meas sys clock:  %.0fkHz",   (double)(clock_get_hz(clk_sys))/1000);
	logc(CORE, COLOR_GREEN, "Version:         %s",      PROJECT_VERSION);
	logc(CORE, COLOR_GREEN, "Describe:       \'%s\'",   PROJECT_VERSION_DESCRIBE);
	logc(CORE, COLOR_GREEN, "Core cpu:        %d",   get_core_num());
}




void core_run()
{
	welcome_message();

	led_init();
	led_set_anim(LED_ANIM_HEART);

	het_generator_init();

	QueueHandle_t aquisitionDdsQueue = xQueueCreate(16, sizeof(float32_t)*CHAN_NUM);
	aquisition_init(&aquisitionDdsQueue);
	dds_init(&aquisitionDdsQueue);


	dds_set_sound(0, 1);
	dds_set_sound(1, 1);
	dds_set_sound(2, 2);
	dds_set_sound(3, 3);
	
	dds_set_amp(0, int2fix32(0));
	dds_set_amp(1, int2fix32(1));
	dds_set_amp(2, int2fix32(1));
	dds_set_amp(3, int2fix32(0));
	// dds_set_freq(0, int2fix32(990));


	// while (1)
	// {
	// 	for (uint16_t _freq = 100; _freq < 5000; _freq+=1)
	// 	{
	// 		dds_set_freq(0, int2fix32(_freq));
	// 		vTaskDelay(pdMS_TO_TICKS(10));
	// 	}
	// }
	


	vTaskDelete(NULL);
}