#ifndef HELLO_WORD_KEYBOARD_FW_HW_LED_H
#define HELLO_WORD_KEYBOARD_FW_HW_LED_H

#include "spi.h"
#include "HelloWord/hw_keyboard.h"

class HWLed {
	public:
		explicit HWLed(SPI_HandleTypeDef* _spi) :
			spiHandle(_spi)
	{
		// Init RGB buffer
		/* TurnLight(); */
		for (uint8_t i = 0; i < LED_NUMBER; i++)
			SetRgbBufferByID(i, Color_t{0, 0, 0}, 0);
	}
		static const uint8_t LED_NUMBER = 104;
		struct Color_t { uint8_t r, g, b; };

		enum SpiWs2812Byte_t : uint8_t {
			// This should be tuned considering WS2812b clock timing
			WS_HIGH = 0xFE, // 0b11111110
			WS_LOW = 0xE0   // 0b11100000
		};

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

		static constexpr uint8_t keyNearMap[HWKeyboard::KEY_NUMBER][6] = {
			{13, 14, 127, 127, 127, 127},
			{12, 11, 15, 16, 127, 127},
			{11, 12, 10, 15, 16, 127},
			{10, 11, 9, 16, 17, 127},
			{9, 10, 18, 19, 127, 127},
			{8, 7, 20, 21, 127, 127},
			{7, 8, 7, 21, 22, 127},
			{6, 7, 5, 22, 23, 127},
			{5, 6, 23, 24, 127, 127},
			{4, 3, 24, 25, 127, 127},
			{3, 4, 2, 25, 26, 127},
			{2, 3, 1, 26, 27, 127},
			{1, 2, 27, 127, 127, 127},
			{0, 28, 127, 127, 127, 127},
			{14, 13, 15, 43, 127, 127},
			{15, 14, 16, 43, 42, 127},
			{16, 15, 17, 12, 42, 41},
			{17, 16, 18, 11, 41, 40},
			{18, 17, 19, 10, 40, 39},
			{19, 18, 20, 9, 39, 38},
			{20, 19, 21, 8, 38, 37},
			{21, 20, 22, 7, 37, 36},
			{22, 21, 23, 6, 36, 35},
			{23, 22, 24, 5, 35, 34},
			{24, 23, 25, 4, 34, 33},
			{25, 24, 26, 3, 33, 32},
			{26, 25, 27, 2, 32, 31},
			{27, 26, 2, 1, 31, 30},
			{28, 0, 29, 127, 127, 127},
			{43, 42, 14, 44, 127, 127},
			{42, 41, 43, 15, 16, 45},
			{41, 40, 42, 16, 17, 46},
			{40, 39, 41, 17, 18, 47},
			{39, 38, 40, 18, 19, 48},
			{38, 37, 39, 19, 20, 49},
			{37, 36, 38, 20, 21, 50},
			{36, 35, 37, 21, 22, 51},
			{35, 34, 36, 22, 23, 52},
			{34, 33, 35, 23, 24, 53},
			{33, 32, 34, 24, 25, 54},
			{32, 31, 33, 25, 26, 55},
			{31, 30, 32, 26, 27, 56},
			{30, 56, 31, 27, 127, 127},
			{29, 28, 57, 127, 127, 127},
			{44, 45, 42, 43, 71, 127},
			{45, 46, 44, 42, 71, 70},
			{46, 47, 45, 41, 70, 69},
			{47, 48, 46, 40, 69, 68},
			{48, 49, 47, 39, 68, 67},
			{49, 50, 48, 38, 67, 66},
			{50, 51, 49, 37, 66, 65},
			{51, 52, 50, 36, 65, 64},
			{52, 53, 51, 35, 64, 63},
			{53, 54, 52, 34, 63, 62},
			{54, 55, 53, 33, 62, 61},
			{55, 56, 54, 32, 61, 60},
			{56, 31, 55, 30, 60, 127},
			{57, 29, 58, 127, 127, 127},
			{71, 44, 72, 45, 70, 73},
			{70, 71, 69, 46, 73, 74},
			{69, 70, 68, 47, 74, 127},
			{68, 69, 67, 48, 127, 127},
			{67, 68, 66, 49, 75, 127},
			{66, 67, 65, 50, 75, 127},
			{65, 66, 64, 51, 75, 127},
			{64, 65, 63, 52, 127, 127},
			{63, 64, 62, 53, 76, 127},
			{62, 63, 61, 54, 76, 127},
			{61, 62, 60, 55, 77, 127},
			{60, 61, 127, 56, 78, 127},
			{59, 80, 79, 81, 127, 127},
			{58, 57, 127, 127, 127, 127},
			{72, 73, 60, 127, 127, 127},
			{73, 74, 72, 71, 127, 127},
			{74, 71, 73, 69, 127, 127},
			{75, 67, 66, 65, 127, 127},
			{76, 77, 62, 127, 127, 127},
			{77, 78, 76, 61, 127, 127},
			{78, 77, 60, 127, 127, 127},
			{79, 80, 81, 59, 127, 127},
			{80, 79, 81, 59, 127, 127},
			{81, 80, 79, 59, 127, 127}
		};

		void SetRgbBufferByID(uint8_t _keyId, Color_t _color, float _brightness);
		void SyncLights();

		float GetBrightness() { return brightness; }
		uint8_t GetLedMode() { return ledMode; }

		void SetBrightness(float _brightness) { brightness = _brightness; }
		void SetLedMode(uint8_t _ledMode) { ledMode = _ledMode; }

		// Lamp efficiency code
		void RespiratoryEffect(Color_t _color);
		void TurnLight();
		void OneButton(HWKeyboard _keyboard, uint8_t _color_v);
		void ButtonRange(HWKeyboard _keyboard, uint8_t _color_v);

		volatile bool isRgbTxBusy{};

	private:
		SPI_HandleTypeDef* spiHandle;
		uint8_t rgbBuffer[LED_NUMBER][3][8]{};
		uint8_t wsCommit[64] = {0};
		uint8_t brightnessPreDiv = 2; // 1/4
		float brightness = 0.25;
		uint8_t ledMode = 0;
};

#endif
