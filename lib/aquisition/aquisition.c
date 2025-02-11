#include "aquisition.h"
#include "hardware/pwm.h"
#include "freq_meas.h"



// static uint aquisition_slice_num;
static SemaphoreHandle_t wrap_sempahore;
static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
q15_t ticks_buffer[CHANNEL_NB][FREQ_DET_DMA_BUFFER_NUM];
float32_t ticks_buffer_f[CHANNEL_NB][FREQ_DET_DMA_BUFFER_NUM];




void wrap_irq()
{
	// gpio_toggle(GPIO_TEST);
	arm_copy_q15((q15_t*)freq_meas_dma_buffer(0), ticks_buffer[0], FREQ_DET_DMA_BUFFER_NUM);
	arm_copy_q15((q15_t*)freq_meas_dma_buffer(1), ticks_buffer[1], FREQ_DET_DMA_BUFFER_NUM);
	arm_copy_q15((q15_t*)freq_meas_dma_buffer(2), ticks_buffer[2], FREQ_DET_DMA_BUFFER_NUM);
	arm_copy_q15((q15_t*)freq_meas_dma_buffer(3), ticks_buffer[3], FREQ_DET_DMA_BUFFER_NUM);

	xSemaphoreGiveFromISR(wrap_sempahore, &xHigherPriorityTaskWoken);
	// gpio_toggle(GPIO_TEST);
}



void analyse_task(void* param)
{
	QueueHandle_t put_frequences_queue = *(QueueHandle_t*)param;

	wrap_sempahore = xSemaphoreCreateBinary();

	freq_meas_init();
	freq_meas_set_wrap_cb(wrap_irq);

	float32_t timer_freq = (float32_t)clock_get_hz(clk_sys);

	int i = 0;
	float32_t mean_f[CHAN_NUM];
	float32_t freq[CHAN_NUM];
	while(1)
	{
		if(xSemaphoreTake( wrap_sempahore, 100 ) == pdTRUE)
		{
			if(i%10 == 0)
			{
				gpio_toggle(GPIO_TEST);

				for (uint8_t chan = 0; chan < CHAN_NUM; chan++)
				{
				
					for (uint32_t n = 0; n < FREQ_DET_DMA_BUFFER_NUM; n++)
					{
						ticks_buffer_f[chan][n] = (float32_t)ticks_buffer[chan][n];
					}
					
					arm_mean_f32(ticks_buffer_f[chan], FREQ_DET_DMA_BUFFER_NUM, &mean_f[chan]);
					freq[chan] = timer_freq / mean_f[chan];
					

					
				}
				
				if(xQueueSend(put_frequences_queue, freq, 0) != pdPASS)
				{
					loge(AQUISITION, "Cannot put to dds queue!\n");
				}
				gpio_toggle(GPIO_TEST);
				


			}

			i++;
		}
	}

	vTaskDelete(NULL);


}



void aquisition_init(QueueHandle_t *dds_queue)
{
	logg(AQUISITION, "Create analyse task\n");

	xTaskCreate(analyse_task, "analyse", 1024, dds_queue, 1, NULL);
	
}

void aquisition_deinit()
{
	logg(AQUISITION, "Deinit\n");
	// TODO
}
