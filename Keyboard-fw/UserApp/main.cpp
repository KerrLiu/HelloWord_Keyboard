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
uint8_t key_speed_level = 2;
uint8_t lastHidBuffer[KEY_REPORT_SIZE] = {0};
uint8_t report_ID = 1;
bool report_flag = false;


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
	
	while(true)
	{
		hwled.Update(keyboard);
	}
}

/* void FnCombination() */
/* { */

/* } */

/* Event Callbacks -----------------------------------------------------------*/
extern "C" void OnTimerCallback() // 1000Hz callback
{
	bool is_Send = true;
	keyboard.ScanKeyStates();  // Around 40us use 4MHz SPI clk
	keyboard.ApplyDebounceFilter(100 * key_speed_level); // DebounceFilter Default value is 100
	uint8_t layer = keyboard.FnPressed() ? 2 : 1;
	keyboard.Remap(layer);  // When Fn pressed use layer-2

	if (layer == 2 && !isKeyDownCombination){
		if (keyboard.KeyPressed(SPACE)) {
			is_Send = false;
			uint8_t tmp = hwled.GetLedMode();
			hwled.SetLedMode((tmp + 1) % 6);
		}else if (keyboard.KeyPressed(UP_ARROW)) {
			is_Send = false;
			float tmp = hwled.GetBrightness() + 0.25;
			hwled.SetBrightness(MIN(1, tmp));
		}else if (keyboard.KeyPressed(DOWN_ARROW)) {
			is_Send = false;
			float tmp = hwled.GetBrightness() - 0.25;
			hwled.SetBrightness(MAX(0.25, tmp));
		}else if (keyboard.KeyPressed(LEFT_ARROW)) {
			is_Send = false;
			key_speed_level += 1;
			key_speed_level = MIN(5, key_speed_level);	
		}else if (keyboard.KeyPressed(RIGHT_ARROW)) {
			is_Send = false;
			key_speed_level -= 1;
			key_speed_level = MAX(1, key_speed_level);	
		}else if(keyboard.KeyPressed(F1)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			keyboard.SetHidReportBuffer(1, 0x94);
			keyboard.SetHidReportBuffer(2, 0x01);
			report_flag = true;
		}else if(keyboard.KeyPressed(F2)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			/* keyboard.SetHidReportBuffer(1, 0x23); */
			/* keyboard.SetHidReportBuffer(2, 0x02); */
			keyboard.SetHidReportBuffer(1, 0x6F);
			report_flag = true;
		}else if(keyboard.KeyPressed(F3)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			/* keyboard.SetHidReportBuffer(1, 0x8A); */
			/* keyboard.SetHidReportBuffer(2, 0x01); */
			keyboard.SetHidReportBuffer(1, 0x70);
			report_flag = true;
		}else if(keyboard.KeyPressed(F4)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			keyboard.SetHidReportBuffer(1, 0x83);
			keyboard.SetHidReportBuffer(2, 0x01);
			report_flag = true;
		}else if(keyboard.KeyPressed(F5)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			keyboard.SetHidReportBuffer(1, 0xB6);
			report_flag = true;
		}else if(keyboard.KeyPressed(F6)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			keyboard.SetHidReportBuffer(1, 0xB5);
			report_flag = true;
		}else if(keyboard.KeyPressed(F7)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			keyboard.SetHidReportBuffer(1, 0xCD);
			report_flag = true;
		}else if(keyboard.KeyPressed(F8)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			keyboard.SetHidReportBuffer(1, 0xB7);
			report_flag = true;
		}else if(keyboard.KeyPressed(F9)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			keyboard.SetHidReportBuffer(1, 0xE9);
			report_flag = true;
		}else if(keyboard.KeyPressed(F10)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			keyboard.SetHidReportBuffer(1, 0xEA);
			report_flag = true;
		}else if(keyboard.KeyPressed(F11)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			keyboard.SetHidReportBuffer(1, 0xE2);
			report_flag = true;
		}else if(keyboard.KeyPressed(F12)){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			keyboard.SetHidReportBuffer(1, 0x92);
			keyboard.SetHidReportBuffer(2, 0x01);
			report_flag = true;
		}
	}else {
		if(report_flag){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
			report_flag = false;
		} else {
			report_ID = 1;
		}
		lastHidBuffer[0] = report_ID;
	}
	isKeyDownCombination = keyboard.KeyPressed(UP_ARROW) | keyboard.KeyPressed(DOWN_ARROW) | keyboard.KeyPressed(LEFT_ARROW) | keyboard.KeyPressed(RIGHT_ARROW) | keyboard.KeyPressed(SPACE) | keyboard.KeyPressed(F1) | keyboard.KeyPressed(F2) | keyboard.KeyPressed(F3) | keyboard.KeyPressed(F4) | keyboard.KeyPressed(F5) | keyboard.KeyPressed(F6) | keyboard.KeyPressed(F7) | keyboard.KeyPressed(F8) | keyboard.KeyPressed(F9) | keyboard.KeyPressed(F10) | keyboard.KeyPressed(F11) | keyboard.KeyPressed(F12);

	if (is_Send && memcmp(lastHidBuffer + 1, keyboard.GetHidReportBuffer(report_ID) + 1, KEY_REPORT_SIZE - 1) != 0) {
		// Report HID key states
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, keyboard.GetHidReportBuffer(report_ID), KEY_REPORT_SIZE);
		memcpy(lastHidBuffer, keyboard.GetHidReportBuffer(report_ID), KEY_REPORT_SIZE);
		report_ID++;
		if (report_ID > 3) report_ID = 1;
		lastHidBuffer[0] = report_ID;
	}
	
	/* if (is_Send){ */
	/* 	USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, keyboard.GetHidReportBuffer(report_ID), KEY_REPORT_SIZE); */
	/* } */
	/* uint8_t voidHidBuffer[HID_REPORT_SIZE] = {0}; */
	/* USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, voidHidBuffer, KEY_REPORT_SIZE); */
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
