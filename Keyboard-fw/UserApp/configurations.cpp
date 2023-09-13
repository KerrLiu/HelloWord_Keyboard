#include "configurations.h"

#ifdef EEPROM_CONFIG
#include "HelloWord/eeconfig/eeconfig.h"
#endif

#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
#endif

void config_init(){
#ifdef EEPROM_CONFIG
  eep_config_init();
#endif

if (config.configStatus != CONFIG_OK) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_config = {.enable = 1,
                               .mode = 0,
                               .hsv = {RGB_MATRIX_DEFAULT_HUE,
                                       RGB_MATRIX_DEFAULT_SAT,
                                       RGB_MATRIX_DEFAULT_VAL},
                               .speed = RGB_MATRIX_DEFAULT_SPD,
                               .flags = LED_FLAG_ALL};
#endif
    // Use default settings
    config = KeyboardConfig_t{.configStatus = CONFIG_COMMIT,
                              .filter_level = 5,
                              .unFnLayout = 1,
#ifdef RGB_MATRIX_ENABLE
                              .rgb_config_cfg = rgb_matrix_config,
#endif
    };
    config_update();
  }
}

void config_set(){
  if (config.configStatus == CONFIG_OK) {
    config.configStatus = CONFIG_COMMIT;
  }
}

void config_update(){
  if (config.configStatus == CONFIG_COMMIT) {
    config.configStatus = CONFIG_OK;

#ifdef RGB_MATRIX_ENABLE
    config.rgb_config_cfg = rgb_matrix_config;
#endif

#ifdef EEPROM_CONFIG
    eep_config_update();
#endif
  }
}