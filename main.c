#include "comlib.h"
#include "led_anim.h"
#include "het_generator.h"
#include <math.h>
#include "arm_math.h"


                                                                                
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

void cmsis_test_task()
{
	// vTaskDelay(1000);
	// float32_t t[10] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
	// float32_t bulbul  = arm_cos_f32(t[0]);
	// for (size_t i = 0; i < 10; i++)
	// {
	// 	// logg(MAIN, "sin(%.2f) = %.2f\n", t[i], bulbul);
	// }
	

	vTaskDelete(NULL);
}

int main( void )
{
	stdio_init_all();
    logger_init();
	welcome_message();

	led_init();
	led_set_anim(LED_ANIM_HEART);

	het_generator_init();

	xTaskCreate(cmsis_test_task, "cmsis_test_task", 1024, NULL, 1, NULL);




    vTaskStartScheduler();
    while(1);
}
