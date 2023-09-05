#pragma once

#include <cstdint>

#if defined(__GNUC__)
#    define PACKED __attribute__((__packed__))
#else
#    define PACKED
#endif

#if defined(_MSC_VER)
#    pragma pack(push, 1)
#endif

typedef struct PACKED {
    uint8_t r, g, b;
}RGB;

typedef struct PACKED {
    uint8_t h;
    uint8_t s;
    uint8_t v;
} HSV;

RGB hsv_to_rgb_impl(HSV hsv);
RGB hsv_to_rgb(HSV hsv);

#if defined(_MSC_VER)
#    pragma pack(pop)
#endif
