#include "common_inc.h"
/* #include "configurations.h" */
#include "HelloWord/hw_keyboard.h"
#include "HelloWord/hw_led.h"


/* Component Definitions -----------------------------------------------------*/
/* KeyboardConfig_t config; */
HWKeyboard keyboard(&hspi1);
HWLed hwled(&hspi2);;
/* EEPROM eeprom; */

bool isKeyDownCombination = false;
uint8_t key_speed_level = 5;
uint8_t lastHidBuffer[HWKeyboard::KEY_REPORT_SIZE] = {0};


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
	/* 			.key_speed_level=5 */
	/* 	}; */
	/* 	memset(config.keyMap, -1, 128); */
	/* 	eeprom.Push(0, config); */
	/* } */
	/* if (config.light_mode < 1 || config.key_speed_level < 1){ */
	/* 	config.light_mode = 1; */
	/* 	config.led_brightness = 0.25; */
	/* 	config.key_speed_level = 5; */
	/* 	eeprom.Push(0, config); */
	/* } */

	// Keyboard Report Start
	HAL_TIM_Base_Start_IT(&htim4);
	
	/*---- This is RGB effect ----*/
	while(true)
	{
		switch (hwled.GetLedMode()) {
			case 0 :
				hwled.TurnLight();
				break;
			case 1:
				hwled.RespiratoryEffect();
				break;
			case 2:
				hwled.OneButton(keyboard.GetKeyIndex());
				break;
			case 3:
				hwled.ButtonRange(keyboard.GetKeyIndex());
				break;
			case 4:
				hwled.TurnLight();
				break;
			case 5:
				hwled.TurnLight();
				break;
		}
	}
}

/* Event Callbacks -----------------------------------------------------------*/
extern "C" void OnTimerCallback() // 1000Hz callback
{
	bool is_Send = true;
	keyboard.ScanKeyStates();  // Around 40us use 4MHz SPI clk
	keyboard.ApplyDebounceFilter(20 * key_speed_level); // DebounceFilter Default value is 100
	uint8_t layer = keyboard.FnPressed() ? 2 : 1;
	keyboard.Remap(layer);  // When Fn pressed use layer-2

	if (layer == 2 && !isKeyDownCombination){
		if (keyboard.KeyPressed(HWKeyboard::SPACE)) {
			is_Send = false;
			uint8_t tmp = hwled.GetLedMode();
			hwled.SetLedMode((tmp + 1) % 6);
		}else if (keyboard.KeyPressed(HWKeyboard::UP_ARROW)) {
			is_Send = false;
			float tmp = hwled.GetBrightness() + 0.25;
			hwled.SetBrightness(MIN(1, tmp));
		}else if (keyboard.KeyPressed(HWKeyboard::DOWN_ARROW)) {
			is_Send = false;
			float tmp = hwled.GetBrightness() - 0.25;
			hwled.SetBrightness(MAX(0.25, tmp));
		}else if (keyboard.KeyPressed(HWKeyboard::LEFT_ARROW)) {
			is_Send = false;
			key_speed_level += 1;
			key_speed_level = MIN(6, key_speed_level);	
		}else if (keyboard.KeyPressed(HWKeyboard::RIGHT_ARROW)) {
			is_Send = false;
			key_speed_level -= 1;
			key_speed_level = MAX(1, key_speed_level);	
		}
	}
	isKeyDownCombination = keyboard.KeyPressed(HWKeyboard::UP_ARROW) | keyboard.KeyPressed(HWKeyboard::DOWN_ARROW) | keyboard.KeyPressed(HWKeyboard::LEFT_ARROW) | keyboard.KeyPressed(HWKeyboard::RIGHT_ARROW) | keyboard.KeyPressed(HWKeyboard::SPACE);
	if (is_Send && memcmp(lastHidBuffer + 1, keyboard.GetHidReportBuffer(1) + 1, HWKeyboard::KEY_REPORT_SIZE - 1) != 0) {
		// Report HID key states
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, keyboard.GetHidReportBuffer(1), HWKeyboard::KEY_REPORT_SIZE);
	}
	memcpy(lastHidBuffer, keyboard.GetHidReportBuffer(1), HWKeyboard::KEY_REPORT_SIZE);
	/* uint8_t voidHidBuffer[HWKeyboard::HID_REPORT_SIZE] = {0}; */
	/* USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, voidHidBuffer, HWKeyboard::KEY_REPORT_SIZE); */
}


	extern "C"
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi)
{
	hwled.isRgbTxBusy = false;
}

	extern "C"
void HID_RxCpltCallback(uint8_t* _data)
{

}

	extern "C"
void HID_OnEventOutCallback(uint8_t event_idx, uint8_t state)
{
	if (event_idx == 1)
	{
		keyboard.isCapsLocked = (state & 0b10) >> 1;
		/* keyboard.isScrollLocked = (state & 0b100) >> 2; */
		/* keyboard.ledCtrler->isCapsChanged = true; */
	}
}
