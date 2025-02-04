#include "comlib.h"
#include "core.h"



int main( void )
{
	stdio_init_all();
    logger_init();

	xTaskCreate(core_run, CORE_NAME, CORE_STACK_SIZE, NULL, 0, NULL);

    vTaskStartScheduler(); // start FreeRTOS
	

}