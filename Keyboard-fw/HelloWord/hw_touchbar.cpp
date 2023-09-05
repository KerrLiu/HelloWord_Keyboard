#include "hw_touchbar.h"
#include <cstdint>
#include <cstring>

extern HWKeyboard keyboard;

void HW_TOUCHBAR::GetTouchbarKeyState(){
  for (uint8_t i = 0; i < TOUCHPAD_NUMBER; i++) {
    if(keyboard.GetTouchBarState(i + 1)){
      barBuffer[i] = 1;
      barTouched = true;
    }else{
      barBuffer[i] = 0;
    }
  }
}

void HW_TOUCHBAR::Action(){
  if (memcmp(barBuffer, lastbarBuffer, TOUCHPAD_NUMBER)) {
    if (barTouched) {
      
    }else{

    }
  }else{

  }
}

void HW_TOUCHBAR::Task(){
  GetTouchbarActionState();
  Action();
}
