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


	logc(CORE, COLOR_PURPLE, "\n");
	logc(CORE, COLOR_PURPLE, "-----------------------------------------\n");
	logc(CORE, COLOR_PURPLE, "|             BOOT SUCCESS!             |\n");
	logc(CORE, COLOR_PURPLE, "-----------------------------------------\n");
	logc(CORE, COLOR_GREEN, "Project name:   \'%s\'\n",   PROJECT_NAME );
	logc(CORE, COLOR_GREEN, "Meas sys clock:  %.0fkHz\n",   (double)(clock_get_hz(clk_sys))/1000);
	logc(CORE, COLOR_GREEN, "Version:         %s\n",      PROJECT_VERSION);
	logc(CORE, COLOR_GREEN, "Describe:       \'%s\'\n",   PROJECT_VERSION_DESCRIBE);
	logc(CORE, COLOR_GREEN, "Core cpu:        %d\n",   get_core_num());
}




void core_run()
{
	welcome_message();

	led_init();
	led_set_anim(LED_ANIM_HEART);

	het_generator_init();

	QueueHandle_t aquisitionDdsQueue = xQueueCreate(16, sizeof(float32_t)*CHAN_NUM);
	dds_init(&aquisitionDdsQueue);
	aquisition_init(&aquisitionDdsQueue);

	vTaskDelete(NULL);
}