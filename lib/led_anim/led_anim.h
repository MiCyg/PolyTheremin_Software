#ifndef __LED_ANIM__
#define __LED_ANIM__

#include "comlib.h"
#include "ws2812.h"

typedef enum led_animation_e
{
	LED_ANIM_STARTUP,
	LED_ANIM_BLINK_OF_DEAD,
	LED_ANIM_BLINK_IDLE,
	LED_ANIM_BLINK,
	LED_ANIM_RAINBOW,
	LED_ANIM_HEART,

	LED_ANIM_NB,
} led_animation_e;

void led_init();
void led_deinit();
void led_set_anim(led_animation_e anim);
led_animation_e led_get_anim();

#endif // __LED_ANIM__