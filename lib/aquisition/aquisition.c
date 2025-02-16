#include "aquisition.h"
#include "hardware/pwm.h"
#include "freq_meas.h"

#define MIN_FREQUENCY 50
#define MAX_FREQUENCY 5000
// static uint aquisition_slice_num;
static SemaphoreHandle_t wrap_sempahore;
static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
float32_t ticks_buffer[CHANNEL_NB][FREQ_DET_DMA_BUFFER_NUM];

static uint8_t chan;
static uint16_t idx;
void wrap_irq()
{
	for (chan = 0; chan < CHANNEL_NB; chan++)
	{
		for (idx = 0; idx < FREQ_DET_DMA_BUFFER_NUM; idx++)
		{
			ticks_buffer[chan][idx] = (float32_t)freq_meas_dma_buffer(chan)[idx];
		}
	}

	xSemaphoreGiveFromISR(wrap_sempahore, &xHigherPriorityTaskWoken);
}

inline float32_t scale_freq(float32_t in, float32_t in_min, float32_t in_max, float32_t out_min, float32_t out_max)
{
	// TODO prevention from max min values
	// if(in < in_min) return out_min;
	// if(in > in_max) return out_max;
	return (out_max - out_min) / (in_max - in_min) * (in - in_min) + out_min;
}

inline float32_t freq_bounds(float32_t in, float32_t min, float32_t max)
{
	if (in > max)
		return max;
	if (in < min)
		return min;
	return in;
}


typedef struct calibration_t
{
	float32_t in_min;
	float32_t in_max;
	float32_t out_min;
	float32_t out_max;
}calibration_t;

calibration_t frequency_calibration[CHANNEL_NB]=
{
	{.in_min=20000, .in_max=25000,.out_min=100, .out_max=500 },
	{.in_min=20000, .in_max=25000,.out_min=100, .out_max=500 },
	{.in_min=20000, .in_max=25000,.out_min=100, .out_max=500 },
	{.in_min=20000, .in_max=25000,.out_min=100, .out_max=500 }
};




void analyse_task(void *param)
{
	QueueHandle_t put_frequences_queue = *(QueueHandle_t *)param;

	wrap_sempahore = xSemaphoreCreateBinary();

	freq_meas_init();
	freq_meas_set_wrap_cb(wrap_irq);

	float32_t timer_freq = (float32_t)clock_get_hz(clk_sys);

	float32_t freq[CHAN_NUM];
	int i = 0;
	while (1)
	{
		if (xSemaphoreTake(wrap_sempahore, 10) == pdTRUE)
		{
			for (uint8_t chan = 0; chan < CHAN_NUM; chan++)
			{
				// arm_clip_f32(ticks_buffer[chan], ticks_buffer[chan], FREQ_DET_MIN_TICKS, FREQ_DET_MAX_TICKS, FREQ_DET_DMA_BUFFER_NUM);
				arm_mean_f32(ticks_buffer[chan], FREQ_DET_DMA_BUFFER_NUM, &freq[chan]);
				freq[chan] = timer_freq / freq[chan];
				freq[chan] = scale_freq(freq[chan], 
					frequency_calibration[chan].in_min, 
					frequency_calibration[chan].in_max, 
					frequency_calibration[chan].out_min, 
					frequency_calibration[chan].out_max
				);
				freq[chan] = freq_bounds(freq[chan], MIN_FREQUENCY, MAX_FREQUENCY);
				
			}
			
			if(i%100 == 0)
			{
				// for (uint16_t idx = 0; idx < FREQ_DET_DMA_BUFFER_NUM; idx++)
				// {
				// 	// logg(AQUISITION, "ticks %.3f %.3f %.3f %.3f", (double)ticks_buffer[0][idx], (double)ticks_buffer[1][idx], (double)ticks_buffer[2][idx], (double)ticks_buffer[3][idx]);
				// }
				logg(AQUISITION, "freqs: %10.3f %10.3f %10.3f %10.3f", (double)freq[3], (double)freq[2], (double)freq[1], (double)freq[0]);
			}
			
			
			if (xQueueSend(put_frequences_queue, freq, 0) != pdPASS)
			{
				loge(AQUISITION, "Cannot put to dds queue!");
			}
			i++;
		}
	}

	vTaskDelete(NULL);
}

void aquisition_init(QueueHandle_t *dds_queue)
{
	logi(AQUISITION, "Create analyse task");

	xTaskCreate(analyse_task, "analyse", 1024, dds_queue, 0, NULL);
}

void aquisition_deinit()
{
	logi(AQUISITION, "Deinit");
	// TODO
}
