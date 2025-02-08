
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



#include "config.h"

#define gpio_toggle(gpio) gpio_put(gpio, !gpio_get(gpio));




#endif // __COMLIB__