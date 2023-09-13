#include "eeconfig.h"

extern EEPROM eeprom;
extern KeyboardConfig_t config;

void eep_config_init(){
  eeprom.Pull(0, config);
}

void eep_config_update(){
  eeprom.Push(0, config);
}

