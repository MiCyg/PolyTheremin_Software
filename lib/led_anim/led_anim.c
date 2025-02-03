#include "led_anim.h"


static color_t color;
static uint32_t anim_time_diff_us;
static uint32_t anim_time_us;
static led_animation_e actual_animation = LED_ANIM_BLINK_IDLE;
TaskHandle_t led_task_handle;

void led_update();

void led_task(void *pvParameters){
	led_init();
	while(1){
		led_update();
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}



void led_init(){
	xTaskCreate(led_task, "lead_task", 1024, NULL, 0, &led_task_handle);
	ws2812_init();
	anim_time_us = 0;
	color.raw = 0;
}

void led_deinit(){
	vTaskDelete(led_task_handle);

	ws2812_deinit();
}

#define BLINK_BRIGHT 0.06
#define BLINK_COLOR 0x0055ff20
#define BLINK_TIME 2000000
void led_anim_blink(){
	anim_time_diff_us = time_us_32()-anim_time_us;

	if(anim_time_diff_us < BLINK_TIME/2){
		if(!color.raw){
			color.raw			= BLINK_COLOR;
			color.colors.red	*= BLINK_BRIGHT;
			color.colors.green	*= BLINK_BRIGHT;
			color.colors.blue	*= BLINK_BRIGHT;
			ws2812_put(color);
		}
	}
	else if(anim_time_diff_us < BLINK_TIME){
		if(color.raw){
			color.raw = 0;
			ws2812_put(color);
		}
	}
	
	if(anim_time_diff_us >= BLINK_TIME){
		// end of animation
		anim_time_us = time_us_32();
	}

}

#define BLINK_IDLE_BRIGHT 0.1
#define BLINK_IDLE_COLOR 0x0080ffed
#define BLINK_IDLE_TIME 2000000
void led_anim_blink_idle(){
	anim_time_diff_us = time_us_32()-anim_time_us;

	if(anim_time_diff_us < BLINK_IDLE_TIME/2){
		if(!color.raw){
			color.raw			= BLINK_IDLE_COLOR;
			color.colors.red	*= BLINK_IDLE_BRIGHT;
			color.colors.green	*= BLINK_IDLE_BRIGHT;
			color.colors.blue	*= BLINK_IDLE_BRIGHT;
			ws2812_put(color);
		}
	}
	else if(anim_time_diff_us < BLINK_IDLE_TIME){
		if(color.raw){
			color.raw = 0;
			ws2812_put(color);
		}
	}
	
	if(anim_time_diff_us >= BLINK_IDLE_TIME){
		// end of animation
		anim_time_us = time_us_32();
	}

}

#define BLINK_OF_DEAD_BRIGHT 0.2
#define BLINK_OF_DEAD_COLOR 0x0000ff00
#define BLINK_OF_DEAD_TIME 500000
void led_anim_blink_of_dead(){
	anim_time_diff_us = time_us_32()-anim_time_us;

	if(anim_time_diff_us < BLINK_OF_DEAD_TIME/2){
		if(!color.raw){
			color.raw			= BLINK_OF_DEAD_COLOR;
			color.colors.red	*= BLINK_OF_DEAD_BRIGHT;
			color.colors.green	*= BLINK_OF_DEAD_BRIGHT;
			color.colors.blue	*= BLINK_OF_DEAD_BRIGHT;
			ws2812_put(color);
		}
	}
	else if(anim_time_diff_us < BLINK_OF_DEAD_TIME){
		if(color.raw){
			color.raw = 0;
			ws2812_put(color);
		}
	}
	
	// logg(LED, "%8d, r:%3d, g:%3d, b:%3d\n", anim_time_us, color.colors.red, color.colors.green, color.colors.blue);
	if(anim_time_diff_us >= BLINK_OF_DEAD_TIME){
		// end of animation
		anim_time_us = time_us_32();
	}

}

#define HEART_BRIGHT 0.2
#define HEART_COLOR 0x0055ff20
#define HEART_TIME 2000000

void led_anim_heart(){
	anim_time_diff_us = time_us_32()-anim_time_us;

	if(anim_time_diff_us <= HEART_TIME/2){
		color.raw			= HEART_COLOR;
		color.colors.red	*= (float)anim_time_diff_us*2.0 / HEART_TIME;
		color.colors.green	*= (float)anim_time_diff_us*2.0 / HEART_TIME;
		color.colors.blue	*= (float)anim_time_diff_us*2.0 / HEART_TIME;
		color.colors.red	*= HEART_BRIGHT;
		color.colors.green	*= HEART_BRIGHT;
		color.colors.blue	*= HEART_BRIGHT;
		ws2812_put(color);
	}
	else if(anim_time_diff_us < HEART_TIME){
		color.raw			= HEART_COLOR;
		color.colors.red	*= (float)(HEART_TIME-(anim_time_diff_us))*2.0/ HEART_TIME;
		color.colors.green	*= (float)(HEART_TIME-(anim_time_diff_us))*2.0/ HEART_TIME;
		color.colors.blue	*= (float)(HEART_TIME-(anim_time_diff_us))*2.0/ HEART_TIME;
		color.colors.red	*= HEART_BRIGHT;
		color.colors.green	*= HEART_BRIGHT;
		color.colors.blue	*= HEART_BRIGHT;
		ws2812_put(color);
	}
	
	
	if(anim_time_diff_us >= HEART_TIME){
		// end of animation
		anim_time_us = time_us_32();
	}
}

#define STARTUP_BRIGHT 0.2
#define STARTUP_TIME 700000
void led_anim_startup(){
	anim_time_diff_us = time_us_32()-anim_time_us;

	if(anim_time_diff_us <= STARTUP_TIME/6){
		color.raw			= 0;
		color.colors.red	= 255*STARTUP_BRIGHT;
		ws2812_put(color);
	}
	else if(anim_time_diff_us <= 2*STARTUP_TIME/6){
		color.raw			= 0;
		ws2812_put(color);
	}
	else if(anim_time_diff_us <= 3*STARTUP_TIME/6){
		color.raw			= 0;
		color.colors.green	= 255*STARTUP_BRIGHT;
		ws2812_put(color);
	}
	else if(anim_time_diff_us <= 4*STARTUP_TIME/6){
		color.raw			= 0;
		ws2812_put(color);
	}
	else if(anim_time_diff_us <= 5*STARTUP_TIME/6){
		color.raw			= 0;
		color.colors.blue	= 255*STARTUP_BRIGHT;
		ws2812_put(color);
	}
	else if(anim_time_diff_us < STARTUP_TIME){
		color.raw			= 0;
		ws2812_put(color);
	}
	
}





void led_update(){

	switch (actual_animation)
	{
		case LED_ANIM_STARTUP:
			led_anim_startup();
			break;

		case LED_ANIM_BLINK:
			led_anim_blink();
			break;

		case LED_ANIM_BLINK_IDLE:
			led_anim_blink_idle();
			break;
	
		case LED_ANIM_HEART:
			led_anim_heart();
			break;

		case LED_ANIM_BLINK_OF_DEAD:
			led_anim_blink_of_dead();
			break;

		default:

	}


}

void led_set_anim(led_animation_e anim){
	if(anim<LED_ANIM_NB){
		
		actual_animation = anim;

		anim_time_us = time_us_32();
		anim_time_diff_us = 0;
		// logg(LED, "Set animation number: %d\n", anim);
	}
	else{
		loge(LED, "Anim number is bad.\n");
	}
}

led_animation_e led_get_anim(){
	return actual_animation;
}

