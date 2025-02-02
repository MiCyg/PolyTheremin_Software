#include "comlib.h"

void helloTask()
{
	while (true) {
		printf("Hello, world!\n");
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}



int main()
{
    stdio_init_all();

	printf("BULBUL\n");

	xTaskCreate(helloTask, "helloTask", 1024, NULL, 1, NULL);

	// vTaskStartScheduler();

	while (1)
	{
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
	
}
