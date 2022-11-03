#include "common_inc.h"
#include "configurations.h"
#include "HelloWord/hw_keyboard.h"


/* Component Definitions -----------------------------------------------------*/
KeyboardConfig_t config;
HWKeyboard keyboard(&hspi1);
EEPROM eeprom;

/* Main Entry ----------------------------------------------------------------*/
void Main()
{
	eeprom.Pull(0, config);
	if (config.configStatus != CONFIG_OK)
	{
		// Use default settings
		config = KeyboardConfig_t{
			.configStatus = CONFIG_OK,
				.serialNum=123,
				.keyMap={},
				.light_mode=1,
				.light_level=1,
				.key_speed_level=5
		};
		memset(config.keyMap, -1, 128);
		eeprom.Push(0, config);
	}
	if (config.light_mode < 1 || config.light_level < 1 || config.key_speed_level < 1){
		config.light_mode = 1;
		config.light_level = 1;
		config.key_speed_level = 1;
		eeprom.Push(0, config);
	}

	// Keyboard Report Start
	HAL_TIM_Base_Start_IT(&htim4);


	/*---- This is a demo RGB effect ----*/
	static uint8_t color_v = 1;
	static bool color_flag = true;
	while (true)
	{
		color_flag ? color_v++ : color_v--;
		if (color_v > 254) color_flag = false;
		else if (color_v < 1) color_flag = true;

		if (config.light_mode == 1){
			for (uint8_t i = 0; i < HWKeyboard::LED_NUMBER; i++){
				keyboard.SetRgbBufferByID(i, HWKeyboard::Color_t{color_v, 20, 100});
			}

		}else if (config.light_mode == 2){
			for (uint8_t i = 0; i < HWKeyboard::LED_NUMBER; i++){
				keyboard.SetRgbBufferByID(i, HWKeyboard::Color_t{0, 0, 0});
			}

		}else if (config.light_mode == 3){
			for (uint8_t i = 0; i < HWKeyboard::LED_NUMBER; i++){
				keyboard.SetRgbBufferByID(i, HWKeyboard::Color_t{0, 0, 0});
			}

		}else if (config.light_mode == 4){
			for (uint8_t i = 0; i < HWKeyboard::LED_NUMBER; i++){
				keyboard.SetRgbBufferByID(i, HWKeyboard::Color_t{0, 0, 0});
			}

		}else {
			for (uint8_t i = 0; i < HWKeyboard::LED_NUMBER; i++){
				keyboard.SetRgbBufferByID(i, HWKeyboard::Color_t{0, 0, 0});
			}

		}
		// Send RGB buffers to LEDs
		keyboard.SyncLights();
	}
}

/* Event Callbacks -----------------------------------------------------------*/
extern "C" void OnTimerCallback() // 1000Hz callback
{
	bool is_Send = true;
	keyboard.ScanKeyStates();  // Around 40us use 4MHz SPI clk
	keyboard.ApplyDebounceFilter(config.key_speed_level * 20); // DebounceFilter Default value is 100
	uint8_t layer = keyboard.FnPressed() ? 2 : 1;
	keyboard.Remap(layer);  // When Fn pressed use layer-2

	if (layer == 2 && keyboard.KeyPressed(HWKeyboard::SPACE))
	{
		config.light_mode = (config.light_mode + 1 ) % 4 ;
		eeprom.Push(0, config);
		is_Send = false;
	}else if (layer == 2 && keyboard.KeyPressed(HWKeyboard::UP_ARROW)) {
		is_Send = false;

	}else if (layer == 2 && keyboard.KeyPressed(HWKeyboard::DOWN_ARROW)) {
		is_Send = false;

	}else if (layer == 2 && keyboard.KeyPressed(HWKeyboard::LEFT_ARROW)) {
		config.key_speed_level = config.key_speed_level++;
		if (config.key_speed_level > 6){
			config.key_speed_level = 6;
		}
		eeprom.Push(0,config);
	}else if (layer == 2 && keyboard.KeyPressed(HWKeyboard::RIGHT_ARROW)) {
		config.key_speed_level = config.key_speed_level--;
		if (config.key_speed_level < 1){
			config.key_speed_level = 1;
		}
		eeprom.Push(0,config);
	}

	if (is_Send){
		// Report HID key states
		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,
				keyboard.GetHidReportBuffer(1),
				HWKeyboard::KEY_REPORT_SIZE);
	}

}


	extern "C"
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi)
{
	keyboard.isRgbTxBusy = false;
}

	extern "C"
void HID_RxCpltCallback(uint8_t* _data)
{

}
