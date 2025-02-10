#include "comlib.h"
#include "core.h"


#define PLL_SYS_KHZ (250*1000)
int main( void )
{

	bool stat = set_sys_clock_khz(PLL_SYS_KHZ, false);
	panic_check(stat == false, "Cannot set clock frequency");

    clock_configure(
        clk_peri,
        0,                                                // No glitchless mux
        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, // System PLL on AUX mux
        PLL_SYS_KHZ * 1000,                               // Input frequency
        PLL_SYS_KHZ * 1000                                // Output (must be same as no divider)
    );
	
	stdio_init_all();

    logger_init();

	xTaskCreate(core_run, CORE_NAME, CORE_STACK_SIZE, NULL, 0, NULL);

    vTaskStartScheduler(); // start FreeRTOS
	
	while(1);
}