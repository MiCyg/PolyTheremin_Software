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



// one tick -> 500us
// Ftimer = Fsys * FREQ_DET_TIMER_X_FRACTION / FREQ_DET_TIMER_Y_FRACTION
float ticks_to_frequency(float ticks)
{
	return  ( clock_get_hz(clk_sys) * FREQ_DET_TIMER_X_FRACTION ) / ( ticks * 0.0005 * FREQ_DET_TIMER_Y_FRACTION );
}

void core_run()
{
	welcome_message();

	gpio_init(GPIO_TEST);
	gpio_set_dir(GPIO_TEST, true);
	gpio_put(GPIO_TEST, 0);
	vTaskDelay(pdMS_TO_TICKS(10));
	gpio_put(GPIO_TEST, 1);
	vTaskDelay(pdMS_TO_TICKS(10));
	gpio_put(GPIO_TEST, 0);
	vTaskDelay(pdMS_TO_TICKS(10));
	gpio_put(GPIO_TEST, 1);


	led_init();
	led_set_anim(LED_ANIM_HEART);

	het_generator_init();

	aquisition_init();
	
	// vTaskDelay(pdMS_TO_TICKS(1000));
	// start_dma();

	// dds_init();
	// dds_set_amp(0, 0);
	// dds_set_amp(1, 0);
	// dds_set_amp(2, 0);
	// dds_set_amp(3, 0);



	int i = 0;
	while (1)
	{
		if(2137 == i)
		{
			logg(CORE, "Goodbye cruel world ...\n\n");
			return ;

		}
		vTaskDelay(1000);
	}
	vTaskDelete(NULL);
}