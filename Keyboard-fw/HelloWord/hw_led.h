#ifndef HELLO_WORD_KEYBOARD_FW_HW_LED_H
#define HELLO_WORD_KEYBOARD_FW_HW_LED_H

#include "spi.h"
#include "hw_keyboard.h"
#include "math.h"


class HWLed {
	public:
		explicit HWLed(SPI_HandleTypeDef* _spi) :
			spiHandle(_spi)
		{
		// Init RGB buffer
		/* TurnLight(); */
		/* for (uint8_t i = 0; i < LED_NUMBER; i++) */
		/* 	SetRgbBufferByID(i, Color_t{0, 0, 0}, 0); */
		}
		struct Color_t { uint8_t r, g, b; };

		enum SpiWs2812Byte_t : uint8_t {
			// This should be tuned considering WS2812b clock timing
			WS_HIGH = 0xFE, // 0b11111110
			WS_LOW = 0xE0   // 0b11100000
		};

		void SetRgbBufferByID(uint8_t _keyId, Color_t _color, float _brightness);
		void SetSinRgbBufferByID(uint8_t _index, float _brightness);
		void SyncLights();

		float GetBrightness() { return brightness; }
		uint8_t GetLedMode() { return ledMode; }
		float GetRgbBrightnessFactor(uint8_t _index);
		void DecBrightnessFactor(uint8_t _index, float _dec);

		void SetBrightness(float _brightness) { brightness = _brightness; }
		void SetLedMode(uint8_t _ledMode) { ledMode = _ledMode; }
		void SetRgbBrightnessFactor(uint8_t _index, float _value);


		// Lamp efficiency code
		void Update(HWKeyboard _keyboard);

		volatile bool isRgbTxBusy{};

	private:
		SPI_HandleTypeDef* spiHandle;
		uint8_t rgbBuffer[LED_NUMBER][3][8]{};
		uint8_t wsCommit[64] = {0};
		uint8_t brightnessPreDiv = 2; // 1/4
		float brightness = 0.25;
		uint8_t ledMode = 0;

		/*--------RGB Color Values--------*/
		uint8_t color_v = 1;
		bool color_flag = true;
		float rgbBrightnessFactor[KEY_NUMBER] = {0};
		uint16_t angleCount = 0;
		float PI = 3.14159265;
		float HALF_PI = PI / 2;
		float RADIAN_1 = PI / 180;
		uint8_t ANGLE_GAP = 120;
		uint8_t HALF_FF = 0xFF / 2;
};


#endif
