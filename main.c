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

    printf("Start\n");

    xTaskCreate(helloTask, "example", 1024, NULL, 0, NULL);

    vTaskStartScheduler();

    while(1);

}
