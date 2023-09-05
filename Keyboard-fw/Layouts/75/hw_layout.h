#pragma once

#ifndef HELLO_WORD_KEYBOARD_FW_HW_LAYOUT_H
#define HELLO_WORD_KEYBOARD_FW_HW_LAYOUT_H

#include "hw_core.h"

/*----Key combination key Map----*/

const int16_t keyMap[5][IO_NUMBER] = {
  {67, 61, 60, 58, 59, 52, 55, 51, 50, 49, 48, 47, 46, 3,  80, 81, 64, 57,
   62, 63, 53, 54, 45, 44, 40, 31, 26, 18, 2,  19, 70, 71, 66, 65, 56, 36,
   37, 38, 39, 43, 42, 41, 28, 0,  15, 74, 73, 72, 68, 69, 29, 30, 35, 34,
   33, 32, 24, 1,  14, 76, 77, 78, 79, 16, 20, 21, 22, 23, 27, 25, 17, 4,
   13, 12, 8,  75, 9,  10, 7,  11, 6,  5,  86, 84, 82, 87, 85, 83}, // TouchBar index

  {ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, PRINT,
    GRAVE_ACCENT, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, NUM_0, MINUS, EQUAL, BACKSPACE, INSERT,
    TAB, Q, W, E, R, T, Y, U, I, O, P, LEFT_U_BRACE, RIGHT_U_BRACE, BACKSLASH, DELETE,
    CAP_LOCK, A, S, D, F, G, H, J, K, L, SEMI_COLON, QUOTE, ENTER, HOME,
    LEFT_SHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH, RIGHT_SHIFT, UP_ARROW, END,
    LEFT_CTRL, LEFT_GUI, LEFT_ALT, SPACE, RIGHT_ALT, FN, RIGHT_CTRL, LEFT_ARROW, DOWN_ARROW, RIGHT_ARROW}, // Default layout for win

  {ESC, KB_SU_MY_COMPUTER, KB_SU_DIS_BRIGHTNESS_INC, KB_SU_DIS_BRIGHTNESS_DEC, KB_SU_MEDIA_SELECT, KB_SU_SCAN_PREV_TRACK, KB_SU_SCAN_NEXT_TRACK, KB_SU_PLAY_PAUSE, KB_SU_STOP, KB_SU_VOLUME_INC, KB_SU_VOLUME_DEC, KB_SU_MUTE, KB_SU_CALCULATOR,
    PAUSE, GRAVE_ACCENT, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, NUM_0, MINUS, EQUAL, BACKSPACE, KB_KS_CFG_SV,
    KB_KS_HUE_LOOP, Q, W, E, R, T, Y, U, I, O, P, LEFT_U_BRACE, RIGHT_U_BRACE, BACKSLASH, DELETE,
    CAP_LOCK, A, S, D, F, G, H, J, K, L, SEMI_COLON, QUOTE, ENTER, PAGE_UP,
    LEFT_SHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH, RIGHT_SHIFT, KB_KS_BRIGHT_INC, PAGE_DOWN,
    LEFT_CTRL, KB_KS_LAYER, LEFT_ALT, KB_KS_RGBMODE, RIGHT_ALT, FN, RIGHT_CTRL, LEFT_ARROW, KB_KS_BRIGHT_DEC, RIGHT_ARROW}, // Fn Layout This is Static

  {ESC, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, PRINT,
    GRAVE_ACCENT, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, NUM_0, MINUS, EQUAL, BACKSPACE, INSERT,
    TAB, Q, W, E, R, T, Y, U, I, O, P, LEFT_U_BRACE, RIGHT_U_BRACE, BACKSLASH, DELETE,
    CAP_LOCK, A, S, D, F, G, H, J, K, L, SEMI_COLON, QUOTE, ENTER, HOME,
    LEFT_SHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH, RIGHT_SHIFT, UP_ARROW, END,
    LEFT_CTRL, LEFT_ALT, LEFT_GUI, SPACE, RIGHT_GUI, FN, RIGHT_ALT, LEFT_ARROW, DOWN_ARROW, RIGHT_ARROW}, // Default layout for mac
};

#endif
