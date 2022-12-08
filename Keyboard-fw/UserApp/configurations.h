#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------- C Scope ---------------------------*/
#include <stdbool.h>
#include "stdint-gcc.h"


typedef enum configStatus_t
{
    CONFIG_RESTORE = 0,
    CONFIG_OK,
    CONFIG_COMMIT
} configStatus_t;


typedef struct KeyboardConfig_t
{
    configStatus_t configStatus;
    uint64_t serialNum;
    uint8_t keyMap[128];
    uint8_t led_Mode = 1;
	uint8_t led_brightness = 20;
    // int8_t filter_level = 5;
} KeyboardConfig_t;

extern KeyboardConfig_t config;


#ifdef __cplusplus
}
/*---------------------------- C++ Scope ---------------------------*/



#endif
#endif
