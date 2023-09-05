#pragma once

#ifndef EEPROM_CONFIGURATIONS_H
#define EEPROM_CONFIGURATIONS_H

#include "HelloWord/Utils/Memory/random_flash_interface.h"
#include "configurations.h"
#include "hw_core.h"

void eeprom_init();
void eeprom_read_to_cfg();
void eeprom_write();
void eeprom_synctime();
void eeprom_task();

#endif