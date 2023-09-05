#include "hw_led.h"
#include "color.h"
#include <cstdint>

void HWLed::set_color(uint8_t index, uint8_t red, uint8_t green, uint8_t blue) {
  // To ensure there's no sequence zero bits, otherwise will case ws2812b
  // protocol error.
  if (blue < 1)
    blue = 1;

  for (uint8_t i = 0; i < 8; i++) {
    rgbBuffer[index][0][i] =
        (green >> brightnessPreDiv) & (0x80 >> i) ? WS_HIGH : WS_LOW;
    rgbBuffer[index][1][i] =
        (red >> brightnessPreDiv) & (0x80 >> i) ? WS_HIGH : WS_LOW;
    rgbBuffer[index][2][i] =
        (blue >> brightnessPreDiv) & (0x80 >> i) ? WS_HIGH : WS_LOW;
  }
}

void HWLed::set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
  for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++)
    set_color(i, red, green, blue);
}

void HWLed::init(void) {
  set_color_all(0, 0, 0);

  flush();
}

void HWLed::flush(void) {
  while (isRgbTxBusy)
    ;
  isRgbTxBusy = true;
  HAL_SPI_Transmit_DMA(&hspi2, (uint8_t *)rgbBuffer, RGB_MATRIX_LED_COUNT * 24);
  while (isRgbTxBusy)
    ;
  isRgbTxBusy = true;
  HAL_SPI_Transmit_DMA(&hspi2, wsCommit, 64);
}

#ifdef KEYBOARD_LOCK_STATE_ENABLE
/** \brief Lock LED update callback - keymap/user level
 *
 * \return True if led_update_kb() should run its own code, false otherwise.
 */
__attribute__((weak)) bool HWLed::led_update_user() {
  return true;
}

/** \brief Lock LED update callback - keyboard level
 *
 * \return Ignored for now.
 */
__attribute__((weak)) bool HWLed::led_update_kb() {
  bool res = led_update_user();
  if (res) {
      led_update_ports();
  }
  return res;
}


__attribute__((weak)) void HWLed::led_update_ports() {
  if(AnyLock){
    #if defined(LED_NUMS) && (LED_NUMS != NO_LED)
    if (AnyLock & 0x01) // Determine NumsLock
      set_color(LED_NUMS, 200, 0, 0);
    else
      set_color(LED_NUMS, 0, 0, 0);
    #endif

    #if defined(LED_CAPS) && (LED_CAPS != NO_LED)
    if (AnyLock & 0x02) // Determine CapsLock
      set_color(LED_CAPS, 0, 200, 0);
    else
      set_color(LED_CAPS, 0, 0, 0);
    #endif

    #if defined(LED_SCROLL) && (LED_SCROLL != NO_LED)
    if (AnyLock & 0x04) // Determine ScrollLock
      set_color(LED_SCROLL, 0, 0, 200);
    else
      set_color(LED_SCROLL, 0, 0, 0);
    #endif

    #if defined(LED_COMPOSE) && (LED_COMPOSE != NO_LED)
    if (AnyLock & 0x08) // Determine ComposeLock
      set_color(LED_COMPOSE, 255, 255, 0);
    else
      set_color(LED_COMPOSE, 0, 0, 0);
    #endif

    #if defined(LED_KANA) && (LED_KANA != NO_LED)
    if (AnyLock & 0x10) // Determine KanaLock
      set_color(LED_KANA, 255, 255, 255);
    else
      set_color(LED_KANA, 0, 0, 0);
    #endif
  }
}

/*
__attribute__((weak)) void HWLed::led_update_ports() {
  if(g_kb_lock.AnyLock || g_kb_lock.KanaLock){
    #if defined(LED_Num) && (LED_Num != NO_LED)
    if (g_kb_lock.NumLock)
      set_color(LED_Num, 200, 0, 0);
    else
      set_color(LED_Num, 0, 0, 0);
    #endif

    #if defined(LED_Caps) && (LED_Caps != NO_LED)
    if (g_kb_lock.CapsLock)
      set_color(LED_Caps, 0, 200, 0);
    else
      set_color(LED_Caps, 0, 0, 0);
    #endif

    #if defined(LED_Scro) && (LED_Scro != NO_LED)
    if (g_kb_lock.ScrollLock)
      set_color(LED_Scro, 0, 0, 200);
    else
      set_color(LED_Scro, 0, 0, 0);
    #endif

    #if defined(LED_Compose) && (LED_Compose != NO_LED)
    if (g_kb_lock.ComposeLock)
      set_color(LED_Compose, 255, 255, 0);
    else
      set_color(LED_Compose, 0, 0, 0);
    #endif

    #if defined(LED_Kana) && (LED_Kana != NO_LED)
    if (g_kb_lock.KanaLock)
      set_color(LED_Kana, 255, 255, 255);
    else
      set_color(LED_Kana, 0, 0, 0);
    #endif
  }
}*/

#endif