#ifndef HELLO_WORD_KEYBOARD_FW_HW_LED_H
#define HELLO_WORD_KEYBOARD_FW_HW_LED_H

#include "spi.h"

class HW_Led {
	public:
		explicit HW_Led(SPI_HandleTypeDef* _spi) :
			spiHandle(_spi)
	{
		// Init RGB buffer
		for (uint8_t i = 0; i < HW_Led::LED_NUMBER; i++)
			SetRgbBufferByID(i, HW_Led::Color_t{0, 0, 0});
	}
		static const uint8_t LED_NUMBER = 104;
		struct Color_t { uint8_t r, g, b; };

		enum SpiWs2812Byte_t : uint8_t {
			// This should be tuned considering WS2812b clock timing
			WS_HIGH = 0xFE, // 0b11111110
			WS_LOW = 0xE0   // 0b11100000
		};

		void SetRgbBufferByID(uint8_t _keyId, Color_t _color, float _brightness = 0.25);
		void SyncLights();

		volatile bool isRgbTxBusy{};

	private:
		SPI_HandleTypeDef* spiHandle;
		uint8_t rgbBuffer[LED_NUMBER][3][8]{};
		uint8_t wsCommit[64] = {0};
		uint8_t brightnessPreDiv = 2; // 1/4
};

#endif
