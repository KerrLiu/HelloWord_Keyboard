#ifndef HELLO_WORD_KEYBOARD_FW_HW_TOUCHBAR_H
#define HELLO_WORD_KEYBOARD_FW_HW_TOUCHBAR_H

#include "cstdint"
#include "hw_keyboard.h"

class HW_TOUCHBAR{
public:
  explicit HW_TOUCHBAR(){
    action_type = NO_ACTION;
    action_state = 0;
    barTouched = false;
  }

  enum Touchbar_action : uint8_t{
    NO_ACTION = 0,
    ALL_RIGHT_SLIDING, ALL_LEFT_SLIDING, SHORT_RIGHT_SLIDING, SHORT_LEFT_SLIDING, 
    RIGHT_PULL_UP, LEFT_PULL_UP, CLICK, DOUBLE_CLICK
  };

  void Task();
  void GetTouchbarKeyState();
  void Action();
  uint8_t GetTouchbarActionType(){ return action_type; }
  uint8_t GetTouchbarActionState(){ return action_state; }
private:
  uint8_t barBuffer[TOUCHPAD_NUMBER] = {0};
  uint8_t lastbarBuffer[TOUCHPAD_NUMBER] = {0};
  uint8_t action_type;
  uint8_t action_state;
  bool barTouched;
};
#endif
