#include "core.h"
#include "led_anim.h"
#include "het_generator.h"
#include "aquisition.h"

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


void core_run()
{
	welcome_message();

	led_init();
	led_set_anim(LED_ANIM_HEART);

	het_generator_init();

	aquisition_init();



	vTaskDelete(NULL);
}