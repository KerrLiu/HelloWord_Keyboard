#include "hw_led.h"

void HWLed::SetRgbBufferByID(uint8_t _keyId, HWLed::Color_t _color, float _brightness)
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

void HWLed::SyncLights()
{
	while (isRgbTxBusy);
	isRgbTxBusy = true;
	HAL_SPI_Transmit_DMA(&hspi2, (uint8_t*) rgbBuffer, LED_NUMBER * 3 * 8);
	while (isRgbTxBusy);
	isRgbTxBusy = true;
	HAL_SPI_Transmit_DMA(&hspi2, wsCommit, 64);
}
// -----------------------Lamp efficiency code----------------------
void HWLed::RespiratoryEffect()
{
	while(ledMode == 1)
	{
		angleCount += 4;
		if (angleCount > 3600) {
			angleCount = 0;
		}
		for (uint8_t i = 0; i < LED_NUMBER; i++)
		{
			SetRgbBufferByID(i, Color_t{HALF_FF * sin((angleCount + ANGLE_GAP * 0 + i) * RADIAN_1 + HALF_PI) + HALF_FF, 
					HALF_FF * sin((angleCount + ANGLE_GAP * 1 + i) * RADIAN_1 + HALF_PI) + HALF_FF, 
					HALF_FF * sin((angleCount + ANGLE_GAP * 2 + i) * RADIAN_1 + HALF_PI) + HALF_FF}, brightness);
		}
		SyncLights();
		color_flag ? color_v ++ : color_v --;
		if (color_v > 254) color_flag = false;
		else if (color_v < 1) color_flag = true;
	}
}

void HWLed::TurnLight()
{
	for (uint8_t i = 0; i < LED_NUMBER; i++)
	{
		SetRgbBufferByID(i, Color_t{0, 0, 0}, 0);
	}
	SyncLights();
}

void HWLed::OneButton(uint8_t _index)
{
	if (_index == 254) return;
	color_v = 1;
	while(color_v > 0)
	{
		SetRgbBufferByID(_index, Color_t{color_v, 20, 100}, brightness);
		color_flag ? color_v += 5 : color_v -= 5;
		if (color_v > 254) color_flag = false;
		SyncLights();
	}
	TurnLight();
}

void HWLed::ButtonRange(uint8_t _index){
	if (_index == 254) return;
	color_v = 1;
	while(color_v > 0)
	{
		uint8_t index;
		for(uint8_t i = 0; i < 6; i++)
		{
			index = keyNearMap[_index][i];
			if(index != 127)
				SetRgbBufferByID(index, Color_t{color_v, 20, 100}, brightness);
		}
		color_flag ? color_v += 5 : color_v -= 5;
		if (color_v > 254) color_flag = false;
		SyncLights();
	}
	TurnLight();
}
// -----------------------------------------------------------------

