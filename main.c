#include "comlib.h"





void helloTask()
{
	while(1)
	{
		printf("Hello, World!\n");
		vTaskDelay(1000);
	}
}


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

    xTaskCreate(helloTask, "example", 1024, NULL, 0, NULL);

    vTaskStartScheduler();

    while(1);

}
