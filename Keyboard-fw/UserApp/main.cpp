#include "common_inc.h"
/* #include "configurations.h" */
#include "HelloWord/hw_keyboard.h"
#include "HelloWord/hw_led.h"


/* Component Definitions -----------------------------------------------------*/
/* KeyboardConfig_t config; */
HWKeyboard keyboard(&hspi1);
HWLed hwled(&hspi2);;
/* EEPROM eeprom; */

// UpdateKeyboardHID State
enum Update_State : uint8_t
{
	NORMAL = 0, SENDING, SENDED
};

int16_t zoneF[3][12] = {
	{F1  , F2  , F3  , F4  , F5  , F6  , F7  , F8  , F9  , F10 , F11 , F12},	// zone F 
	{0x94, 0x6F, 0x70, 0x83, 0xB6, 0xB5, 0xCD, 0xB7, 0xE9, 0xEA, 0xE2, 0x92},	// HID Data[2]
	{0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}	// HID Data[1]
};

uint8_t isKeyboardUpdate = SENDED;
bool isKeyDownCombination = false;
uint8_t key_speed_level = 1;
uint8_t lastHidBuffer[KEY_REPORT_SIZE] = {0};
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
	keyboard.ResetHidReportBuffer(report_ID);
}

void FnCombinationFactory()
{
	uint8_t zoneF_index = 0;
	if(!isKeyDownCombination){
		if(keyboard.KeyPressed(SPACE)){
			uint8_t tmp = hwled.GetLedMode();
			hwled.SetLedMode((tmp + 1) % 5);
		}else if (keyboard.KeyPressed(UP_ARROW)) {
			float tmp = hwled.GetBrightness() + 0.25;
			hwled.SetBrightness(MIN(1, tmp));
		}else if (keyboard.KeyPressed(DOWN_ARROW)) {
			float tmp = hwled.GetBrightness() - 0.25;
			hwled.SetBrightness(MAX(0.25, tmp));
		}else if (keyboard.KeyPressed(LEFT_ARROW)) {
			key_speed_level += 1;
			key_speed_level = MIN(5, key_speed_level);	
		}else if (keyboard.KeyPressed(RIGHT_ARROW)) {
			key_speed_level -= 1;
			key_speed_level = MAX(1, key_speed_level);	
		}

		for(uint8_t i = 0; i < 12; i++)
		{
			if(keyboard.KeyPressed((int16_t)zoneF[0][i]))
			{
				zoneF_index = i;
				report_ID = 3;
				report_flag = true;
				keyboard.ResetHidReportBuffer(report_ID);
				keyboard.SetHidReportBuffer(1, zoneF[1][i]);
				keyboard.SetHidReportBuffer(2, zoneF[2][i]);
				break;
			}
		}
	}
	isKeyDownCombination = keyboard.KeyPressed(UP_ARROW) | keyboard.KeyPressed(DOWN_ARROW) | keyboard.KeyPressed(LEFT_ARROW) | keyboard.KeyPressed(RIGHT_ARROW) | keyboard.KeyPressed(SPACE) | keyboard.KeyPressed(zoneF[0][zoneF_index]);
}

void UpdateKeyboardHID()
{
	isKeyboardUpdate = SENDING;
	uint8_t layer = keyboard.FnPressed() ? 2 : 1;
	keyboard.Remap(layer);  // When Fn pressed use layer-2
	if(layer == 2)
	{
		FnCombinationFactory();
	}else{
		if(report_flag){
			report_ID = 3;
			keyboard.ResetHidReportBuffer(report_ID);
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
		if(isKeyboardUpdate == NORMAL)
			UpdateKeyboardHID();

		hwled.Update(keyboard);
	}
}

/* Event Callbacks -----------------------------------------------------------*/
extern "C" void OnTimerCallback() // 1000Hz callback
{
	keyboard.ScanKeyStates();  // Around 40us use 4MHz SPI clk
	keyboard.ApplyDebounceFilter(100 * key_speed_level); // DebounceFilter Default value is 100
	if(isKeyboardUpdate == SENDED)
	{
		isKeyboardUpdate = NORMAL;
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
