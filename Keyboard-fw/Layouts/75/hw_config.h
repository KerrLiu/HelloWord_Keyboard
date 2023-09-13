#pragma once

#ifndef HELLO_WORD_KEYBOARD_FW_HW_CFG_H
#define HELLO_WORD_KEYBOARD_FW_HW_CFG_H

/*------------------------- This is 75 layout config -------------------------*/

/*-------------------------- Begin Necessary config --------------------------*/
#define IO_NUMBER 11 * 8               // Used 11 pcs 74HC165
#define KEY_NUMBER 82                  // Layout Key Numbers Default 75 layout
#define TOUCHPAD_NUMBER 6              // Touch bar Key Number
#define FN_NUMBER 9                    // FN On remapBuffer index FnPressed()
#define FN_OFFSET 0x04                 // FN On remapBuffer & value FnPressed()

#define RGB_MATRIX_LED_COUNT 101                 // ALL LED Numbers
#define MATRIX_ROWS 6                     // Key Rows
#define MATRIX_COLS 16                    // Key Cols
/*--------------------------- End Necessary config ---------------------------*/

/*--------------------------- Begin Module config ---------------------------*/
#define RGB_MATRIX_ENABLE              // Don't need RGB led can delete it
#define TOUCHBAR_ENABLE                // Don't need touch bar can delete it
#define EEPROM_CONFIG                  // Don't need EEPROM can delete it
/*---------------------------- End Module config ----------------------------*/


/*------------------------ Begin Module Delay config ------------------------*/
#define EEPROM_CONFIG_TIME 600 * 1000  // 1 second equals 1000 milliseconds
/*------------------------ End Module Delay config ------------------------*/

#define RGB_MATRIX_KEYREACTIVE_ENABLED    // KEYREACTIVE ENABLED
#define RGB_MATRIX_KEYPRESSES             // KEYREACTIVE Use RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASE

#define NO_LED 255

/*------------------------- Begin Led Module config -------------------------*/
#define LED_NUMS 82                      // NumLock led index or NO_LED
#define LED_CAPS 83                      // CapsLock led index or NO_LED
#define LED_SCROLL 84                    // ScrollLock led index or NO_LED
#define LED_COMPOSE NO_LED               // ComposeLock led index or NO_LED
#define LED_KANA NO_LED                  // KanaLock led index or NO_LED

#define RGB_MATRIX_TIMEOUT 600 * 1000    // Not pressing the button to turn off the light after these times
#define RGB_MATRIX_BRIGHTNESS_STEP 32
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX
#define RGB_MATRIX_DEFAULT_HUE 0
#define RGB_MATRIX_DEFAULT_SAT UINT8_MAX
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_DEFAULT_SPD UINT8_MAX / 2
#define RGB_MATRIX_HUE_STEP 32
#define RGB_MATRIX_SAT_STEP 32
#define RGB_MATRIX_VAL_STEP 32
#define RGB_MATRIX_SPD_STEP 16
#define RGB_MATRIX_CENTER {112, 32}
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
/*------------------------- End Led Module config -------------------------*/

/*----------------------- Begin Light Animation config -----------------------*/
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_PIXEL_RAIN
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
/*------------------------ End Light Animation config ------------------------*/

#endif
