#ifndef HELLO_WORD_KEYBOARD_FW_HW_CFG_H
#define HELLO_WORD_KEYBOARD_FW_HW_CFG_H

#include "hw_hid_report.h"

/*------------------------- This is 75 layout -------------------------*/

static const uint8_t IO_NUMBER = 11 * 8; 		// Used 11 pcs 74HC165
static const uint8_t KEY_NUMBER = 82;			// Layout Key Numbers Default 75 layout
static const uint8_t TOUCHPAD_NUMBER = 6;		// Touch bar Key Number
static const uint8_t FN_NUMBER = 9;				// FN On remapBuffer index FnPressed()
static const uint8_t FN_OFFSET = 0x04;			// FN On remapBuffer & value FnPressed()
static const uint16_t KEY_REPORT_SIZE = 1 + 16;
static const uint16_t RAW_REPORT_SIZE = 1 + 32;
static const uint16_t HID_REPORT_SIZE = KEY_REPORT_SIZE + RAW_REPORT_SIZE;

static const uint8_t LED_NUMBER = 104;
static const uint8_t LED_VOID = 127;			// For light matrix
static const uint8_t LED_Num = 82;				// NumLock led index
static const uint8_t LED_Caps = 83;				// CapsLock led index
static const uint8_t LED_Scr = 84;				// ScrollLock led index

static int16_t keyMap[5][IO_NUMBER] = {
	{67,61,60,58,59,52,55,51,50,49,48,47,46,3,
		80,81,64,57,62,63,53,54,45,44,40,31,26,18,2,
		19,70,71,66,65,56,36,37,38,39,43,42,41,28,0,
		15,74,73,72,68,69,29,30,35,34,33,32,24,1,
		14,76,77,78,79,16,20,21,22,23,27,25,17,4,
		13,12,8,75,9,10,7,11,6,5,
		86,84,82,87,85,83}, // TouchBar index

	{ESC,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,PRINT,
		GRAVE_ACCENT,NUM_1,NUM_2,NUM_3,NUM_4,NUM_5,NUM_6,NUM_7,NUM_8,NUM_9,NUM_0,MINUS,EQUAL,BACKSPACE,INSERT,
		TAB,Q,W,E,R,T,Y,U,I,O,P,LEFT_U_BRACE,RIGHT_U_BRACE,BACKSLASH,DELETE,
		CAP_LOCK,A,S,D,F,G,H,J,K,L,SEMI_COLON,QUOTE,ENTER,HOME,
		LEFT_SHIFT,Z,X,C,V,B,N,M,COMMA,PERIOD,SLASH,RIGHT_SHIFT,UP_ARROW,END,
		LEFT_CTRL,LEFT_GUI,LEFT_ALT,SPACE,RIGHT_ALT,FN,RIGHT_CTRL,LEFT_ARROW,DOWN_ARROW,RIGHT_ARROW }, // Default layout for win

	{ESC,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,PAUSE,
		GRAVE_ACCENT,NUM_1,NUM_2,NUM_3,NUM_4,NUM_5,NUM_6,NUM_7,NUM_8,NUM_9,NUM_0,MINUS,EQUAL,BACKSPACE,INSERT,
		TAB,Q,W,E,R,T,Y,U,I,O,P,LEFT_U_BRACE,RIGHT_U_BRACE,BACKSLASH,DELETE,
		CAP_LOCK,A,S,D,F,G,H,J,K,L,SEMI_COLON,QUOTE,ENTER,PAGE_UP,
		LEFT_SHIFT,Z,X,C,V,B,N,M,COMMA,PERIOD,SLASH,RIGHT_SHIFT,UP_ARROW,PAGE_DOWN,
		LEFT_CTRL,LEFT_GUI,LEFT_ALT,SPACE,RIGHT_ALT,FN,RIGHT_CTRL,LEFT_ARROW,DOWN_ARROW,RIGHT_ARROW }, // Fn Layout This is Static

	{ESC,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,PRINT,
		GRAVE_ACCENT,NUM_1,NUM_2,NUM_3,NUM_4,NUM_5,NUM_6,NUM_7,NUM_8,NUM_9,NUM_0,MINUS,EQUAL,BACKSPACE,INSERT,
		TAB,Q,W,E,R,T,Y,U,I,O,P,LEFT_U_BRACE,RIGHT_U_BRACE,BACKSLASH,DELETE,
		CAP_LOCK,A,S,D,F,G,H,J,K,L,SEMI_COLON,QUOTE,ENTER,HOME,
		LEFT_SHIFT,Z,X,C,V,B,N,M,COMMA,PERIOD,SLASH,RIGHT_SHIFT,UP_ARROW,END,
		LEFT_CTRL,LEFT_ALT,LEFT_GUI,SPACE,RIGHT_GUI,FN,RIGHT_ALT,LEFT_ARROW,DOWN_ARROW,RIGHT_ARROW }, // Default layout for mac
};

/*----Key corresponds to Led subscript----*/
static constexpr uint8_t keyLEDMap[LED_NUMBER] = {
	13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
	14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,  28,
	43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29,
	44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
	71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58,
	72, 73, 74, 75, 76, 77, 78, 79, 80, 81,
	82, 83, 84,
	85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100
};

static constexpr uint8_t keyNearMap[KEY_NUMBER][6] = {
	{1, 14, 15, 127, 127, 127},			{2, 15, 16, 17, 127, 127},
	{1, 3, 16, 17, 18, 127},			{2, 4, 17, 18, 19, 127},
	{3, 5, 18, 19, 20, 127},			{4, 6, 20, 21, 127, 127},
	{5, 7, 21, 22, 127, 127},			{6, 8, 22, 23, 127, 127},
	{7, 9, 23, 24, 127, 127},			{8, 10, 24, 25, 127, 127},
	{9, 11, 25, 26, 127, 127},			{10, 12, 26, 27, 127, 127},
	{11, 12, 27, 28, 127, 127},			{12, 28, 127, 127, 127, 127},
	{0, 15, 29, 127, 127, 127},			{0, 1, 14, 16, 29, 30},
	{1, 2, 15, 17, 30, 31},				{2, 3, 16, 18, 31, 32},
	{3, 4, 17, 19, 32, 33},				{4, 18, 20, 33, 34, 127},
	{4, 5, 19, 21, 34, 35},				{5, 6, 20, 22, 35, 36},
	{6, 7, 21, 23, 36, 37},				{7, 8, 22, 24, 37, 38},
	{8, 9, 23, 25, 38, 39},				{9, 10, 24, 26, 39, 40},
	{10, 11, 25, 27, 40, 41},			{11, 12, 26, 41, 42, 127},
	{13, 27, 43, 127, 127, 127},		{14, 15, 30, 44, 127, 127},
	{15, 16, 29, 31, 44, 45},			{16, 17, 30, 32, 45, 46},
	{17, 18, 31, 33, 46, 47},			{18, 19, 32, 34, 47, 48},
	{19, 20, 33, 35, 48, 49},			{21, 22, 34, 36, 49, 50},
	{22, 23, 35, 37, 50, 51},			{23, 24, 36, 38, 51, 52},
	{24, 25, 37, 39, 52, 53},			{25, 26, 38, 40, 53, 54},
	{26, 27, 39, 41, 54, 55},			{27, 28, 40, 42, 55, 56},
	{27, 41, 43, 56, 127, 127},			{28, 42, 57, 127, 127, 127},
	{29, 30, 45, 58, 127, 127},			{30, 31, 44, 46, 58, 59},
	{31, 32, 45, 47, 59, 60},			{32, 33, 46, 48, 60, 61},
	{33, 34, 47, 49, 61, 62},			{34, 35, 48, 50, 62, 63},
	{35, 36, 49, 51, 63, 64},			{36, 37, 50, 52, 64, 65},
	{37, 38, 51, 53, 65, 66},			{38, 39, 52, 54, 66, 67},
	{39, 40, 53, 55, 67, 68},			{40, 41, 54, 56, 68, 69},
	{41, 42, 55, 69, 70, 127},			{43, 71, 127, 127, 127, 127},
	{44, 45, 59, 72, 73, 127},			{45, 46, 58, 60, 73, 74},
	{46, 47, 59, 61, 74, 127},			{47, 48, 60, 62, 127, 127},
	{48, 49, 61, 63, 75, 127},			{49, 50, 62, 64, 75, 127},
	{50, 51, 63, 65, 75, 127},			{51, 52, 64, 66, 127, 127},
	{51, 53, 65, 67, 76, 127},			{53, 54, 66, 68, 76, 77},
	{54, 55, 67, 69, 77, 78},			{55, 56, 68, 70, 78, 79},
	{56, 69, 71, 79, 80, 81},			{57, 70, 80, 81, 127, 127},
	{58, 73, 127, 127, 127, 127},		{58, 59, 72, 74, 127, 127},
	{59, 60, 73, 127, 127, 127},		{62, 63, 64, 127, 127, 127},
	{66, 67, 77, 127, 127, 127},		{67, 68, 76, 78, 127, 127},
	{68, 69, 77, 79, 127, 127},			{69, 70, 78, 80, 127, 127},
	{70, 79, 81, 127, 127, 127},		{70, 71, 80, 127, 127, 127}
};

static constexpr uint8_t colLEDMap[15][6] = {
	{13, 14, 43, 44, 71, 72},
	{12, 15, 42, 45, 70, 73},
	{11, 16, 41, 46, 69, 74},
	{10, 17, 40, 47, 68, 75},
	{9, 18, 39, 48, 67, 76},
	{8, 19, 38, 49, 66, 77},
	{7, 20, 37, 50, 65, 78},
	{6, 21, 36, 51, 64, 79},
	{5, 22, 35, 52, 63, 80},
	{4, 23, 34, 53, 62, 81},
	{3, 24, 33, 54, 61, 127},
	{2, 25, 32, 55, 60, 127},
	{1, 26, 31, 56, 59, 127},
	{0, 27, 30, 57, 58, 127},
	{127, 28, 29, 127, 127, 127}
};

static constexpr uint8_t rowLEDMap[6][15] = {
	{13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 127},
	{14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28},
	{43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29},
	{44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 127},
	{71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 127},
	{72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 127, 127, 127, 127, 127},
};
#endif
