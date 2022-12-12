#include "common_inc.h"
/* #include "configurations.h" */
#include "HelloWord/hw_keyboard.h"
#include "HelloWord/hw_led.h"

#define LSB(_x) ((_x) & 0xFF)
#define MSB(_x) ((_x) >> 8)

/* Component Definitions -----------------------------------------------------*/
/* KeyboardConfig_t config; */
HWKeyboard keyboard(&hspi1);
HWLed hwled(&hspi2);;
/* EEPROM eeprom; */

// UpdateKeyboardHID State
enum Update_State : uint8_t
{
	NORMAL = 0, SENDING, SENDPASS, SENDED
};

const int16_t combinationKeyMap[2][16] = {
	{F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, SPACE, UP_ARROW, DOWN_ARROW, LEFT_GUI},	// combinationKey
	{MY_COMPUTER, DISPLAY_BRIGHTNESS_INC, DISPLAY_BRIGHTNESS_DEC, MEDIA_SELECT, SCAN_PREV_TRACK, SCAN_NEXT_TRACK, PLAY_PAUSE, SU_STOP, SU_VOLUME_INC, SU_VOLUME_DEC, SU_MUTE, CALCULATOR, KEYSET_LIGHTMODE, KEYSET_BRIGHTNESS_INC, KEYSET_BRIGHTNESS_DEC, KEYSET_LAYOUT_WIN_MAC}	// consumer code and custom code
};

uint8_t isKeyboardUpdate = SENDED;
bool isKeyDownCombination = false;
/* uint8_t filter_level = 1; */
uint8_t unFnLayout = 1;
uint8_t lastHidBuffer[KEY_REPORT_SIZE];
uint8_t report_ID = 1;
uint8_t report_flag = false;

void SendReportKeyboardHID(uint8_t* _HidBuffer)
{
	memcpy(lastHidBuffer, _HidBuffer, KEY_REPORT_SIZE);
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, _HidBuffer, KEY_REPORT_SIZE);
}

void SendReportRawHID(uint8_t* _HidBuffer)
{

}

void SendReportConsumerHID(uint8_t* _HidBuffer)
{
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, _HidBuffer, KEY_REPORT_SIZE);
	keyboard.ResetHidReportBuffer();
}

void FnCombinationFactory()
{
	uint8_t combinationKey_index = RESERVED;
	if(!isKeyDownCombination){
		uint8_t low, high;
		for(uint8_t i = 0; i < 16; i++){
			if(keyboard.KeyPressed((int16_t)combinationKeyMap[0][i])){
				combinationKey_index = combinationKeyMap[0][i];
				low = LSB(combinationKeyMap[1][i]);
				high = MSB(combinationKeyMap[1][i]);
				if(high < 0x60){
					report_ID = 3;
					report_flag = true;
					keyboard.ResetHidReportBuffer();
					keyboard.SetHidReportBuffer(1, low);
					keyboard.SetHidReportBuffer(2, high);
				}else{
					// isKeyboardUpdate = SENDPASS;
					switch(high){
						case 0x60 :
							hwled.SetLedMode((hwled.GetLedMode() + 1) % 5);
							break;
						case 0x61 :
							if (low){
								uint8_t tmp = hwled.GetBrightness() + 20;
								hwled.SetBrightness(MIN(100, tmp));
							}else{
								uint8_t tmp = hwled.GetBrightness() - 20;
								hwled.SetBrightness(MAX(20, tmp));
							}
							break;
						// case 0x62 :
						// 	if(low){
						// 		filter_level += 1;
						// 		filter_level = MIN(5, filter_level);
						// 	}else{
						// 		filter_level -= 1;
						// 		filter_level = MAX(1, filter_level);
						// 	}
						// 	break;
						case 0x63 :
							if(!low){
								unFnLayout = unFnLayout == 1 ? 3 : 1;
							}
							break;
					}
				}
				break;
			}
		}
	}
	isKeyDownCombination = keyboard.KeyPressed(UP_ARROW) | keyboard.KeyPressed(DOWN_ARROW) | keyboard.KeyPressed(LEFT_ARROW) | keyboard.KeyPressed(RIGHT_ARROW) | keyboard.KeyPressed(SPACE) | keyboard.KeyPressed(combinationKey_index);
}

void UpdateKeyboardHID()
{
	isKeyboardUpdate = SENDING;
	uint8_t layer = keyboard.FnPressed() ? 2 : unFnLayout;
	keyboard.Remap(layer);  // When Fn pressed use layer-2
	if(layer == 2)
	{
		FnCombinationFactory();
	}else{
		if(report_flag){
			report_ID = 3;
			keyboard.ResetHidReportBuffer();
			report_flag = false;
		}else{
			report_ID = 1;
		}
	}

	if (!isKeyDownCombination && memcmp(lastHidBuffer + 1, keyboard.GetHidReportBuffer(report_ID) + 1, KEY_REPORT_SIZE - 1) != 0) {
		// Report HID key states
		SendReportKeyboardHID(keyboard.GetHidReportBuffer(report_ID));
	}
	isKeyboardUpdate = SENDED;
}

/* Main Entry ----------------------------------------------------------------*/
void Main()
{
	/* eeprom.Pull(0, config); */
	/* if (config.configStatus != CONFIG_OK) */
	/* { */
	/* 	// Use default settings */
	/* 	config = KeyboardConfig_t{ */
	/* 		.configStatus = CONFIG_OK, */
	/* 			.serialNum=123, */
	/* 			.keyMap={}, */
	/* 			.light_mode=1, */
	/* 			.led_brightness=0.2, */
	/* 			.filter_level=5 */
	/* 	}; */
	/* 	memset(config.keyMap, -1, 128); */
	/* 	eeprom.Push(0, config); */
	/* } */
	/* if (config.light_mode < 1 || config.filter_level < 1){ */
	/* 	config.light_mode = 1; */
	/* 	config.led_brightness = 0.25; */
	/* 	config.filter_level = 5; */
	/* 	eeprom.Push(0, config); */
	/* } */

	// Keyboard Report Start
	HAL_TIM_Base_Start_IT(&htim4);

	while(true)
	{
		hwled.Update(keyboard);
	}
}

/* Event Callbacks -----------------------------------------------------------*/
extern "C" void OnTimerCallback() // 1000Hz callback
{
	keyboard.ScanKeyStates();  // Around 40us use 4MHz SPI clk
	// keyboard.ApplyDebounceFilter(100 * filter_level);
	keyboard.ApplyDebounceFilter(100); // DebounceFilter Default value is 100
	if(isKeyboardUpdate == SENDED){
		isKeyboardUpdate = NORMAL;
		UpdateKeyboardHID();
	}

	/*
	   uint8_t layer = keyboard.FnPressed() ? 2 : 1;
	   keyboard.Remap(layer);  // When Fn pressed use layer-2

	   if (is_Send && memcmp(lastHidBuffer + 1, keyboard.GetHidReportBuffer(report_ID) + 1, KEY_REPORT_SIZE - 1) != 0) {
	// Report HID key states
	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, keyboard.GetHidReportBuffer(report_ID), KEY_REPORT_SIZE);
	memcpy(lastHidBuffer, keyboard.GetHidReportBuffer(report_ID), KEY_REPORT_SIZE);
	report_ID++;
	if (report_ID > 3) report_ID = 1;
	lastHidBuffer[0] = report_ID;
	}
	*/
}


	extern "C"
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi)
{
	hwled.isRgbTxBusy = false;
}

	extern "C"
void HID_RxCpltCallback(uint8_t* _data)
{
	hwled.isNumLocked = _data[1] & 0x01? true: false;
	hwled.isCapsLocked = _data[1] & 0x02? true: false;
	hwled.isScrollLocked = _data[1] & 0x04? true: false;

}

	/* extern "C" */
/* void HID_OnEventOutCallback(uint8_t event_idx, uint8_t state) */
/* { */
	/* if (event_idx == 1) */
	/* { */
	/* 	keyboard.isCapsLocked = (state & 0b10) >> 1; */
	/* 	/1* keyboard.isScrollLocked = (state & 0b100) >> 2; *1/ */
	/* 	/1* keyboard.ledCtrler->isCapsChanged = true; *1/ */
	/* } */
/* } */
