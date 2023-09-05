#include "hw_layout.h"

/*--------------------- Key corresponds to Led subscript ---------------------*/
#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
  {
    {13, NO_LED, 12, 11, 10, 9, 8, 7, 6, 5, 4,  3,  2,  1, NO_LED, 0},
    {14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, NO_LED, 28},
    {43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, NO_LED, 29},
    {44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, NO_LED, 56, NO_LED, 57},
    {71, NO_LED, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, NO_LED, 58},
    {72, 73, 74, NO_LED, NO_LED, NO_LED, 75, NO_LED, NO_LED, NO_LED, 76, 77, 78, 79, 80, 81}
  }, 
  /*{
    {224, 0}, {208, 0}, {192, 0}, {176, 0}, {160, 0}, {144, 0}, {128, 0}, {112, 0}, 
    {96, 0}, {80, 0}, {64, 0}, {48, 0}, {32, 0}, {0, 0}, // 0
    {0, 16}, {16, 16}, {32, 16}, {48, 16}, {64, 16}, {80, 16}, {96, 16}, {112, 16}, {128, 16}, 
    {144, 16}, {160, 16}, {176, 16}, {192, 16}, {208, 16}, {224, 16}, // 1
    {224, 32}, {216, 32}, {180, 32}, {184, 32}, {168, 32}, {152, 32}, {136, 32}, {120, 32}, {104, 32}, 
    {88, 32}, {72, 32}, {56, 32}, {40, 32}, {16, 32}, {0, 32}, // 2 offset 8
    {0, 48}, {30, 48}, {46, 48}, {62, 48}, {78, 48}, {94, 48}, {110, 48}, {126, 48}, 
    {142, 48}, {158, 48}, {174, 48}, {190, 48}, {206, 48}, {222, 48}, // 3
    {224, 64}, {209, 64}, {193, 64}, {177, 64}, {161, 64}, {145, 64}, {129, 64}, {113, 64}, 
    {97, 64}, {81, 64}, {65, 64}, {49, 64}, {33, 64}, {1, 64}, // 4 offset 1
    {0, 80}, {16, 80}, {32, 80}, {96, 80}, {144, 80}, {160, 80}, {176, 80}, {192, 80}, {208, 80}, 
	{224, 80}, // 5
    {240, 72}, {240, 80}, {240, 88}, // 3 state led
	{0, 22}, 
	{224, 0}, {208, 0}, {192, 0}, {176, 0}, {160, 0}, {144, 0}, {128, 0}, {112, 0}, {96, 0}, 
    {80, 0}, {64, 0}, {48, 0}, {32, 0}, {0, 0}, 
	{224, 22}, // 16
  },*/
  {
    {218,0}, {190,0}, {176,0}, {162,0}, {148,0}, {127,0}, {113,0}, {99,0}, 
    {85,0}, {64,0}, {50,0}, {36,0}, {22,0}, {0,0}, // 0
    {0,14}, {14,14}, {28,14}, {42,14}, {56,14}, {70,14}, {84,14}, {98,14}, 
    {112,14}, {126,14}, {140,14}, {154,14}, {168,14}, {196,14}, {218,14}, // 1
    {218,26}, {197,26}, {183,26}, {169,26}, {155,26}, {141,26}, {127,26}, 
    {113,26}, {99,26}, {85,26}, {71,26}, {57,26}, {43,26}, {22,26}, {0,26}, // 2 offset 8
    {0,38}, {25,38}, {39,38}, {53,38}, {67,38}, {81,38}, {95,38}, {109,38}, 
    {123,38}, {137,38}, {151,38}, {165,38}, {196,38}, {218,38}, // 3
    {218,50}, {182,50}, {168,50}, {154,50}, {140,50}, {126,50}, {112,50}, 
    {98,50}, {84,50}, {70,50}, {56,50}, {36,50}, {16,53}, {0,50}, // 4 offset 1
    {0,62}, {19,62}, {33,62}, {91,62}, {140,62}, {154,62}, {168,62}, 
    {186,64}, {200,64}, {214,64}, // 5
    
    {220,67}, {220,64}, {220,61}, // 3 state led
	{4,28}, 
	{214,0}, {186,0}, {172,0}, {158,0}, {144,0}, {130,0}, {116,0}, {102,0}, 
  {88,0}, {74,0}, {60,0}, {46,0}, {32,0}, {4,0}, 
	{214,28}, // 16
  },  
  {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   8, 8, 8, 
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};

/*
const uint8_t LEDMAP[MATRIX_COLS][MATRIX_ROWS]{
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, 13, NO_LED, 12, 11, 10, 9, NO_LED, 8, 7,
     6,        5,  NO_LED, 4,  3,  2,  1, NO_LED, 0, NO_LED},
    {NO_LED, 14, 15,       16, 17, 18,       19, 20,       21, 22,
     23,       24, NO_LED, 25, 26, NO_LED, 27, NO_LED, 28, NO_LED},
    {NO_LED, 43, NO_LED, 42, 41, 40,       39, 38,       37, 36,
     35,       34, 33,       32, 31, NO_LED, 30, NO_LED, 29, NO_LED},
    {NO_LED, 44,       NO_LED, 45,       46, 47,      48,
     49,       50,       51,       52,       53, 54,      55,
     NO_LED, NO_LED, 56,       NO_LED, 57, NO_LED},
    {NO_LED, 71, NO_LED, NO_LED, 70, 69,       68, 67, 66,      65, 64,
     63,       62, 61,       NO_LED, 60, NO_LED, 59, 58, NO_LED},
    {NO_LED, 72,       73,       74,       NO_LED, NO_LED, NO_LED,
     NO_LED, 75,       NO_LED, NO_LED, NO_LED, 76,       77,
     78,       NO_LED, 79,       80,       81,       NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}};*/
#endif

#ifdef KEYBOARD_LOCK_STATE_ENABLE

bool HWLed::led_update_user() {
  return true;
}

bool HWLed::led_update_kb() {
  bool res = led_update_user();
  if (res) {
      led_update_ports();
  }
  return res;
}

/** 
 * You can override the display effect of the status indicator here
 * uint8_t AnyLock & 0x01 nums 0x02 caps 0x04 scroll 0x08 compare 0x10 kana
 */
void HWLed::led_update_ports(){
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
#endif