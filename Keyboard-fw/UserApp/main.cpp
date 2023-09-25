#include "common_inc.h"
#include "configurations.h"

/*------------------------ Begin Component Definitions -----------------------*/
HWKeyboard keyboard(&hspi1);
HWLed hwled(&hspi2);
KeyboardConfig_t config;
/*------------------------- End Component Definitions ------------------------*/

#ifdef RGB_MATRIX_ENABLE
extern rgb_config_t rgb_matrix_config;
#endif

volatile uint8_t isKeyboardState = SENDED;
volatile bool isKeyDownComb = false;
volatile uint8_t report_ID = 1;
volatile bool report_flag = true;

void SendReportKeyboardHID(uint8_t *_HidBuffer) {
  if(USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, _HidBuffer, KEY_REPORT_SIZE) == USBD_BUSY){
    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, _HidBuffer, KEY_REPORT_SIZE);
  }
}

void SendReportRawHID(uint8_t *_HidBuffer) {}

void SendReportConsumerHID(uint8_t *_HidBuffer) {
  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, _HidBuffer, KEY_REPORT_SIZE);
}

#ifdef EEPROM_CONFIG
EEPROM eeprom;
uint32_t eeprom_time = timer_read32();
#endif

void KbSetCfg(uint8_t high, uint8_t low) {
  switch (high) {
#ifdef RGB_MATRIX_ENABLE
  case MSB(KEYSET_LIGHTMODE):
    rgb_matrix_config.mode = ((rgb_matrix_config.mode + 1) % RGB_MATRIX_EFFECT_MAX);
    config_set();
    break;
  case MSB(KEYSET_BRIGHTNESS_INC):
    uint8_t tmp;
    if (low) {
      tmp = MIN(RGB_MATRIX_MAXIMUM_BRIGHTNESS,
                rgb_matrix_config.hsv.v + RGB_MATRIX_BRIGHTNESS_STEP);
    } else {
      tmp = MAX(RGB_MATRIX_BRIGHTNESS_STEP,
                rgb_matrix_config.hsv.v - RGB_MATRIX_BRIGHTNESS_STEP);
    }
    rgb_matrix_config.hsv.v = tmp;

    config_set();
    break;
  case MSB(KEYSET_HSV_HUE_LOOP):
    rgb_matrix_config.hsv.h = (rgb_matrix_config.hsv.h + RGB_MATRIX_HUE_STEP);
    config_set();
  break;
#endif
  case MSB(KEYSET_LAYOUT_WIN_MAC):
    config.unFnLayout = config.unFnLayout == 1 ? 3 : 1;
    config_set();
    break;
  case MSB(KEYSET_CONFIG_SAVE):
    config_update();
    break;
  default:
#ifdef EEPROM_CONFIG
    eeprom_time = timer_read32();
#endif
    break;
  }
}

void FnCombFactory() {
  if (isKeyDownComb)
    return;

  int16_t combCode;
  uint8_t low, high;
  for (uint8_t i = 0; i < sizeof(combCodeMap) / sizeof(uint16_t); i++) {
    if (keyboard.KeyPressed(combCodeMap[i])) {
      combCode = combCodeMap[i];
      int16_t consumerCode = keyboard.KEYCODE2CONSUMER(combCode);
      low = LSB(consumerCode);
      high = MSB(consumerCode);
      if (high < MSB(KEYSET_LIGHTMODE)) {
        report_ID = 3;
        report_flag = true;
        keyboard.ResetHidReportBuffer();
        keyboard.SetHidReportBuffer(1, low);
        keyboard.SetHidReportBuffer(2, high);
      } else {
        isKeyDownComb = true;
        report_flag = true;
        keyboard.ResetHidReportBuffer();
        KbSetCfg(high, low);
      }
      break;
    }
  }
}

void switch_events(){
  uint8_t keyindex = 0;
  for(uint8_t i = 0; i < MATRIX_ROWS; i++){
    for(uint8_t j = 0; j < MATRIX_COLS; j++){
      if(g_led_config.matrix_co[i][j] == NO_LED)
        continue;
      
      if(keyboard.GetButtonStatus(keyindex)){
        process_rgb_matrix(i, j, true);
      }else{
        process_rgb_matrix(i, j, false);
      }
      keyindex++;
    }
  }
}

void UpdateKeyboardHID() {
  isKeyboardState = SENDING;
  // if (layer == 2) {
  if (keyboard.FnPressed()) {
    FnCombFactory();
  } else {
    isKeyDownComb = false;
    if (report_flag) {
      report_ID = 3;
      keyboard.ResetHidReportBuffer();
      report_flag = false;
    } else {
      report_ID = 1;
    }
  }

  if (keyboard.IsUpdateHidBuffer()) {
    SendReportKeyboardHID(keyboard.GetHidReportBuffer(report_ID));
    keyboard.UpdateLastHidBuffer();
#ifdef RGB_MATRIX_ENABLE
    switch_events();
#endif
  }
  isKeyboardState = SENDED;
}

void HelloWordInit(){
  config_init();

#if defined (RGB_MATRIX_ENABLE)
  rgb_matrix_config = config.rgb_config_cfg;
  rgb_matrix_init();
#else
  hwled.init();
#endif

  // OnTimerCallback Start
  HAL_TIM_Base_Start_IT(&htim4);
}

void SecondLoop(){

}

void MinuteLoop(){
#ifdef EEPROM_CONFIG
  if (config.configStatus == CONFIG_COMMIT &&
      timer_elapsed32(eeprom_time) > EEPROM_CONFIG_TIME) {
    config_update();
  }
#endif
}

/* Main Entry ----------------------------------------------------------------*/
void Main() {
  HelloWordInit();

  while (true) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_task();
#endif

    if (!(timer_read32() & 0x3FF)) 
      SecondLoop();

    if (!(timer_read32() & 0xFFFF))
      MinuteLoop();

    FnCombFactory();
  }
}

/* Event Callbacks -----------------------------------------------------------*/
extern "C" void OnTimerCallback() // 1000Hz callback and continue once!
{
  ms_clk += 1;
  if (ms_clk & 1)
    return;

  keyboard.ScanKeyStates();          // Around 40us use 4MHz SPI clk
  keyboard.ApplyDebounceFilter(300); // DebounceFilter Default value is 100
  // keyboard.DebounceFilter();
  // layer = keyboard.FnPressed() ? 2 : config.unFnLayout;
  keyboard.Remap(keyboard.FnPressed()
                     ? 2
                     : config.unFnLayout); // When Fn pressed use layer-2
  if (isKeyboardState == SENDED) {
    isKeyboardState = NORMAL;
    UpdateKeyboardHID();
  }
}

extern "C" void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
  hwled.isRgbTxBusy = false;
}

// extern "C" void HID_RxCpltCallback(uint8_t *_data) {
// }

extern "C" void HID_OnEventOutCallback(uint8_t event_idx, uint8_t state) {
  if (event_idx == 1) {
      hwled.anylock = state;
  }
}
