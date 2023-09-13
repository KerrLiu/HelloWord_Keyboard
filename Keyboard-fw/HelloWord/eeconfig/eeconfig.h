#pragma once

#ifndef EEPROM_CONFIGURATIONS_H
#define EEPROM_CONFIGURATIONS_H

#include "HelloWord/Utils/Memory/random_flash_interface.h"
#include "configurations.h"

void eep_config_init();
void eep_config_update();

#endif