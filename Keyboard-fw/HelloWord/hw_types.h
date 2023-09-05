#pragma once

#ifndef HELLO_WORD_KEYBOARD_FW_HW_TYP_H
#define HELLO_WORD_KEYBOARD_FW_HW_TYP_H

#include "hw_core.h"

#if defined(__GNUC__)
#    define PACKED __attribute__((__packed__))
#else
#    define PACKED
#endif

#if defined(_MSC_VER)
#    pragma pack(push, 1)
#endif

#define LSB(_x) ((_x) & 0xFF)
#define MSB(_x) ((_x) >> 8)

#include <stdint.h>
#include <stdbool.h>

#define KEY_REPORT_SIZE 1 + 16
#define RAW_REPORT_SIZE 1 + 32
#define HID_REPORT_SIZE KEY_REPORT_SIZE + RAW_REPORT_SIZE

// typedef enum rgb_task_states { STARTING, RENDERING, FLUSHING, SYNCING } rgb_task_states;

enum Update_State { NORMAL = 0, SENDING, SENDPASS, SENDED };

enum HidPage_t { Keyboard_page = 1, Consumer_page = 3 };

// typedef union {
//   int AnyLock;
//   struct PACKED{
//     bool NumLock;
//     bool CapsLock;
//     bool ScrollLock;
//     bool ComposeLock;
//     bool KanaLock;
//   };
// } kb_lock_state_t;

typedef union {
  struct PACKED {
    uint8_t led_num;
    uint8_t led_caps;
    uint8_t led_scroll;
    uint8_t led_compose;
    uint8_t led_kana;
  };
} kb_lock_led_t;

typedef struct PACKED {
  uint8_t row;
  uint8_t col;
  bool pressed;
} event_t;

typedef struct PACKED {
  uint8_t filter_level;
  uint8_t default_layer;
}keyboard_config_t;

#if defined(_MSC_VER)
#    pragma pack(pop)
#endif

#endif