#include "common_inc.h"
#include "configurations.h"
#include "HelloWord/hw_keyboard.h"


/* Component Definitions -----------------------------------------------------*/
KeyboardConfig_t config;
HWKeyboard keyboard(&hspi1);
static uint8_t light_mode=0;

/* Main Entry ----------------------------------------------------------------*/
void Main()
{
    EEPROM eeprom;
    eeprom.Pull(0, config);
    if (config.configStatus != CONFIG_OK)
    {
        // Use default settings
        config = KeyboardConfig_t{
            .configStatus = CONFIG_OK,
            .serialNum=123,
            .keyMap={}
        };
        memset(config.keyMap, -1, 128);
        eeprom.Push(0, config);
    }

    // Keyboard Report Start
    HAL_TIM_Base_Start_IT(&htim4);


    while (true)
    {
		switch(light_mode){
			case 0 :
				/*---- This is a demo RGB effect ----*/
				static uint8_t color_v = 1;
				static bool color_flag = true;
				color_flag ? color_v++ : color_v--;
				if (color_v > 254) color_flag = false;
				else if (color_v < 1) color_flag = true;

				for (uint8_t i = 0; i < HWKeyboard::LED_NUMBER; i++)
					keyboard.SetRgbBufferByID(i, HWKeyboard::Color_t{color_v, 20, 100});
				/*-----------------------------------*/

				// Send RGB buffers to LEDs
				keyboard.SyncLights();
			break;
			case 1 :
			break;
		}
    }
}

/* Event Callbacks -----------------------------------------------------------*/
extern "C" void OnTimerCallback() // 1000Hz callback
{
    keyboard.ScanKeyStates();  // Around 40us use 4MHz SPI clk
    keyboard.ApplyDebounceFilter(100);
    keyboard.Remap(keyboard.FnPressed() ? 2 : 1);  // When Fn pressed use layer-2

    if (keyboard.KeyPressed(HWKeyboard::LEFT_CTRL) &&
        keyboard.KeyPressed(HWKeyboard::ESC))
    {
        // do something...
		light_mode = 1;
        // or trigger some keys...
        /* keyboard.Press(HWKeyboard::DELETE); */
    }

    // Report HID key states
    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,
                               keyboard.GetHidReportBuffer(1),
                               HWKeyboard::KEY_REPORT_SIZE);
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
