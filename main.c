#include "comlib.h"
#include "led_anim.h"
#include "het_generator.h"



void welcome_message(){
	logc(MAIN, COLOR_PURPLE, "\n");
	logc(MAIN, COLOR_PURPLE, "-----------------------------------------\n");
	logc(MAIN, COLOR_PURPLE, "|             BOOT SUCCESS!             |\n");
	logc(MAIN, COLOR_PURPLE, "-----------------------------------------\n");
	logc(MAIN, COLOR_GREEN, "Project name:   \'%s\'\n",   PROJECT_NAME );
	logc(MAIN, COLOR_GREEN, "Meas sys clock:  %.2fMHz\n",   (float)(clock_get_hz(clk_sys))/1000000.0);
	logc(MAIN, COLOR_GREEN, "Version:         %s\n",      PROJECT_VERSION);
	logc(MAIN, COLOR_GREEN, "Describe:       \'%s\'\n",   PROJECT_VERSION_DESCRIBE);
}



int main( void )
{
	stdio_init_all();
    logger_init();
	welcome_message();

	led_init();
	led_set_anim(LED_ANIM_HEART);

	het_generator_init();

    vTaskStartScheduler();
    while(1);
}
