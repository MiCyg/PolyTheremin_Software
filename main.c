#include "comlib.h"
#include "led_anim.h"







int main( void )
{
	stdio_init_all();
    logger_init();
	
	logc(MAIN, COLOR_LIGHT_GREEN, "-----------------------------------------\n");
	logc(MAIN, COLOR_LIGHT_GREEN, "|             BOOT SUCCESS!             |\n");
	logc(MAIN, COLOR_LIGHT_GREEN, "-----------------------------------------\n");
	logc(MAIN, COLOR_GREEN, "Project name:   \'%s\'\n",   PROJECT_NAME );
	logc(MAIN, COLOR_GREEN, "Meas sys clock:  %.2fMHz\n",   (float)(clock_get_hz(clk_sys))/1000000.0);
	logc(MAIN, COLOR_GREEN, "Version:         %s\n",      PROJECT_VERSION);
	logc(MAIN, COLOR_GREEN, "Describe:       \'%s\'\n",   PROJECT_VERSION_DESCRIBE);

	led_init();
	led_set_anim(LED_ANIM_HEART);


    vTaskStartScheduler();

    while(1);

}
