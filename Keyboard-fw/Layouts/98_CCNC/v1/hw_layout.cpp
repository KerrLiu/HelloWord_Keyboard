#include "hw_layout.h"

/*--------------------- Key corresponds to Led subscript ---------------------*/
#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
  {
    {16, NO_LED, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, NO_LED, 3, 2, 1, 0},
    {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, NO_LED, 31, 32, 33, 34},
    {52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, NO_LED, 38, 37, 36, 35},
    {53, NO_LED, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, NO_LED, 64, NO_LED, 65, 66, 67, 68},
    {85, NO_LED, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, NO_LED, 73, 72, 71, 70, 69},
    {86, 87, 88, NO_LED, NO_LED, NO_LED, 89, NO_LED, NO_LED, NO_LED, 90, 91, 92, 93, 94, 95, 96, 97, NO_LED}
  }, 
  {
    {224,0}, {200,0}, {188,0}, {176,0}, {164,0}, {146,0}, {134,0}, {122,0}, {110,0}, {92,0}, {80,0}, {68,0}, {56,0}, {36,0}, {24,0}, {12,0}, {0,0}, // 0
    {0,14}, {12,14}, {24,14}, {36,14}, {48,14}, {60,14}, {72,14}, {84,14}, {96,14}, {108,14}, {120,14}, {132,14}, {144,14}, {168,14}, {188,14}, {200,14}, {212,14}, {224,14}, // 1
    {224,26}, {206,26}, {194,26}, {182,26}, {170,26}, {158,26}, {146,26}, {134,26}, {122,26}, {110,26}, {98,26}, {86,26}, {74,26}, {56,26}, {36,26}, {24,26}, {12,26}, {0,32}, // 2
    {0,38}, {21,38}, {33,38}, {45,38}, {57,38}, {69,38}, {81,38}, {93,38}, {105,38}, {117,38}, {129,38}, {141,38}, {168,38}, {188,38}, {200,38}, {212,38}, // 3
    {224,50}, {195,50}, {183,50}, {171,50}, {159,50}, {147,50}, {135,50}, {123,50}, {111,50}, {99,50}, {87,50}, {69,50}, {52,53}, {36,50}, {24,50}, {12,50}, {0,50}, // 4
    {0,64}, {17,64}, {30,64}, {74,64}, {120,64}, {134,64}, {146,64}, {161,64}, {173,64}, {185,64}, {200,64}, {212,64}, // 5
    {2,28}, {220,0}, {196,0}, {184,0}, {172,0}, {160,0}, {148,0}, {136,0}, {124,0}, {112,0}, {100,0}, {88,0}, {76,0}, {64,0}, {40,0}, {28,0}, {16,0}, {4,0} ,{220,28}, // 19
  },  
  {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   }
};

/** 
 * You can override the display effect of the status indicator here
 * uint8_t anylock & 0x01 nums 0x02 caps 0x04 scroll 0x08 compare 0x10 kana
 */
bool rgb_matrix_indicators_user(uint8_t anylock){
  if(anylock){
    #if defined(LED_NUMS) && (LED_NUMS != NO_LED)
    if (anylock & 0x01) // Determine NumsLock
      rgb_matrix_set_color(LED_NUMS, 255, 0, 0);
    else
      rgb_matrix_set_color(LED_NUMS, 0, 0, 0);
    #endif

    #if defined(LED_CAPS) && (LED_CAPS != NO_LED)
    if (anylock & 0x02) // Determine CapsLock
      rgb_matrix_set_color(LED_CAPS, 0, 255, 0);
    else
      rgb_matrix_set_color(LED_CAPS, 0, 0, 0);
    #endif

    #if defined(LED_SCROLL) && (LED_SCROLL != NO_LED)
    if (anylock & 0x04) // Determine ScrollLock
      rgb_matrix_set_color(LED_SCROLL, 0, 0, 255);
    else
      rgb_matrix_set_color(LED_SCROLL, 0, 0, 0);
    #endif

    #if defined(LED_COMPOSE) && (LED_COMPOSE != NO_LED)
    if (anylock & 0x08) // Determine ComposeLock
      rgb_matrix_set_color(LED_COMPOSE, 255, 255, 0);
    else
      rgb_matrix_set_color(LED_COMPOSE, 0, 0, 0);
    #endif

    #if defined(LED_KANA) && (LED_KANA != NO_LED)
    if (anylock & 0x10) // Determine KanaLock
      rgb_matrix_set_color(LED_KANA, 255, 255, 255);
    else
      rgb_matrix_set_color(LED_KANA, 0, 0, 0);
    #endif
  }
  return true;
}

#endif