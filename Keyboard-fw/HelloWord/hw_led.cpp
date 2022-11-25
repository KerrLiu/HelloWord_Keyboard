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

float HWLed::GetRgbBrightnessFactor(uint8_t _index)
{
	return rgbBrightnessFactor[_index];
}

void HWLed::SetRgbBrightnessFactor(uint8_t _index, float _value)
{
	rgbBrightnessFactor[_index] = _value > rgbBrightnessFactor[_index] ? _value : rgbBrightnessFactor[_index];
}

void HWLed::DecBrightnessFactor(uint8_t _index, float _dec){
	if (rgbBrightnessFactor[_index] > 0) rgbBrightnessFactor[_index] -= _dec;
}

void HWLed::SetSinRgbBufferByID(uint8_t _index, float _brightness){
	SetRgbBufferByID(_index, Color_t{(uint8_t)(HALF_FF * sin((angleCount + ANGLE_GAP * 0 + _index) * RADIAN_1 + HALF_PI) + HALF_FF), 
			(uint8_t)(HALF_FF * sin((angleCount + ANGLE_GAP * 1 + _index) * RADIAN_1 + HALF_PI) + HALF_FF), 
			(uint8_t)(HALF_FF * sin((angleCount + ANGLE_GAP * 2 + _index) * RADIAN_1 + HALF_PI) + HALF_FF)}, _brightness);
}
// -----------------------Lamp efficiency code----------------------

void HWLed::Update(HWKeyboard _keyboard)
{
	if(ledMode == 0){
		for (uint8_t i = 0; i < LED_NUMBER; i++)
		{
			SetRgbBufferByID(i, Color_t{0, 0, 0}, 0);
		}
		SyncLights();
		_keyboard._DelayUs(1000000);
	} else {
		angleCount += 4;
		if (angleCount > 3600) angleCount = 0;

		color_flag ? color_v++ : color_v --;
		if (color_v > 254) color_flag = false;
		else if (color_v < 1) color_flag = true;

		for (uint8_t i = 0; i < LED_KEY_NUMBER; i++){
			if(ledMode == 1){
				SetSinRgbBufferByID(i, brightness);
			}else if (ledMode == 2 || ledMode == 3){
				if(_keyboard.GetButtonStatus(i)){
					if (ledMode == 2){
						SetRgbBrightnessFactor(i, brightness);
					}else if (ledMode == 3){
						for(uint8_t j = 0; j < 6; j++){
							uint8_t _index = keyNearMap[i][j];
							if (_index != 127) SetRgbBrightnessFactor(_index, brightness);
						}
					}
				}
				SetSinRgbBufferByID(keyLEDMap[i], GetRgbBrightnessFactor(i));
				DecBrightnessFactor(i, 0.01);
			}else if (ledMode == 4){
				if (i == (angleCount / 4) % LED_KEY_NUMBER)
					SetRgbBrightnessFactor(i, brightness);
				SetSinRgbBufferByID(i, GetRgbBrightnessFactor(i));
				DecBrightnessFactor(i, 0.02);
				_keyboard._DelayUs(200);
			}
		}
		for (uint8_t i = LED_KEY_NUMBER; i < LED_NUMBER; i++)
		{
			SetSinRgbBufferByID(i, brightness);
		}
		SyncLights();
	}
}

