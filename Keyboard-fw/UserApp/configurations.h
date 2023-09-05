#pragma once

#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include "hw_core.h"

#if defined(__GNUC__)
#    define PACKED __attribute__((__packed__))
#else
#    define PACKED
#endif

#if defined(_MSC_VER)
#    pragma pack(push, 1)
#endif

// #ifdef __cplusplus
// extern "C" {
// #endif
// /*---------------------------- C Scope ---------------------------*/
// #include <stdbool.h>
// #include "stdint-gcc.h"

typedef enum configStatus_t
{
  CONFIG_RESTORE = 0,
  CONFIG_OK,
  CONFIG_COMMIT
} configStatus_t;

typedef struct PACKED
{
  configStatus_t configStatus;
  // uint64_t serialNum;
  // uint8_t keyMap[128];
  // uint8_t led_Mode = 0;
	// uint8_t led_brightness = 20;
  uint8_t filter_level = 5;
	uint8_t unFnLayout = 1;
  #ifdef RGB_MATRIX_ENABLE
  rgb_config_t rgb_config_cfg;
  #endif
} KeyboardConfig_t;

extern KeyboardConfig_t config;

#if defined(EEPROM_CONFIG)
void eep_config_init();
void eep_config_update();
#endif

void config_init();
void config_set();
void config_update();

// #ifdef __cplusplus
// }
// /*---------------------------- C++ Scope ---------------------------*/
// #endif

#if defined(_MSC_VER)
#    pragma pack(pop)
#endif

#endif
