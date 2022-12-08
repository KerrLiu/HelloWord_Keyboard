#ifndef HELLO_WORD_KEYBOARD_FW_HW_KEYBOARD_H
#define HELLO_WORD_KEYBOARD_FW_HW_KEYBOARD_H

#include "spi.h"
#include "hw_config.h"

class HWKeyboard
{
public:
    explicit HWKeyboard(SPI_HandleTypeDef* _spi) :
        spiHandle(_spi)
    {
        scanBuffer = &spiBuffer[1];

        // Enable clock
        HAL_GPIO_WritePin(CE_GPIO_Port,CE_Pin,GPIO_PIN_RESET);

    }

    uint8_t* ScanKeyStates();
    void ApplyDebounceFilter(uint32_t _filterTimeUs = 100);
    uint8_t* Remap(uint8_t _layer = 1);
    /* void SyncLights(); */
    bool FnPressed();
    bool GetButtonStatus(uint8_t _customId);
    bool KeyPressed(int16_t _key);
    void Press(int16_t _key);
    void Release(int16_t _key);
	void _DelayUs(uint32_t _delayUs = 50);
    uint8_t* GetHidReportBuffer(uint8_t _reportId);
    uint8_t GetTouchBarState(uint8_t _id = 0);
	void SetHidReportBuffer(uint8_t _index, uint8_t _value);
	void ResetHidReportBuffer();

    bool isCapsLocked = false;

private:
    SPI_HandleTypeDef* spiHandle;
    uint8_t spiBuffer[IO_NUMBER / 8 + 1]{};
    uint8_t* scanBuffer;
    uint8_t debounceBuffer[IO_NUMBER / 8 + 1]{};
    uint8_t remapBuffer[IO_NUMBER / 8]{};
    uint8_t hidBuffer[HID_REPORT_SIZE]{};
    /* uint8_t lastHidBuffer[HID_REPORT_SIZE]{}; */
};


#endif
