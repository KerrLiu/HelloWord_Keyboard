#include "hw_led.h"

void HW_Led::SetRgbBufferByID(uint8_t _keyId, HW_Led::Color_t _color, float _brightness)
{
	// To ensure there's no sequence zero bits, otherwise will case ws2812b protocol error.
	if (_color.b < 1) _color.b = 1;

	for (int i = 0; i < 8; i++)
	{
		rgbBuffer[_keyId][0][i] =
			((uint8_t) ((float) _color.g * _brightness) >> brightnessPreDiv) & (0x80 >> i) ? WS_HIGH : WS_LOW;
		rgbBuffer[_keyId][1][i] =
			((uint8_t) ((float) _color.r * _brightness) >> brightnessPreDiv) & (0x80 >> i) ? WS_HIGH : WS_LOW;
		rgbBuffer[_keyId][2][i] =
			((uint8_t) ((float) _color.b * _brightness) >> brightnessPreDiv) & (0x80 >> i) ? WS_HIGH : WS_LOW;
	}
}

void HW_Led::SyncLights()
{
	while (isRgbTxBusy);
	isRgbTxBusy = true;
	HAL_SPI_Transmit_DMA(&hspi2, (uint8_t*) rgbBuffer, LED_NUMBER * 3 * 8);
	while (isRgbTxBusy);
	isRgbTxBusy = true;
	HAL_SPI_Transmit_DMA(&hspi2, wsCommit, 64);
}

// -----------------------Lamp efficiency code----------------------
void HW_Led::RespiratoryEffect(HW_Led::Color_t _color)
{
	for (uint8_t i = 0; i < LED_NUMBER; i++)
	{
		SetRgbBufferByID(i, _color, brightness);
	}
}

void HW_Led::TurnLight()
{
	for (uint8_t i = 0; i < LED_NUMBER; i++)
	{
		SetRgbBufferByID(i, Color_t{0, 0, 0}, 0);
	}
}

void HW_Led::OneButton(HWKeyboard _keyboard, uint8_t _color_v)
{
	uint8_t keyState;
	for (uint8_t i = 0; i < HWKeyboard::KEY_NUMBER; i++)
	{
		keyState = _keyboard.GetButtonStatus(i);
		SetRgbBufferByID(keyLEDMap[i], HW_Led::Color_t{(uint8_t)(keyState * _color_v), (uint8_t)(keyState * 20), (uint8_t)(keyState * 100)}, brightness);
	}
	for (uint8_t i = HWKeyboard::KEY_NUMBER; i < LED_NUMBER; i++){
		SetRgbBufferByID(i, HW_Led::Color_t{_color_v, 20, 100}, brightness);
	}
}

bool HW_Led::OneButtonRetention(HWKeyboard _keyboard, uint8_t _color_v)
{
	uint8_t keyState;
	for (uint8_t i = 0; i < HWKeyboard::KEY_NUMBER; i++)
	{
		keyState = _keyboard.GetButtonStatus(i);
		SetRgbBufferByID(keyLEDMap[i], HW_Led::Color_t{(uint8_t)(keyState * _color_v), (uint8_t)(keyState * 20), (uint8_t)(keyState * 100)}, brightness);
	}
	for (uint8_t i = HWKeyboard::KEY_NUMBER; i < LED_NUMBER; i++){
		SetRgbBufferByID(i, HW_Led::Color_t{_color_v, 20, 100}, brightness);
	}
	return keyState;
}

void HW_Led::ButtonRange(HWKeyboard _keyboard, uint8_t _color_v)
{
	uint8_t keyState;
	/* for (uint8_t i = 0; i < HWKeyboard::KEY_NUMBER; i++) */
	/* { */
	/* 	keyState = _keyboard.GetButtonStatus(i); */
	/* 	SetRgbBufferByID(keyLEDMap[i], HW_Led::Color_t{(uint8_t)(keyState * _color_v), (uint8_t)(keyState * 20), (uint8_t)(keyState * 100)}, brightness); */
	/* } */
	TurnLight();
	for (uint8_t i = HWKeyboard::KEY_NUMBER; i < LED_NUMBER; i++)
	{
		SetRgbBufferByID(i, HW_Led::Color_t{_color_v, 20, 100}, brightness);
	}
	for (uint8_t i = 0; i < HWKeyboard::KEY_NUMBER; i++)
	{
		keyState = _keyboard.GetButtonStatus(i);
		if (!keyState){
			continue;
		}
		for (uint8_t j = 0; j < 6; j++)
		{
			uint8_t index = keyNearMap[i][j];
			if(index != 127)
				SetRgbBufferByID(keyNearMap[i][j], HW_Led::Color_t{(uint8_t)(keyState * _color_v), (uint8_t)(keyState * 20), (uint8_t)(keyState * 100)}, brightness);
		}
	}
}
// -----------------------------------------------------------------

