#include "comlib.h"
#include "core.h"



#define PLL_SYS_KHZ (250*1000)
int main( void )
{
	bool stat;
	stat = set_sys_clock_khz(PLL_SYS_KHZ, false);
	panic_check(stat == false, "Cannot set clock frequency %d", PLL_SYS_KHZ);
    stat = clock_configure(clk_peri, 0, CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, PLL_SYS_KHZ * 1000, PLL_SYS_KHZ * 1000);
	panic_check(stat == false, "Cannot configure clock frequency %d", PLL_SYS_KHZ);
	
	stdio_init_all();

    logger_init();

	xTaskCreate(core_run, CORE_NAME, CORE_STACK_SIZE, NULL, 0, NULL);

    vTaskStartScheduler();
	
	while(1);
}