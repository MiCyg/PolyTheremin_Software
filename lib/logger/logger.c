
#include "logger.h"

#if SPIN_LOCK_ENABLE == 1
	static int _logger_sync_num;
	static spin_lock_t *_logger_sync_count;
#endif

void logger_init(){

	#if SPIN_LOCK_ENABLE == 1
		_logger_sync_num = spin_lock_claim_unused(false);
		if(_logger_sync_num == -1){
			logg(LOGGER, "Cannot claim spin lock for logger.");
		}
		if(_logger_sync_num)
		_logger_sync_count = spin_lock_init(_logger_sync_num) ;
	#endif
}

void logger_test_colors(){

	logg(LOGGER, "TEST COLORS!");
	logc(LOGGER, COLOR_BLACK, 			"COLOR_BLACK");
	logc(LOGGER, COLOR_RED, 			"COLOR_RED");
	logc(LOGGER, COLOR_GREEN, 			"COLOR_GREEN");
	logc(LOGGER, COLOR_ORANGE, 			"COLOR_ORANGE");
	logc(LOGGER, COLOR_BLUE, 			"COLOR_BLUE");
	logc(LOGGER, COLOR_PURPLE, 			"COLOR_PURPLE");
	logc(LOGGER, COLOR_CYAN, 			"COLOR_CYAN");
	logc(LOGGER, COLOR_LIGHT_GRAY, 		"COLOR_LIGHT_GRAY");
	logc(LOGGER, COLOR_DARK_GRAY, 		"COLOR_DARK_GRAY");
	logc(LOGGER, COLOR_LIGHT_RED, 		"COLOR_LIGHT_RED");
	logc(LOGGER, COLOR_LIGHT_GREEN, 	"COLOR_LIGHT_GREEN");
	logc(LOGGER, COLOR_YELLOW, 			"COLOR_YELLOW");
	logc(LOGGER, COLOR_LIGHT_BLUE, 		"COLOR_LIGHT_BLUE");
	logc(LOGGER, COLOR_LIGHT_PURPLE,	"COLOR_LIGHT_PURPLE");
	logc(LOGGER, COLOR_LIGHT_CYAN, 		"COLOR_LIGHT_CYAN");
	logc(LOGGER, COLOR_WHITE, 			"COLOR_WHITE");


}

void logger_enable(debug_type_e type, bool enable){
	_debug_prefixes[type].enable = enable;
}


void logger_deinit(){
	#if SPIN_LOCK_ENABLE == 1
		spin_lock_unclaim(_logger_sync_num);
	#endif
}





void _logger_begin_block(){
	#if SPIN_LOCK_ENABLE == 1
		spin_lock_unsafe_blocking(_logger_sync_count);
	#endif
}

void _logger_end_block(){
	#ifdef SPIN_LOCK_ENABLE
		spin_unlock_unsafe(_logger_sync_count);
	#endif
}

// #endif










