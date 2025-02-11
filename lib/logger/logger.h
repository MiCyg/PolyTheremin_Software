#ifndef __LOGGER__
#define __LOGGER__

#include "comlib.h"
#include "colors.h"
#include "hardware/clocks.h"

#define DEBUG_ENABLE		1
#define SPIN_LOCK_ENABLE	1
#define INFO_COLOR			COLOR_BLUE
#define WARN_COLOR			COLOR_YELLOW
#define ERR_COLOR			COLOR_RED



#if SPIN_LOCK_ENABLE == 1
	#include "pico/sync.h"
#endif
typedef enum debug_type_e{
	MAIN,
	CORE,
	THER,
	AQUISITION,
	FREQ_DET,
	HET_GEN,
	DDS,
	DAC,
	DECOR,
	TFLITE,
	LOGGER,
	LED,

	DEB_TYPE_NUM,
} debug_type_e;

static struct type_char_t{
	char * prefix;	
	bool enable;	
} _debug_prefixes[DEB_TYPE_NUM] __unused= {
	[MAIN]			= {.prefix="MAIN",		.enable=true	},
	[CORE]			= {.prefix="CORE",		.enable=true	},
	[THER]			= {.prefix="THEREMIN",	.enable=true	},
	[AQUISITION]	= {.prefix="AQST",		.enable=true	},
	[FREQ_DET]		= {.prefix="FREQDET",	.enable=true	},
	[HET_GEN]		= {.prefix="CLOCKGEN",	.enable=true	},
	[DDS]			= {.prefix="DDS",		.enable=true	},
	[DAC]			= {.prefix="DAC",		.enable=true	},
	[DECOR]			= {.prefix="DECOR",		.enable=true	},
	[TFLITE]		= {.prefix="TFLITE",	.enable=true	},
	[LOGGER]		= {.prefix="LOGGER",	.enable=true	},
	[LED]			= {.prefix="LED",		.enable=true	},
};

void logger_init();
void logger_deinit();
void logger_enable(debug_type_e type, bool enable);
void logger_test_colors();



#define LOG_TAB(tab)		for(uint8_t i=0;i<tab;i++)printf("-"); if(tab)printf(">")
#define LOG_CAT(cat)		printf("%s: ", cat)
#define LOG_COLOR(color)	printf("%s", color)
#define LOG_ENDCOLOR()	printf("%s", NOCOLOR)

void _logger_begin_block();
void _logger_end_block();

#if DEBUG_ENABLE == 1
#define logg(type, ...) 								\
	do {												\
		_logger_begin_block();							\
		if(type < DEB_TYPE_NUM){						\
			if(_debug_prefixes[type].enable){			\
				LOG_TAB(type);							\
				LOG_CAT(_debug_prefixes[type].prefix);	\
				printf(__VA_ARGS__);					\
			}											\
		}												\
		_logger_end_block();							\
	} while(0)
#else
	#define logg(type, ...) do {} while(0)
#endif

#if DEBUG_ENABLE == 1
#define logc(type, color, ...) 							\
	do {												\
		_logger_begin_block();							\
		if(type < DEB_TYPE_NUM){						\
			if(_debug_prefixes[type].enable){			\
				LOG_COLOR(color);						\
				LOG_TAB(type);							\
				LOG_CAT(_debug_prefixes[type].prefix);	\
				printf(__VA_ARGS__);					\
				LOG_ENDCOLOR();							\
			}											\
		}												\
		_logger_end_block();							\
	} while(0)
#else
	#define logc(type, ...) do {} while(0)
#endif

#if DEBUG_ENABLE == 1
#define logi(type, ...)									\
	do {												\
		_logger_begin_block();							\
		if(type < DEB_TYPE_NUM){						\
			if(_debug_prefixes[type].enable){			\
				LOG_COLOR(INFO_COLOR);					\
				LOG_TAB(type);							\
				LOG_CAT(_debug_prefixes[type].prefix);	\
				printf(__VA_ARGS__);					\
				LOG_ENDCOLOR();							\
			}											\
		}												\
		_logger_end_block();							\
	} while(0)
#else
	#define logi(type, ...) do {} while(0)
#endif

#if DEBUG_ENABLE == 1
#define loge(type, ...)									\
	do {												\
		_logger_begin_block();							\
		if(type < DEB_TYPE_NUM){						\
			if(_debug_prefixes[type].enable){			\
				LOG_COLOR(ERR_COLOR);					\
				LOG_TAB(type);							\
				LOG_CAT(_debug_prefixes[type].prefix);	\
				printf(__VA_ARGS__);					\
				LOG_ENDCOLOR();							\
			}											\
		}												\
		_logger_end_block();							\
	} while(0)
#else
	#define loge(type, ...) do {} while(0)
#endif

#if DEBUG_ENABLE == 1
#define logw(type, ...)									\
	do {												\
		_logger_begin_block();							\
		if(type < DEB_TYPE_NUM){						\
			if(_debug_prefixes[type].enable){			\
				LOG_COLOR(WARN_COLOR);				\
				LOG_TAB(type);							\
				LOG_CAT(_debug_prefixes[type].prefix);	\
				printf(__VA_ARGS__);					\
				LOG_ENDCOLOR();							\
			}											\
		}												\
		_logger_end_block();							\
	} while(0)
#else
	#define logw(type, ...) do {} while(0)
#endif

#if DEBUG_ENABLE == 1
#define log_hex(type, data, len) 						\
	do {												\
		_logger_begin_block();							\
		if(type < DEB_TYPE_NUM){						\
			if(_debug_prefixes[type].enable){			\
				LOG_TAB(type);							\
				LOG_CAT(_debug_prefixes[type].prefix);	\
				for (size_t i = 0; i < len; i++)		\
				{										\
					printf("%02X", data[i]);			\
				}										\
			}											\
		}												\
		printf("\n");									\
		_logger_end_block();							\
	} while(0)
#else
	#define log_hex(type, ..., ...) do {} while(0)
#endif

#endif // __LOGGER__