#ifndef __BUTTON_WRAPPER__
#define __BUTTON_WRAPPER__

#include "comlib.h"

void button_init();
void button_deinit();

void button_set_press_callback(void (*function)(void *), void *arg);
void button_set_lpress_callback(void (*function)(void *), void *arg);

#endif // __BUTTON_WRAPPER__