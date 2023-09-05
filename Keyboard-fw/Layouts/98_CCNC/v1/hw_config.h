#pragma once

#ifndef HELLO_WORD_KEYBOARD_FW_HW_CFG_H
#define HELLO_WORD_KEYBOARD_FW_HW_CFG_H

/*------------------------- This is 98 layout v1 -------------------------*/

/*-------------------------- Begin Necessary config --------------------------*/
#define IO_NUMBER 13 * 8               // Used 13 pcs 74HC165
#define KEY_NUMBER 98                  // Layout Key Numbers
#define TOUCHPAD_NUMBER 6              // Touch bar Key Number
#define FN_NUMBER 11                   // FN On remapBuffer index FnPressed()
#define FN_OFFSET 0x10                 // FN On remapBuffer & value FnPressed()

#define RGB_MATRIX_LED_COUNT 117                 // ALL LED Numbers
#define MATRIX_ROWS 6                     // Key Rows
#define MATRIX_COLS 19                    // Key Cols
/*--------------------------- End Necessary config ---------------------------*/

/*--------------------------- Begin Module config ---------------------------*/
#define RGB_MATRIX_ENABLE              // Don't need RGB led can delete it
#define TOUCHBAR_ENABLE                // Don't need touch bar can delete it
#define EEPROM_CONFIG                  // Don't need EEPROM can delete it
#define LED_SLEEP_ENABLE               // Don't need EEPROM can delete it
#define KEYBOARD_LOCK_STATE_ENABLE     // Don't need keyboard lock state can delete it
/*---------------------------- End Module config ----------------------------*/


/*------------------------ Begin Module Delay config ------------------------*/
#define EEPROM_CONFIG_TIME 600 * 1000     // 1 second equals 1000 milliseconds
#define LED_SLEEP_TIME 600 * 1000         // 1 second equals 1000 milliseconds
/*------------------------ End Module Delay config ------------------------*/

#define RGB_MATRIX_KEYREACTIVE_ENABLED    // KEYREACTIVE ENABLED
#define RGB_MATRIX_KEYPRESSES             // KEYREACTIVE Use RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASE

/*------------------------- Begin Led Module config -------------------------*/
#define LED_NUMS 32                        // NumLock led index or NO_LED
#define LED_CAPS 53                       // CapsLock led index or NO_LED
#define LED_SCROLL 3                       // ScrollLock led index or NO_LED
#define LED_COMPOSE NO_LED                 // ComposeLock led index or NO_LED
#define LED_KANA NO_LED                    // KanaLock led index or NO_LED

#define RGB_MATRIX_BRIGHTNESS_STEP 32
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX - 32
#define RGB_MATRIX_DEFAULT_HUE 0
#define RGB_MATRIX_DEFAULT_SAT UINT8_MAX
#define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_DEFAULT_SPD UINT8_MAX / 2
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
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
/*------------------------ End Light Animation config ------------------------*/

/*
static constexpr uint8_t keyLEDMap[LED_NUMBER] = {
	16, 15,  14,13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
	17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
	52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35,
    53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
	85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70,
	86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
	98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116
};
*/

/*const uint8_t LEDMAP[KEY_COLS][KEY_ROWS]{
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, 16, NO_LED, 15, 14, 13, 12, NO_LED, 11, 10, 9, 8, NO_LED, 7, 6, 5, 4, 3, NO_LED, 2, 1, 0, NO_LED},
        {NO_LED, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, NO_LED, 28, 29, NO_LED, 30, NO_LED, 31, 32, 33, 34 , NO_LED},
        {NO_LED, 52, NO_LED, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, NO_LED, 39, NO_LED, 38, 37, 36, 35, NO_LED},
        {NO_LED, 53, NO_LED, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, NO_LED, NO_LED, 65, NO_LED, 66, 67, 68, NO_LED, NO_LED},
        {NO_LED, 85, NO_LED, NO_LED, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, NO_LED, 74, NO_LED, 73, 72, 71, 70, 69, NO_LED},
        {NO_LED, 86, 87, 88, NO_LED, NO_LED, NO_LED, NO_LED, 89, NO_LED, NO_LED, NO_LED, 90, 91, 92, NO_LED, 93, 94, 95, NO_LED, 96, 97, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}
};*/

/*
static uint8_t LEDMAP[KEY_COLS][KEY_ROWS]{
	{NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
		{NO_LED, 16, NO_LED, 15, 14, 13, 12, NO_LED, 11, 10, 9, 8, NO_LED, 7, 6, 5, 4, NO_LED, 3, 2, 1, 0, NO_LED},
		{NO_LED, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, NO_LED, 28, 29, NO_LED, 30, NO_LED, 31, 32, 33, 34 NO_LED},
		{NO_LED, 52, NO_LED, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, NO_LED, 39, NO_LED, 38, 37, 36, 35, NO_LED},
		{NO_LED, 53, NO_LED, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, NO_LED, NO_LED, 65, NO_LED, 66, 67, 68, 69, NO_LED},
		{NO_LED, 85, NO_LED, NO_LED, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, NO_LED, 74, NO_LED, 73, 72, 71, 70, NO_LED, NO_LED},
		{NO_LED, 86, 87, 88, NO_LED, NO_LED, NO_LED, NO_LED, 89, NO_LED, NO_LED, NO_LED, 90, 91, 92, NO_LED, 93, 94, 95, NO_LED, 96, 97, NO_LED},
		{NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}
};*/

/*
static constexpr uint8_t keyNearMap[KEY_NUMBER][6] = {
	{0, 17, 18, 1, 127, 127},			{0,1,2,20,18,19},
	{2,1,3,19,20,21},                   {3,2,4,20,21,22},
	{4,3,5,21,22,23},                   {5,4,6,22,23,24},
	{6,5,7,23,24,25},                   {7,6,8,24,25,26},
	{8,7,9,25,26,27},                   {9,8,10,27,28,29},
	{10,9,11,28,29,30},               {11,10,12,29,30,127},
	{12,11,13,30,31,127},        {13,12,14,30,31,32},
	{14,13,15,31,32,33},     {15,14,16,32,33,34},
	{16,15,127,33,34},

	{17,127,18,35,127,127},     {18,17,19,35,36,127},
	{19,18,20,36,37,127},     {20,19,21,37,38,127},
	{21,20,22,38,39,127},     {22,21,23,39,40,127},
	{23,22,24,40,41,127},     {24,23,25,41,42,127},
	{25,24,26,42,43,127},     {26,25,27,43,44,127},
	{27,26,28,44,45,127},     {28,27,29,46,46,127},
	{29,28,30,46,47,127},     {30,29,31,47,48,127},
	{31,127,32,49,50,127},     {32,31,33,50,127,127},
	{33,32,34,127,127,51},     {34,33,127,52,127,127},

	{35,36,53,127,127,127},     {36,35,37,54,127,127},
	{37,36,68,54,55,56},     {38,37,39,55,56,57},
	{39,38,40,56,57,58},     {40,39,41,57,58,59},
	{41,40,42,58,59,60},     {42,41,43,59,60,61},
	{43,42,44,60,61,62},     {44,43,45,61,62,63},
	{45,44,46,62,63,64},     {46,45,47,63,64,127},
	{47,46,48,64,65,127},     {48,47,49,65,127,127},
	{49,48,50,66,67,127},     {50,49,51,66,67,68},
	{51,50,52,68,127,127},     {52,51,68,127,127,127},

	{53,54,70,127,127,127},     {54,53,55,71,127,127},
	{55,54,56,71,72,127},     {56,55,57,72,73,127},
	{57,56,58,73,74,127},     {58,57,59,74,75,127},
	{59,58,60,75,76,127},     {60,59,61,76,77,127},
	{61,60,62,77,78,127},     {62,61,63,78,79,127},
	{63,62,64,79,80,127},     {64,63,65,80,81,127},
	{65,64,81,127,127,127},     {66,65,67,83,84,127},
	{67,66,68,83,84,85},     {68,67,69,84,85,127},

	{69,86,87,127,127,127},
	{70,86,87,71,127,127},     {71,70,72,87,88,127},
	{72,71,73,88,127,127},     {73,72,74,89,127,127},
	{74,73,75,89,127,127},     {75,74,76,89,127,127},
	{76,75,77,89,127,127},     {77,76,78,89,127,127},
	{78,77,79,90,127,127},     {79,78,80,90,91,127},
	{80,79,81,90,91,92},     {81,80,82,127,92,93},
	{82,81,83,94,95,96},     {83,82,84,96,97,127},
	{84,83,85,96,97,98},     {85,84,69,96,97,127},

	{86,85,70,127,127,127},     {87,86,88,70,127,127},
	{88,87,71,72,127,127},     {89,88,90,127,127,127},
	{90,91,78,79,127,127},     {91,90,92,79,80,127},
	{92,91,93,80,81,127},     {93,92,94,81,82,127},
	{94,93,95,82,127,127},     {95,94,96,82,83,84},
	{96,75,97,83,84,85},     {97,96,127,84,85,69},
};

static constexpr uint8_t colLEDMap[18][6] = {
	{16, 17, 52, 53, 85, 86},
	{15, 18, 51, 54, 84, 87},
	{14, 19, 50, 55, 83 ,88},
	{13, 20, 49, 56, 82, 89},
	{12, 21, 48, 57, 81, 90},
	{11, 22, 47, 58, 80, 91},
	{10, 23, 46, 59, 79, 92},
	{9, 24, 45, 60, 78, 93},
	{8, 25, 44, 61, 77, 94},
	{7, 26, 43, 62, 76, 95},
	{6, 27, 42, 63, 75, 96},
	{5, 28, 41, 64, 74, 97},
	{4, 29, 40, 65, 73, 127},
	{3, 30, 39, 66, 72, 127},
	{2, 31, 38, 67, 71, 127},
	{1, 32, 37, 68, 70, 127},
	{0, 33, 36, 69, 127, 127},
	{127, 34, 35, 127, 127, 127},

};

static constexpr uint8_t rowLEDMap[6][18] = {
	{16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 127},
	{17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34},
	{52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35},
	{53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 127},
	{85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 127, 127},
	{86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 127, 127, 127, 127, 127, 127},
};
*/

#endif

#endif
