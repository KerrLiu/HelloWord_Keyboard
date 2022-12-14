#include <cstring>
#include "hw_keyboard.h"


inline void DelayUs(uint32_t _us)
{
	for (int i = 0; i < _us; i++)
		for (int j = 0; j < 8; j++)  // ToDo: tune this for different chips
			__NOP();
}


uint8_t* HWKeyboard::ScanKeyStates()
{
	memset(spiBuffer, 0xFF, IO_NUMBER / 8 + 1);
	PL_GPIO_Port->BSRR = PL_Pin; // Latch

	spiHandle->pRxBuffPtr = (uint8_t*) spiBuffer;
	spiHandle->RxXferCount = IO_NUMBER / 8 + 1;
	__HAL_SPI_ENABLE(spiHandle);
	while (spiHandle->RxXferCount > 0U)
	{
		if (__HAL_SPI_GET_FLAG(spiHandle, SPI_FLAG_RXNE))
		{
			/* read the received data */
			(*(uint8_t*) spiHandle->pRxBuffPtr) = *(__IO uint8_t*) &spiHandle->Instance->DR;
			spiHandle->pRxBuffPtr += sizeof(uint8_t);
			spiHandle->RxXferCount--;
		}
	}
	__HAL_SPI_DISABLE(spiHandle);

	PL_GPIO_Port->BRR = PL_Pin; // Sample
	return scanBuffer;
}

void HWKeyboard::_DelayUs(uint32_t _delayUs)
{
	DelayUs(_delayUs);
}

void HWKeyboard::ApplyDebounceFilter(uint32_t _filterTimeUs)
{
	memcpy(debounceBuffer, spiBuffer, IO_NUMBER / 8 + 1);

	DelayUs(_filterTimeUs);
	ScanKeyStates();

	uint8_t mask;
	for (int i = 0; i < IO_NUMBER / 8 + 1; i++)
	{
		mask = debounceBuffer[i] ^ spiBuffer[i];
		spiBuffer[i] |= mask;
	}
}

uint8_t* HWKeyboard::Remap(uint8_t _layer)
{
	int16_t index, bitIndex;

	memset(remapBuffer, 0, IO_NUMBER / 8);
	for (int16_t i = 0; i < IO_NUMBER / 8; i++)
	{
		for (int16_t j = 0; j < 8; j++)
		{
			index = (int16_t) (keyMap[0][i * 8 + j] / 8);
			bitIndex = (int16_t) (keyMap[0][i * 8 + j] % 8);
			if (scanBuffer[index] & (0x80 >> bitIndex))
				remapBuffer[i] |= 0x80 >> j;
		}
		remapBuffer[i] = ~remapBuffer[i];
	}

	memset(hidBuffer, 0, KEY_REPORT_SIZE);

	int i = 0, j = 0;
	while (8 * i + j < IO_NUMBER - 6) // TouchBar Number is 6
	{
		for (j = 0; j < 8; j++)
		{
			/* index = (int16_t) (keyMap[_layer][8 * i + j] / 8 + 1); // +1 for modifier */
			/* bitIndex = (int16_t) (keyMap[_layer][8 * i + j] % 8); */
			/* if (bitIndex < 0) */
			/* { */
			/* 	index -= 1; */
			/* 	bitIndex += 8; */
			/* } else if (index > 100) // Restrictions here */
			/* 	continue; */
            
			/* if (remapBuffer[i] & (0x80 >> j)) */
			/* 	hidBuffer[index + 1] |= 1 << (bitIndex); // +1 for Report-ID */

			if (remapBuffer[i] & (0x80 >> j)){
				index = (int16_t) (keyMap[_layer][8 * i + j] / 8 + 1); // +1 for modifier
				bitIndex = (int16_t) (keyMap[_layer][8 * i + j] % 8);
				if (bitIndex < 0)
				{
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


bool HWKeyboard::FnPressed()
{
	return remapBuffer[FN_NUMBER] & FN_OFFSET;
}

bool HWKeyboard::GetButtonStatus(uint8_t _customId)
{
	uint8_t index = _customId / 8;
	uint8_t bitIndex = _customId % 8;
	return remapBuffer[index] & (0x80 >> bitIndex);
}

uint8_t* HWKeyboard::GetHidReportBuffer(uint8_t _reportId)
{
	switch (_reportId)
	{
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

void HWKeyboard::SetHidReportBuffer(uint8_t _index, uint8_t _value)
{
	hidBuffer[_index] = _value;
}

void HWKeyboard::ResetHidReportBuffer()
{
	memset(hidBuffer, 0, HID_REPORT_SIZE);
	// hidBuffer[0] = _reportId;
}

bool HWKeyboard::KeyPressed(int16_t _key)
{
	int index, bitIndex;

	if (_key < RESERVED)
	{
		index = _key / 8;
		bitIndex = (_key + 8) % 8;
	} else
	{
		index = _key / 8 + 1;
		bitIndex = _key % 8;
	}

	return hidBuffer[index + 1] & (1 << bitIndex);
}


void HWKeyboard::Press(int16_t _key)
{
	int index, bitIndex;

	if (_key < RESERVED)
	{
		index = _key / 8;
		bitIndex = (_key + 8) % 8;
	} else
	{
		index = _key / 8 + 1;
		bitIndex = _key % 8;
	}

	hidBuffer[index + 1] |= (1 << bitIndex);
}


void HWKeyboard::Release(int16_t _key)
{
	int index, bitIndex;

	if (_key < RESERVED)
	{
		index = _key / 8;
		bitIndex = (_key + 8) % 8;
	} else
	{
		index = _key / 8 + 1;
		bitIndex = _key % 8;
	}

	hidBuffer[index + 1] &= ~(1 << bitIndex);
}


uint8_t HWKeyboard::GetTouchBarState(uint8_t _id)
{
	uint8_t tmp = (remapBuffer[10] & 0b00000001) << 5 |
		(remapBuffer[10] & 0b00000010) << 3 |
		(remapBuffer[10] & 0b00000100) << 1 |
		(remapBuffer[10] & 0b00001000) >> 1 |
		(remapBuffer[10] & 0b00010000) >> 3 |
		(remapBuffer[10] & 0b00100000) >> 5;
	return _id == 0 ? tmp : (tmp & (1 << (_id - 1)));
}


