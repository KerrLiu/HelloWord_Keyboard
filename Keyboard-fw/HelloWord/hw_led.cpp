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
