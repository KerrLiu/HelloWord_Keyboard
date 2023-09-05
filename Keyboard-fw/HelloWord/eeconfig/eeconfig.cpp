#include "eeconfig.h"
#include "timer.h"

extern EEPROM eeprom;
extern KeyboardConfig_t config;

uint32_t g_eeprom_timer;

void eeprom_init(){
  g_eeprom_timer = 0;
}

void eeprom_read_to_cfg(){
  
}
void eeprom_write(){}
void eeprom_synctime(){}
void eeprom_task(){}

