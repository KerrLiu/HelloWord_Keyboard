#include "hw_led.h"

void HWLed::SetRgbBufferByID(uint8_t _keyId, HWLed::Color_t _color, uint8_t _brightness)
{
	// To ensure there's no sequence zero bits, otherwise will case ws2812b protocol error.
	if (_color.b < 1) _color.b = 1;

	for (int i = 0; i < 8; i++)
	{
		rgbBuffer[_keyId][0][i] =
			((uint8_t) ((float) _color.g * _brightness / 100) >> brightnessPreDiv) & (0x80 >> i) ? WS_HIGH : WS_LOW;
		rgbBuffer[_keyId][1][i] =
			((uint8_t) ((float) _color.r * _brightness / 100) >> brightnessPreDiv) & (0x80 >> i) ? WS_HIGH : WS_LOW;
		rgbBuffer[_keyId][2][i] =
			((uint8_t) ((float) _color.b * _brightness / 100) >> brightnessPreDiv) & (0x80 >> i) ? WS_HIGH : WS_LOW;
	}
}

void HWLed::Init()
{
	for (uint8_t i = 0; i < LED_NUMBER; i++)
		SetRgbBufferByID(i, Color_t{0, 0, 0}, 0);
}

void HWLed::SyncLights()
{
	while (isRgbTxBusy);
	isRgbTxBusy = true;
	HAL_SPI_Transmit_DMA(&hspi2, (uint8_t*) rgbBuffer, LED_NUMBER * 24);
	while (isRgbTxBusy);
	isRgbTxBusy = true;
	HAL_SPI_Transmit_DMA(&hspi2, wsCommit, 64);
}

uint8_t HWLed::GetRgbBrightnessFactor(uint8_t _index)
{
	return rgbBrightnessFactor[_index];
}

void HWLed::SetRgbBrightnessFactor(uint8_t _index, uint8_t _value)
{
	rgbBrightnessFactor[_index] = _value > rgbBrightnessFactor[_index] ? _value : rgbBrightnessFactor[_index];
}

void HWLed::DecBrightnessFactor(uint8_t _index, uint8_t _dec){
	if (rgbBrightnessFactor[_index] > 0) rgbBrightnessFactor[_index] -= _dec;
}

void HWLed::SetSinRgbBufferByID(uint8_t _index, uint8_t _brightness){
	SetRgbBufferByID(_index, Color_t{(uint8_t)(HALF_FF * sin((angleCount + ANGLE_GAP * 0 + _index) * RADIAN_1 + HALF_PI) + HALF_FF), 
			(uint8_t)(HALF_FF * sin((angleCount + ANGLE_GAP * 1 + _index) * RADIAN_1 + HALF_PI) + HALF_FF), 
			(uint8_t)(HALF_FF * sin((angleCount + ANGLE_GAP * 2 + _index) * RADIAN_1 + HALF_PI) + HALF_FF)}, _brightness);
}

// -----------------------Lamp efficiency code----------------------

void HWLed::Update(HWKeyboard _keyboard){
	if(ledMode == 0){
		for (uint8_t i = 0; i < LED_NUMBER; i++)
			SetRgbBufferByID(i, Color_t{0, 0, 0}, 0);
	}else{
		angleCount += 4;
		if (angleCount > 3600) angleCount = 0;
		uint8_t index;
		uint8_t keyindex = 0;
		for(uint8_t i = 1; i < KEY_COLS - 1; i++){
			for(uint8_t j = 1; j < KEY_ROWS - 1; j++){
				index = LEDMAP[i][j];
				if(index == LED_VOID)
					continue;

				if(ledMode == 1){
					SetSinRgbBufferByID(index, brightness);
				}else if(ledMode == 2 || ledMode == 3){
					if(_keyboard.GetButtonStatus(keyindex)){
						if(ledMode == 2){
							SetRgbBrightnessFactor(index, brightness);
						}else if(ledMode == 3){
							SetRgbBrightnessFactor(index, brightness);

							if(LEDMAP[i][j - 1] != LED_VOID)
								SetRgbBrightnessFactor(LEDMAP[i][j - 1], brightness);

							if(LEDMAP[i][j + 1] != LED_VOID)
								SetRgbBrightnessFactor(LEDMAP[i][j + 1], brightness);

							if(LEDMAP[i - 1][j] != LED_VOID)
								SetRgbBrightnessFactor(LEDMAP[i - 1][j], brightness);

							if(LEDMAP[i + 1][j] != LED_VOID)
								SetRgbBrightnessFactor(LEDMAP[i + 1][j], brightness);
						}
					}
					SetSinRgbBufferByID(index, GetRgbBrightnessFactor(index));
					DecBrightnessFactor(index, 1);
					keyindex++;
				}else if(ledMode == 4){
					if (index == (angleCount / 4) % KEY_NUMBER)
						SetRgbBrightnessFactor(index, brightness);

					SetSinRgbBufferByID(index, GetRgbBrightnessFactor(index));
					DecBrightnessFactor(index, 2);
					_keyboard._DelayUs(200);
				}
			}
		}

		for(uint8_t i = KEY_NUMBER; i < LED_NUMBER; i++){
			SetSinRgbBufferByID(i, brightness);
		}
	}
	if(isNumLocked)
		SetRgbBufferByID(LED_Num, Color_t{200, 0, 0}, brightness);
	else
		SetRgbBufferByID(LED_Num, Color_t{0, 0, 0}, 0);

	if(isCapsLocked)
		SetRgbBufferByID(LED_Caps, Color_t{0, 200, 0}, brightness);
	else
		SetRgbBufferByID(LED_Caps, Color_t{0, 0, 0}, 0);

	if(isScrollLocked)
		SetRgbBufferByID(LED_Scro, Color_t{0, 0, 200}, brightness);
	else
		SetRgbBufferByID(LED_Scro, Color_t{0, 0, 0}, 0);

	SyncLights();
}

/* void HWLed::Update(HWKeyboard _keyboard) */
/* { */
/* 	if(ledMode == 0){ */
/* 		for (uint8_t i = 0; i < LED_NUMBER; i++) */
/* 			SetRgbBufferByID(i, Color_t{0, 0, 0}, 0); */

/* 		// _keyboard._DelayUs(1000000); */
/* 	} else { */
/* 		angleCount += 4; */
/* 		if (angleCount > 3600) angleCount = 0; */

/* 		// color_flag ? color_v++ : color_v --; */
/* 		// if (color_v > 254) color_flag = false; */
/* 		// else if (color_v < 1) color_flag = true; */

/* 		for (uint8_t i = 0; i < KEY_NUMBER; i++){ */
/* 			if(ledMode == 1){ */
/* 				SetSinRgbBufferByID(i, brightness); */
/* 			}else if (ledMode == 2 || ledMode == 3){ */
/* 				if(_keyboard.GetButtonStatus(i)){ */
/* 					if (ledMode == 2){ */
/* 						SetRgbBrightnessFactor(i, brightness); */
/* 					}else if (ledMode == 3){ */
/* 						uint8_t _index; */
/* 						for(uint8_t j = 0; j < 6; j++){ */
/* 							_index = keyNearMap[i][j]; */
/* 							if (_index != LED_VOID) SetRgbBrightnessFactor(_index, brightness); */
/* 						} */
/* 					} */
/* 				} */
/* 				SetSinRgbBufferByID(keyLEDMap[i], GetRgbBrightnessFactor(i)); */
/* 				DecBrightnessFactor(i, 1); */
/* 			}else if (ledMode == 4){ */
/* 				if (i == (angleCount / 4) % KEY_NUMBER) */
/* 					SetRgbBrightnessFactor(i, brightness); */
/* 				SetSinRgbBufferByID(i, GetRgbBrightnessFactor(i)); */
/* 				DecBrightnessFactor(i, 2); */
/* 				_keyboard._DelayUs(200); */
/* 			} */
/* 		} */
/* 		for (uint8_t i = KEY_NUMBER + 3; i < LED_NUMBER; i++) */
/* 		{ */
/* 			SetSinRgbBufferByID(i, brightness); */
/* 		} */
/* 	} */

/* 	if(isNumLocked) */
/* 		SetRgbBufferByID(LED_Num, Color_t{200, 0, 0}, brightness); */

/* 	if(isCapsLocked) */
/* 		SetRgbBufferByID(LED_Caps, Color_t{0, 200, 0}, brightness); */

/* 	if(isScrollLocked) */
/* 		SetRgbBufferByID(LED_Caps, Color_t{0, 0, 200}, brightness); */

/* 	SyncLights(); */
/* } */

