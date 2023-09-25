#include "hw_keyboard.h"
#include <cstring>

// uint8_t lastHidBuffer[HID_REPORT_SIZE]{};

inline void DelayUs(uint32_t _us) {
  for (int i = 0; i < _us; i++)
    for (int j = 0; j < 8; j++) // ToDo: tune this for different chips
      __NOP();
}

uint8_t *HWKeyboard::ScanKeyStates() {
  memset(spiBuffer, 0xFF, IO_NUMBER / 8 + 1);
  PL_GPIO_Port->BSRR = PL_Pin; // Latch

  spiHandle->pRxBuffPtr = (uint8_t *)spiBuffer;
  spiHandle->RxXferCount = IO_NUMBER / 8 + 1;
  __HAL_SPI_ENABLE(spiHandle);
  while (spiHandle->RxXferCount > 0U) {
    if (__HAL_SPI_GET_FLAG(spiHandle, SPI_FLAG_RXNE)) {
      /* read the received data */
      (*(uint8_t *)spiHandle->pRxBuffPtr) =
          *(__IO uint8_t *)&spiHandle->Instance->DR;
      spiHandle->pRxBuffPtr += sizeof(uint8_t);
      spiHandle->RxXferCount--;
    }
  }
  __HAL_SPI_DISABLE(spiHandle);

  PL_GPIO_Port->BRR = PL_Pin; // Sample
  return scanBuffer;
}

void HWKeyboard::ApplyDebounceFilter(uint32_t _filterTimeUs) {
  uint8_t debounceBuffer[IO_NUMBER / 8 + 1]{};
  memcpy(debounceBuffer, spiBuffer, IO_NUMBER >> 3 + 1);

  DelayUs(_filterTimeUs);
  ScanKeyStates();

  //uint8_t mask;
  for (int i = 0; i < IO_NUMBER >> 3 + 1; i++) {
    //mask = debounceBuffer[i] ^ spiBuffer[i];
    spiBuffer[i] |= debounceBuffer[i] ^ spiBuffer[i];
  }
}

/*void HWKeyboard::DebounceFilter() {
  memcpy(debounceBuffer, spiBuffer, IO_NUMBER >> 3 + 1);

  ScanKeyStates();

  uint8_t mask;
  for (int i = 0; i < IO_NUMBER >> 3 + 1; i++) {
    mask = debounceBuffer[i] ^ spiBuffer[i];
    spiBuffer[i] |= mask;
  }
}*/

uint8_t *HWKeyboard::Remap(uint8_t _layer) {
  int16_t index, bitIndex;

  memset(remapBuffer, 0, IO_NUMBER >> 3);
  for (int16_t i = 0; i < IO_NUMBER >> 3; i++) {
	int16_t baseIndex = i << 3;
    for (int16_t j = 0; j < 8; j++) {
      index = (int16_t)(keyMap[0][baseIndex + j] >> 3);
      bitIndex = (int16_t)(keyMap[0][baseIndex + j] % 8);
      if (scanBuffer[index] & (0x80 >> bitIndex))
        remapBuffer[i] |= 0x80 >> j;
    }
    remapBuffer[i] = ~remapBuffer[i];
  }
  memset(hidBuffer, 0, KEY_REPORT_SIZE);

  int i = 0, j = 0;
  while (8 * i + j < IO_NUMBER - 6) // TouchBar Number is 6
  // while (8 * i + j < IO_NUMBER)
  {
    for (j = 0; j < 8; j++) {
      /* index = (int16_t) (keyMap[_layer][8 * i + j] / 8 + 1); // +1 for
       * modifier */
      /* bitIndex = (int16_t) (keyMap[_layer][8 * i + j] % 8); */
      /* if (bitIndex < 0) */
      /* { */
      /* 	index -= 1; */
      /* 	bitIndex += 8; */
      /* } else if (index > 100) // Restrictions here */
      /* 	continue; */

      /* if (remapBuffer[i] & (0x80 >> j)) */
      /* 	hidBuffer[index + 1] |= 1 << (bitIndex); // +1 for Report-ID */

      if (remapBuffer[i] & (0x80 >> j)) {
        index = (int16_t)(keyMap[_layer][8 * i + j] / 8 + 1); // +1 for modifier
        bitIndex = (int16_t)(keyMap[_layer][8 * i + j] % 8);
        if (bitIndex < 0) {
          index -= 1;
          bitIndex += 8;
        } else if (index > 100) // Fn Key down pass
          continue;

        hidBuffer[index + 1] |= 1 << (bitIndex); // +1 for Report-ID
      }
    }
    i++;
    j = 0;
  }
  return hidBuffer;
}

bool HWKeyboard::FnPressed() { return remapBuffer[FN_NUMBER] & FN_OFFSET; }

bool HWKeyboard::GetButtonStatus(uint8_t _customId) {
  uint8_t index = _customId / 8;
  uint8_t bitIndex = _customId % 8;
  return remapBuffer[index] & (0x80 >> bitIndex);
}

uint8_t *HWKeyboard::GetHidReportBuffer(uint8_t _reportId) {
  switch (_reportId) {
  case 1:
    hidBuffer[0] = 1;
    return hidBuffer;
  case 2:
    hidBuffer[KEY_REPORT_SIZE] = 2;
    return hidBuffer + KEY_REPORT_SIZE;
  case 3:
    hidBuffer[0] = 3;
    return hidBuffer;
  default:
    return hidBuffer;
  }
}

void HWKeyboard::UpdateLastHidBuffer() {
  memcpy(lastHidBuffer, hidBuffer, KEY_REPORT_SIZE);
}

bool HWKeyboard::IsUpdateHidBuffer() {
  return memcmp(lastHidBuffer + 1, hidBuffer + 1, KEY_REPORT_SIZE - 1) != 0;
}

void HWKeyboard::SetHidReportBuffer(uint8_t _index, uint8_t _value) {
  hidBuffer[_index] = _value;
}

void HWKeyboard::ResetHidReportBuffer() {
  memset(hidBuffer, 0, HID_REPORT_SIZE);
  // hidBuffer[0] = _reportId;
}

bool HWKeyboard::KeyPressed(int16_t _key) {
  int index, bitIndex;

  if (_key < RESERVED) {
    index = _key / 8;
    bitIndex = (_key + 8) % 8;
  } else {
    index = _key / 8 + 1;
    bitIndex = _key % 8;
  }

  return hidBuffer[index + 1] & (1 << bitIndex);
}

void HWKeyboard::Press(int16_t _key) {
  int index, bitIndex;

  if (_key < RESERVED) {
    index = _key / 8;
    bitIndex = (_key + 8) % 8;
  } else {
    index = _key / 8 + 1;
    bitIndex = _key % 8;
  }

  hidBuffer[index + 1] |= (1 << bitIndex);
}

void HWKeyboard::Release(int16_t _key) {
  int index, bitIndex;

  if (_key < RESERVED) {
    // index = _key / 8;
    index = 0;
    bitIndex = (_key + 8) % 8;
  } else {
    index = _key / 8 + 1;
    bitIndex = _key % 8;
  }

  hidBuffer[index + 1] &= ~(1 << bitIndex);
}

#ifdef TOUCHBAR_ENABLE
uint8_t HWKeyboard::GetTouchBarState(uint8_t _id) {
  uint8_t tmp = (remapBuffer[10] & 0b00000001) << 5 |
                (remapBuffer[10] & 0b00000010) << 3 |
                (remapBuffer[10] & 0b00000100) << 1 |
                (remapBuffer[10] & 0b00001000) >> 1 |
                (remapBuffer[10] & 0b00010000) >> 3 |
                (remapBuffer[10] & 0b00100000) >> 5;
  return _id == 0 ? tmp : (tmp & (1 << (_id - 1)));
}
#endif

uint16_t HWKeyboard::KEYCODE2CONSUMER(int16_t key) {
	switch(key){
	case KB_SU_MY_COMPUTER:
	return MY_COMPUTER;
	case KB_SU_DIS_BRIGHTNESS_INC:
	return DISPLAY_BRIGHTNESS_INC;
	case KB_SU_DIS_BRIGHTNESS_DEC:
	return DISPLAY_BRIGHTNESS_DEC;
	case KB_SU_MEDIA_SELECT:
	return MEDIA_SELECT;
	case KB_SU_SCAN_PREV_TRACK:
	return SCAN_PREV_TRACK;
	case KB_SU_SCAN_NEXT_TRACK:
	return SCAN_NEXT_TRACK;
	case KB_SU_PLAY_PAUSE:
	return PLAY_PAUSE;
	case KB_SU_STOP:
	return SU_STOP;
	case KB_SU_VOLUME_INC:
	return SU_VOLUME_INC;
	case KB_SU_VOLUME_DEC:
	return SU_VOLUME_DEC;
	case KB_SU_MUTE:
	return SU_MUTE;
	case KB_SU_CALCULATOR:
	return CALCULATOR;
	case KB_KS_RGBMODE:
	return KEYSET_LIGHTMODE;
	case KB_KS_BRIGHT_INC:
	return KEYSET_BRIGHTNESS_INC;
	case KB_KS_BRIGHT_DEC:
	return KEYSET_BRIGHTNESS_DEC;
	case KB_KS_FILTER_INC:
	return KEYSET_FILTER_LEVEL_INC;
	case KB_KS_FILTER_DEC:
	return KEYSET_FILTER_LEVEL_DEC;
	case KB_KS_LAYER:
	return KEYSET_LAYOUT_WIN_MAC;
  case KB_KS_CFG_SV:
  return KEYSET_CONFIG_SAVE;
  case KB_KS_HUE_LOOP:
  return KEYSET_HSV_HUE_LOOP;
	default:
       return 0;
	}
}
