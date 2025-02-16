
#ifndef __CONFIG__
#define __CONFIG__

// Project info
#define PROJECT_NAME             "PolyTheremin"
#define PROJECT_VERSION          "V1.0.0"
#define PROJECT_VERSION_DESCRIBE "First working version"


#define GPIO_TEST       GPIO_DAC_CS2 

// Hardware configuration

// ================================
// ====== FREQUENCY DETECTOR ======
// Sampling rate can only calculate on hand equation:
// Ftimer = Fsys * FREQ_DET_TIMER_X_FRACTION / FREQ_DET_TIMER_Y_FRACTION
#define FREQ_DET_TIMER_X_FRACTION     8
#define FREQ_DET_TIMER_Y_FRACTION     62500

#define FREQ_DET_DMA_BUFFER_NUM       16

#define GPIO_DET_MEAS1      8
#define GPIO_DET_MEAS2      2
#define GPIO_DET_MEAS3      4
#define GPIO_DET_MEAS4      6


// ================================
// ===== HETERODYNE GENERAOTR =====
// fequency bounds
// ch1 536.5-478.8
// ch2 614.5-508.1
// ch3 544.7-484.5
// ch4 537.6-482.6
#define HET_GEN_PIO_INSTANCE pio1
#define HET_GEN0_GPIO        16
#define HET_GEN1_GPIO        10
#define HET_GEN2_GPIO        12
#define HET_GEN3_GPIO        14
#define HET_GEN0_FREQ        560000
#define HET_GEN1_FREQ        634000
#define HET_GEN2_FREQ        566000
#define HET_GEN3_FREQ        560000

// ================================
// ============ DDS/DAC ===========
#define DAC_SPI_INST        spi0
#define DAC_SPI_CLK_SPEED    (20*1000*1000)

#define GPIO_DAC_LDAC   17
#define GPIO_DAC_CLK    18
#define GPIO_DAC_TX     19
#define GPIO_DAC_CS1    21
#define GPIO_DAC_CS2    20 // I must change this because pinout is not match with the schematic


// Sampling rate can only calculate on hand equation:
// Ftimer = Fsys * DDS_TIMER_X_FRACTION / DDS_TIMER_Y_FRACTION
#define DDS_TIMER_X_FRACTION 8
#define DDS_TIMER_Y_FRACTION 50000

#define DDS_BUFF_SIZE 128
#define DDS_FREQ_CHANGE_FILER_SIZE 128

// ================================
// ======== USER INTERFACE ========
#define WS2812_PIO_INSTANCE   pio0
#define WS2812_IS_RGBW        false
#define WS2812_SPEED          800000
#define GPIO_UI_LED           22

#define GPIO_UI_BUTTON        23








#endif // __CONFIG__