#include "aquisition.h"
#include "hardware/pwm.h"
#include "freq_meas.h"

#define MIN_FREQUENCY 50
#define MAX_FREQUENCY 5000
// static uint aquisition_slice_num;
static SemaphoreHandle_t wrap_sempahore;
static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
q15_t ticks_buffer[CHANNEL_NB][FREQ_DET_DMA_BUFFER_NUM];
float32_t ticks_buffer_f[CHANNEL_NB][FREQ_DET_DMA_BUFFER_NUM];

void wrap_irq()
{
	arm_copy_q15((q15_t *)freq_meas_dma_buffer(0), ticks_buffer[0], FREQ_DET_DMA_BUFFER_NUM);
	arm_copy_q15((q15_t *)freq_meas_dma_buffer(1), ticks_buffer[1], FREQ_DET_DMA_BUFFER_NUM);
	arm_copy_q15((q15_t *)freq_meas_dma_buffer(2), ticks_buffer[2], FREQ_DET_DMA_BUFFER_NUM);
	arm_copy_q15((q15_t *)freq_meas_dma_buffer(3), ticks_buffer[3], FREQ_DET_DMA_BUFFER_NUM);

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

void analyse_task(void *param)
{
	QueueHandle_t put_frequences_queue = *(QueueHandle_t *)param;

	wrap_sempahore = xSemaphoreCreateBinary();

	freq_meas_init();
	freq_meas_set_wrap_cb(wrap_irq);

	float32_t timer_freq = (float32_t)clock_get_hz(clk_sys);

	float32_t mean_f[CHAN_NUM];
	float32_t freq[CHAN_NUM];
	while (1)
	{
		if (xSemaphoreTake(wrap_sempahore, 10) == pdTRUE)
		{

			for (uint8_t chan = 0; chan < CHAN_NUM; chan++)
			{

				for (uint32_t n = 0; n < FREQ_DET_DMA_BUFFER_NUM; n++)
				{
					ticks_buffer_f[chan][n] = (float32_t)ticks_buffer[chan][n];
				}

				arm_mean_f32(ticks_buffer_f[chan], FREQ_DET_DMA_BUFFER_NUM, &mean_f[chan]);
				freq[chan] = timer_freq / mean_f[chan];
			}

			// TODO calibration
			freq[0] = scale_freq(freq[0], 9000, 14000, 1000, 300);
			freq[0] = freq_bounds(freq[0], MIN_FREQUENCY, MAX_FREQUENCY);
			freq[1] = scale_freq(freq[1], 9000, 15000, 1000, 300);
			freq[1] = freq_bounds(freq[1], MIN_FREQUENCY, MAX_FREQUENCY);
			freq[2] = scale_freq(freq[2], 25000, 37000, 1000, 300);
			freq[2] = freq_bounds(freq[2], MIN_FREQUENCY, MAX_FREQUENCY);
			freq[3] = scale_freq(freq[3], 46000, 41000, 1000, 300);
			freq[3] = freq_bounds(freq[3], MIN_FREQUENCY, MAX_FREQUENCY);

			if (xQueueSend(put_frequences_queue, freq, 0) != pdPASS)
			{
				loge(AQUISITION, "Cannot put to dds queue!");
			}
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
