#include "button.h"

struct button_wrapper
{

	enum _button_state_e
	{
		WAIT_PRESS,
		SHORT_ACTION,
		PDEBOUNCING,
		KEEP,
		LONG_ACTION,
		WAIT_RELEASE,
		RELEASE,
		RDEBOUNCING,
	} button_state;
	uint32_t action_time;
	uint32_t bouncing_time_ms;
	uint32_t long_action_time_ms;

	void (*cb_function_press)(void *arg);
	void *cb_arg_press;
	void (*cb_function_lpress)(void *arg);
	void *cb_arg_lpress;

} button_vars;

void button_task()
{
	while (1)
	{
		switch (button_vars.button_state)
		{
		case WAIT_PRESS:
		{
			if (!gpio_get(GPIO_UI_BUTTON))
			{
				button_vars.button_state = SHORT_ACTION;
			}
			break;
		}
		case SHORT_ACTION:
		{
			button_vars.action_time = xTaskGetTickCount();
			if (button_vars.cb_function_press)
				(*button_vars.cb_function_press)(button_vars.cb_arg_press);
			button_vars.button_state = PDEBOUNCING;
			break;
		}
		case PDEBOUNCING:
		{
			if (xTaskGetTickCount() - button_vars.action_time < button_vars.bouncing_time_ms)
			{
				button_vars.button_state = KEEP;
			}
			break;
		}
		case KEEP:
		{
			if (!gpio_get(GPIO_UI_BUTTON))
			{
				if (xTaskGetTickCount() - button_vars.action_time < button_vars.long_action_time_ms)
				{
					button_vars.button_state = LONG_ACTION;
				}
			}
			else
			{
				button_vars.button_state = RELEASE;
			}

			break;
		}

		case LONG_ACTION:
		{
			button_vars.action_time = xTaskGetTickCount();
			if (button_vars.cb_function_lpress != NULL)
				(*button_vars.cb_function_lpress)(button_vars.cb_arg_lpress);
			button_vars.button_state = WAIT_RELEASE;
			break;
		}
		case WAIT_RELEASE:
		{
			if (gpio_get(GPIO_UI_BUTTON))
				button_vars.button_state = RELEASE;
			break;
		}
		case RELEASE:
		{
			button_vars.action_time = xTaskGetTickCount();
			button_vars.button_state = RDEBOUNCING;
			break;
		}
		case RDEBOUNCING:
		{
			if (xTaskGetTickCount() - button_vars.action_time < button_vars.bouncing_time_ms)
			{
				button_vars.button_state = WAIT_PRESS;
			}
		}
		}

		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void button_init()
{
	gpio_init(GPIO_UI_BUTTON);
	gpio_set_dir(GPIO_UI_BUTTON, false);
	gpio_set_pulls(GPIO_UI_BUTTON, true, false);
	button_vars.button_state = WAIT_RELEASE;
	button_vars.action_time = 0;
	button_vars.bouncing_time_ms = 50;
	button_vars.long_action_time_ms = 2000;

	xTaskCreate(button_task, "button", 1024, NULL, tskIDLE_PRIORITY, NULL);
}

void button_deinit()
{
	gpio_deinit(GPIO_UI_BUTTON);
}

void button_set_press_callback(void (*function)(void *), void *arg)
{
	button_vars.cb_function_press = function;
	button_vars.cb_arg_press = arg;
}

void button_set_lpress_callback(void (*function)(void *), void *arg)
{
	button_vars.cb_function_lpress = function;
	button_vars.cb_arg_lpress = arg;
}
