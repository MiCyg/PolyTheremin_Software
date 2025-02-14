#include "core.h"
#include "led_anim.h"
#include "het_generator.h"
#include "aquisition.h"
#include "dds.h"

#define FETCH_COLOR COLOR_CYAN
void neofetch_message(){
	// TODO create custom pico board and update information, simplified logo display

	printf("\n");
	printf(COLOR_GREEN "         ...                . .         \n" NOCOLOR                         );
	printf(COLOR_GREEN "    ^~77??JJ??7!^.     :~77?J?J?77!^.   \n" NOCOLOR                         );
	printf(COLOR_GREEN "   .?YYYJJJJYYYYYJ^  .?YYYYYYJJJYYYY^   \n" NOCOLOR                         );
	printf(COLOR_GREEN "    ~YYYYJJ?77?JYYY. !5YYJ777?JYYYY7.   \n" NOCOLOR                         );
	printf(COLOR_GREEN "     ~YYYYYYYJ7~!?~  :77~!?JYYYYYY?:    \n" NOCOLOR                         );
	printf(COLOR_GREEN "      :7JYYYYYYJ:       7YYYYYYY?~.     " NOCOLOR "%s" NOCOLOR " %s\n", PROJECT_NAME, PROJECT_VERSION);
	printf(COLOR_GREEN "        .^!?7!~: " COLOR_RED " .... " COLOR_GREEN " .^!777~:        \n" NOCOLOR );
	printf(COLOR_RED "        ..:^^: .^~~!!~~^: :^^:.         " FETCH_COLOR "---------------------\n" NOCOLOR );
	printf(COLOR_RED "      .^~!!~:  ^!!!!!!!!~..^~!!~^       " FETCH_COLOR "OS:"         NOCOLOR " freeRTOS %s\n", tskKERNEL_VERSION_NUMBER);
	printf(COLOR_RED "      ~!~^:  ....:^^^^:::....:~!!^      " FETCH_COLOR "Board:"      NOCOLOR " %s\n",          PICO_BOARD);
	printf(COLOR_RED "      ^:. :^~~!~~^    :~~!!~~:..:^      " FETCH_COLOR "Build type:" NOCOLOR " %s\n",          PICO_CMAKE_BUILD_TYPE);
	printf(COLOR_RED "    :^  .~!!!!!!!!~  ^!!!!!!!!~. .^:    " FETCH_COLOR "Uptime:"     NOCOLOR " %ld[ms]\n",     time_us_32()/1000);
	printf(COLOR_RED "  .~!!: ^!!!!!!!!!~. ^!!!!!!!!!~ ^!!~.  " FETCH_COLOR "CPU:"        NOCOLOR " %s (%d)\n",     "Cortex M0+", configNUMBER_OF_CORES);
	printf(COLOR_RED "  ~!!!: ^!!!!!!!!!:   ~!!!!!!!!~ :!!!^  " FETCH_COLOR "Sys clock:"  NOCOLOR " %.0fkHz\n",     (double)(clock_get_hz(clk_sys))/1000);
	printf(COLOR_RED "  ^!!~.  ^~!!!!~^......:^~!!!~^.  ~!!^  " FETCH_COLOR "Flash:"      NOCOLOR " %dMB\n",        PICO_FLASH_SIZE_BYTES/1024/1024);
	printf(COLOR_RED "  .^~.     .:...^~~!!!~^:....  ...:~^   " FETCH_COLOR "SRAM:" NOCOLOR " %dkB\n", 0); // TODO any method to show ram usage?
	printf(COLOR_RED "     :~~~^.   .~!!!!!!!!!^   :~~!!^     \n" NOCOLOR                           );
	printf(COLOR_RED "     ~!!!!!^. :!!!!!!!!!!~ .~!!!!!!.    \n" NOCOLOR                           );
	printf(COLOR_RED "     :!!!!!!~. ^!!!!!!!!~..~!!!!!!^     \n" NOCOLOR                           );
	printf(COLOR_RED "      :~!!!!!^  .:^^^^:.  ^!!!!!~:      \n" NOCOLOR                           );
	printf(COLOR_RED "        .:^^^.  ..:::::.. .:^^:.        \n" NOCOLOR                           );
	printf(COLOR_RED "              .~!!!!!!!!!:              \n" NOCOLOR                           );
	printf(COLOR_RED "               .:^~~~~~^.               \n" NOCOLOR                           );
	printf(COLOR_RED "                    .                   \n" NOCOLOR                           );
	printf("\n");

}


void core_run()
{
	neofetch_message();

	led_init();
	led_set_anim(LED_ANIM_HEART);

	het_generator_init();

	QueueHandle_t aquisitionDdsQueue = xQueueCreate(16, sizeof(float32_t)*CHAN_NUM);
	aquisition_init(&aquisitionDdsQueue);
	dds_init(&aquisitionDdsQueue);

	vTaskDelete(NULL);
}