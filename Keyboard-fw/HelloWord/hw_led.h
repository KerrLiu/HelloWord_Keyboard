#ifndef HELLO_WORD_KEYBOARD_FW_HW_LED_H
#define HELLO_WORD_KEYBOARD_FW_HW_LED_H

#include "spi.h"

class HW_Led {
	public:
		explicit HW_Led(SPI_HandleTypeDef* _spi) :
			spiHandle(_spi)
	{
		// Init RGB buffer
		/* TurnLight(); */
		for (uint8_t i = 0; i < HW_Led::LED_NUMBER; i++)
			SetRgbBufferByID(i, HW_Led::Color_t{0, 0, 0}, 0);
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
		/* explicit HW_Led(SPI_HandleTypeDef* _spi): spiHandle(_spi) {} */

		void SetRgbBufferByID(uint8_t _keyId, Color_t _color, float _brightness);
		void SyncLights();

		float GetBrightness() { return brightness; }
		uint8_t GetLedMode() { return ledMode; }

		void SetBrightness(float _brightness) { brightness = _brightness; }
		void SetLedMode(uint8_t _ledMode) { ledMode = _ledMode; }

		// Lamp efficiency code
		void RespiratoryEffect(Color_t _color);
		void TurnLight();
		void OneButton(uint8_t _index, Color_t _color);

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
