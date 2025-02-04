#include "core.h"
#include "led_anim.h"
#include "het_generator.h"

void welcome_message(){
	logc(MAIN, COLOR_PURPLE, "\n");
	logc(MAIN, COLOR_PURPLE, "-----------------------------------------\n");
	logc(MAIN, COLOR_PURPLE, "|             BOOT SUCCESS!             |\n");
	logc(MAIN, COLOR_PURPLE, "-----------------------------------------\n");
	logc(MAIN, COLOR_GREEN, "Project name:   \'%s\'\n",   PROJECT_NAME );
	logc(MAIN, COLOR_GREEN, "Meas sys clock:  %.2fMHz\n",   (float)(clock_get_hz(clk_sys))/1000000.0);
	logc(MAIN, COLOR_GREEN, "Meas sys clock:  %.2fMHz\n",   (float)(clock_get_hz(clk_sys))/1000000.0);
	logc(MAIN, COLOR_GREEN, "Version:         %s\n",      PROJECT_VERSION);
	logc(MAIN, COLOR_GREEN, "Describe:       \'%s\'\n",   PROJECT_VERSION_DESCRIBE);
}

char ptrTaskList[1024];
void system_info()
{
	vTaskList(ptrTaskList);
	printf(("**********************************\n"));
	printf(("Task  State   Prio    Stack    Num\n")); 
	printf(("**********************************\n"));
	printf(ptrTaskList);
	printf(("**********************************\n"));

	vTaskDelete(NULL);
}



void task1()
{
	while(1)
	{
		printf("Task 2 generate system info task\n");
		xTaskCreate(system_info, "system_info", 1024*4, NULL, 0, NULL);

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
	vTaskDelete(NULL);
}

void led_control()
{
	while(1)
	{
		// logg(LED, "LED init\n");

		// vTaskDelay(pdMS_TO_TICKS(5000));
		
		// logg(LED, "LED change anim\n");
		// led_set_anim(LED_ANIM_HEART);
		// vTaskDelay(pdMS_TO_TICKS(5000));

		// logg(LED, "LED disable\n");
		// led_deinit();
		vTaskDelay(pdMS_TO_TICKS(5000));
	}
	vTaskDelete(NULL);
}

void core_run()
{
	welcome_message();
	het_generator_init();


	xTaskCreate(task1, "task1", 1024*4, NULL, 0, NULL);
	xTaskCreate(led_control, "led", 1024*2 , NULL, 0, NULL);
	

	system_info();



}