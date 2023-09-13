#ifndef HELLO_WORD_KEYBOARD_FW_HW_LED_H
#define HELLO_WORD_KEYBOARD_FW_HW_LED_H

#include "spi.h"
#include "hw_core.h"
#include <cstdint>
#include <stdlib.h>

class HWLed {
public:
  explicit HWLed(SPI_HandleTypeDef *_spi) : spiHandle(_spi) {
    // explicit HWLed(SPI_HandleTypeDef *_spi) {
    // Init RGB buffer
    set_color_all(0, 0, 0);
  }

  volatile bool isRgbTxBusy{};

  enum SpiWs2812Byte_t : uint8_t {
    // This should be tuned considering WS2812b clock timing
    WS_HIGH = 0xFE, // 0b11111110
    WS_LOW = 0xE0   // 0b11100000
  };

  void set_color(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);
  void set_color_all(uint8_t red, uint8_t green, uint8_t blue);
  void init(void);
  void flush(void);

// #ifdef KEYBOARD_LOCK_STATE_ENABLE
  // kb_lock_state_t g_kb_lock;
  uint8_t anylock;
  // bool led_update_user();
  // bool led_update_kb();
  // void led_update_ports();
// #endif

private:
  SPI_HandleTypeDef *spiHandle;
  uint8_t rgbBuffer[RGB_MATRIX_LED_COUNT][3][8]{};
  uint8_t wsCommit[64] = {0};
  const uint8_t brightnessPreDiv = 2; // 1/4
};

#endif
