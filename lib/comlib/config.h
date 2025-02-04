
#ifndef __CONFIG__
#define __CONFIG__

// Project info
#define PROJECT_NAME             "PolyTheremin"
#define PROJECT_VERSION          "1.0.0"
#define PROJECT_VERSION_DESCRIBE "First version of PolyTheremin project"

// system Info

#define SYSTEM_OS          ""
#define SYSTEM_UPTIME      ""
#define SYSTEM_CPU         ""
#define SYSTEM_RAM         ""
#define SYSTEM_FLASH         ""
#define SYSTEM_         ""



// Hardware configuration

#define GPIO_POLYTHEREMIN_TEST 3
// ================================
// ====== FREQUENCY DETECTOR ======
// 4 channels of dma
// 4 channels of pwm
#define FREQ_DET_DMA_BUFFER_NUM             256
#define FREQ_DET_DMA_BUFFER_NUM_IN_BYTES    8

// Sampling rate can only calculate on hand equation:
// Ftimer = Fsys * FREQ_DET_TIMER_X_FRACTION / FREQ_DET_TIMER_Y_FRACTION
// please change these 4 values for changing sampling frequency future
#define FREQ_DET_FS                   2000 // proforma, but can be used
#define FREQ_DET_DELAY_US             500 // proforma, but can be used
#define FREQ_DET_TIMER_X_FRACTION     1
#define FREQ_DET_TIMER_Y_FRACTION     62500


#define GPIO_DET_MEAS1      6
#define GPIO_DET_MEAS2      4
#define GPIO_DET_MEAS3      2
#define GPIO_DET_MEAS4      8
#define GPIO_DET_MEAS_TEST  9
#define GPIO_DET_MEAS_TEST2 7

// ================================
// ===== HETERODYNE GENERAOTR =====
// fequency bounds
// ch1 536.5-478.8
// ch2 614.5-508.1
// ch3 544.7-484.5
// ch4 537.6-482.6
#define HET_GEN_PIO_INSTANCE pio0
#define HET_GEN0_GPIO        16
#define HET_GEN1_GPIO        10
#define HET_GEN2_GPIO        12
#define HET_GEN3_GPIO        14
#define HET_GEN0_FREQ        477000
#define HET_GEN1_FREQ        507000
#define HET_GEN2_FREQ        483000
#define HET_GEN3_FREQ        481000

// ================================
// ============ DDS/DAC ===========
#define GPIO_DDS_TEST 5
#define DAC_SPI_INST        spi0
#define DAC_SPI_CLK_SPEED    (2*1000*1000)

#define GPIO_DAC_LDAC    17
#define GPIO_DAC_CLK    18
#define GPIO_DAC_TX        19
#define GPIO_DAC_CS1    21
#define GPIO_DAC_CS2    20 // I must change this because pinout is not match with the schematic

// Sampling rate can only calculate on hand equation:
// Ftimer = Fsys * DDS_TIMER_X_FRACTION / DDS_TIMER_Y_FRACTION
// please change these 4 values for changing sampling frequency future
#define DDS_FS                 50000 // proforma, but can be used
#define DDS_DELAY_US         20    // proforma, but can be used
#define DDS_TIMER_X_FRACTION 16
#define DDS_TIMER_Y_FRACTION 40000

#define DDS_BUFF_SIZE 128

// ================================
// ======== USER INTERFACE ========
#define TICK_US_UI 10000

#define WS2812_PIO_INSTANCE   pio1
#define WS2812_SM_INSTANCE    0
#define WS2812_IS_RGBW        false
#define WS2812_SPEED          800000
#define GPIO_UI_LED           22

#define GPIO_UI_BUTTON        23



#endif // __CONFIG__