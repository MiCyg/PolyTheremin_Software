
#ifndef __COMLIB__
#define __COMLIB__

#include "pico/stdlib.h"
#include "pico/error.h"
#include "hardware/gpio.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "logger.h"
#include "fixfloat.h"


#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>



#include "config.h"

#define gpio_toggle(gpio) gpio_put(gpio, !gpio_get(gpio));
#define panic_check(error_condition, message, ...) \
	do { \
		if (error_condition) { \
			panic("\033[1;31m> Location: %s:%d\n> Function: %s()\n> Note: " message "\033[0m", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
		} \
	} while (0)



#endif // __COMLIB__