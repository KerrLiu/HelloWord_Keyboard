#pragma once

#ifndef RGB_MATRIX_H
#define RGB_MATRIX_H


#include <cstdint>
#include <lib8tion.h>
#include "rgb_matrix_types.h"
#include "timer.h"

#ifndef RGB_MATRIX_LED_FLUSH_LIMIT
#    define RGB_MATRIX_LED_FLUSH_LIMIT 0
#endif

#ifndef RGB_MATRIX_LED_PROCESS_LIMIT
#    define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5
#endif

#if defined(RGB_MATRIX_LED_PROCESS_LIMIT) && RGB_MATRIX_LED_PROCESS_LIMIT > 0 && RGB_MATRIX_LED_PROCESS_LIMIT < RGB_MATRIX_LED_COUNT
#    if defined(RGB_MATRIX_SPLIT)
#        define RGB_MATRIX_USE_LIMITS(min, max)                                                   \
            uint8_t min = RGB_MATRIX_LED_PROCESS_LIMIT * params->iter;                            \
            uint8_t max = min + RGB_MATRIX_LED_PROCESS_LIMIT;                                     \
            if (max > RGB_MATRIX_LED_COUNT) max = RGB_MATRIX_LED_COUNT;                           \
            uint8_t k_rgb_matrix_split[2] = RGB_MATRIX_SPLIT;                                     \
            if (is_keyboard_left() && (max > k_rgb_matrix_split[0])) max = k_rgb_matrix_split[0]; \
            if (!(is_keyboard_left()) && (min < k_rgb_matrix_split[0])) min = k_rgb_matrix_split[0];
#    else
#        define RGB_MATRIX_USE_LIMITS(min, max)                        \
            uint8_t min = RGB_MATRIX_LED_PROCESS_LIMIT * params->iter; \
            uint8_t max = min + RGB_MATRIX_LED_PROCESS_LIMIT;          \
            if (max > RGB_MATRIX_LED_COUNT) max = RGB_MATRIX_LED_COUNT;
#    endif
#else
#    if defined(RGB_MATRIX_SPLIT)
#        define RGB_MATRIX_USE_LIMITS(min, max)                                                   \
            uint8_t       min                   = 0;                                              \
            uint8_t       max                   = RGB_MATRIX_LED_COUNT;                           \
            const uint8_t k_rgb_matrix_split[2] = RGB_MATRIX_SPLIT;                               \
            if (is_keyboard_left() && (max > k_rgb_matrix_split[0])) max = k_rgb_matrix_split[0]; \
            if (!(is_keyboard_left()) && (min < k_rgb_matrix_split[0])) min = k_rgb_matrix_split[0];
#    else
#        define RGB_MATRIX_USE_LIMITS(min, max) \
            uint8_t min = 0;                    \
            uint8_t max = RGB_MATRIX_LED_COUNT;
#    endif
#endif

#define RGB_MATRIX_INDICATOR_SET_COLOR(i, r, g, b) \
    if (i >= led_min && i < led_max) {             \
        rgb_matrix_set_color(i, r, g, b);          \
    }

#define RGB_MATRIX_TEST_LED_FLAGS() \
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) continue

enum rgb_matrix_effects {
    RGB_MATRIX_NONE = 0,

// --------------------------------------
// -----Begin rgb effect enum macros-----
#define RGB_MATRIX_EFFECT(name, ...) RGB_MATRIX_##name,
#include "rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT

#if defined(RGB_MATRIX_CUSTOM_KB) || defined(RGB_MATRIX_CUSTOM_USER)
#    define RGB_MATRIX_EFFECT(name, ...) RGB_MATRIX_CUSTOM_##name,
#    ifdef RGB_MATRIX_CUSTOM_KB
#        include "rgb_matrix_kb.inc"
#    endif
#    ifdef RGB_MATRIX_CUSTOM_USER
#        include "rgb_matrix_user.inc"
#    endif
#    undef RGB_MATRIX_EFFECT
#endif
    // --------------------------------------
    // -----End rgb effect enum macros-------

    RGB_MATRIX_EFFECT_MAX
};

uint8_t rgb_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i);
uint8_t rgb_matrix_map_row_column_to_led(uint8_t row, uint8_t column, uint8_t *led_i);

void rgb_matrix_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void rgb_matrix_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void process_rgb_matrix(uint8_t row, uint8_t col, bool pressed);

void rgb_matrix_task(void);

// This runs after another backlight effect and replaces
// colors already set
void rgb_matrix_indicators(void);
bool rgb_matrix_indicators_kb(uint8_t anylock);
bool rgb_matrix_indicators_user(uint8_t anylock);

void rgb_matrix_indicators_advanced(effect_params_t *params);
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max);
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max);

void        rgb_matrix_set_suspend_state(bool state);
bool        rgb_matrix_get_suspend_state(void);

void        rgb_matrix_init(void);

static inline bool rgb_matrix_check_finished_leds(uint8_t led_idx) {
#if defined(RGB_MATRIX_SPLIT)
    if (is_keyboard_left()) {
        uint8_t k_rgb_matrix_split[2] = RGB_MATRIX_SPLIT;
        return led_idx < k_rgb_matrix_split[0];
    } else
        return led_idx < RGB_MATRIX_LED_COUNT;
#else
    return led_idx < RGB_MATRIX_LED_COUNT;
#endif
}

// extern const rgb_matrix_driver_t rgb_matrix_driver;

extern rgb_config_t rgb_matrix_config;

extern uint32_t     g_rgb_timer;
extern led_config_t g_led_config;
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
extern last_hit_t g_last_hit_tracker;
#endif
#ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS
extern uint8_t g_rgb_frame_buffer[MATRIX_ROWS][MATRIX_COLS];
#endif

#endif