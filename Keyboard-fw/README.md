# Keyboard_fw
HelloWord Keyboard Firmware
# Code specification
```C
/*
* Copyright (C)
* @file         test.c
* @author       Kerr
* @param        argc,argv
* @date         Mon, Oct 31, 2022  5:55:37 PM
* @version      1.0
*/
int main (int argc, char * argv[]){
  uint8_t int_int = 0;
  printf("The int_int Value is = %d", &int_int);
  return 0;
}
```

# Key Combination
|Keys|Effect|Finished condition|Need optimization|
|---|---|---|---|
|`Fn` + `Space`|Chang Led Mode|complete|NO|
|`Fn` + `Up`|Increase brightness|complete|NO|
|`Fn` + `Down`|Decrease brightness|complete|NO|
|`Fn` + `Win`|Exchange win mac layout|complete|Yes|
|`Fn` + `Ins`|Save config to eeprom now|complete|Yes|
|`Fn` + `Tab`|The Rgb led HUE value loop|complete|Yes|
|`Fn` + `F1`|My Computer|complete|NO|
|`Fn` + `F2`|Brightness Up|complete|NO|
|`Fn` + `F3`|Brightness Down|complete|NO|
|`Fn` + `F4`|Media Select|complete|NO|
|`Fn` + `F5`|Prev|complete|NO|
|`Fn` + `F6`|Next|complete|NO|
|`Fn` + `F7`|Play/Pause|complete|NO|
|`Fn` + `F8`|Stop|complete|NO|
|`Fn` + `F9`|Volume up|complete|NO|
|`Fn` + `F10`|Volume down|complete|NO|
|`Fn` + `F11`|Mute|complete|NO|
|`Fn` + `F12`|Calculator|complete|NO|

## Consumer code and Custom code, you can add other Consumer code

```c
enum Consumer_t : int16_t
{
	/*------------------------- HID Consumer report data -------------------------*/
	DISPLAY_BRIGHTNESS_INC = 0x006F, DISPLAY_BRIGHTNESS_DEC = 0x0070, SCAN_NEXT_TRACK = 0x00B5, SCAN_PREV_TRACK = 0x00B6,
	SU_STOP = 0x00B7, PLAY_PAUSE = 0x00CD, SU_MUTE = 0x00E2, BASS_BOOST = 0x00E5,
	LOUDNESS = 0x00E7, SU_VOLUME_INC = 0x00E9, SU_VOLUME_DEC = 0x00EA, BASS_INC = 0x0152,
	BASS_DEC = 0x0153, TREBLE_UP = 0x0154, TREBLE_DOWN = 0x0155, MEDIA_SELECT = 0x0183,
	MAIL = 0x018A, CALCULATOR = 0x0192, MY_COMPUTER = 0x0194,
	WWW_SEARCH = 0x0221, WWW_HOME = 0x0223, WWW_BACK = 0x0224, WWW_FORWARD = 0x0225,
	WWW_STOP = 0x0226, WWW_REFRESH = 0x0227, WWW_FAVORITES = 0x022A,

	/*------------------------- HID Custom data don't send -------------------------*/
    KEYSET_LIGHTMODE = 0x6000,
	KEYSET_BRIGHTNESS_INC = 0x6101,
	KEYSET_BRIGHTNESS_DEC = 0x6100,
	KEYSET_FILTER_LEVEL_INC = 0x6201,
	KEYSET_FILTER_LEVEL_DEC = 0x6200,
	KEYSET_LAYOUT_WIN_MAC = 0x6300,
	KEYSET_CONFIG_SAVE = 0x6400,
    KEYSET_HSV_HUE_LOOP = 0x6500,
	/*------------------------- HID Consumer report data -------------------------*/
};
```

# Task plan
|Task|Finished condition|
|---|---|
|Shortcut keys|Need to modify|
|Transplant QMK Firmware RGB_MATRIX|Need to modify|
|Add Timer|Need to modify|
|Delayed Save config|Need to modify|
|EEPROM save config|Need to modify|
|RAW HID|Developing|
|HOST control config|Need to modify|
|HOST save config|Need to modify|
|Rewrite Keyboard Scan|Developing|
|Touch Bar Slide|Developing|
|Communication To Dynamic|Developing|

# How to Build
1. Copy Layouts director all file replace HelloWord director file
 - `hw_config.h`
 - `hw_layout.h`
 - `hw_layout.cpp`
 - `rgb_matrix_kb.inc` or `rgb_matrix_user.inc`
2. Run `build.sh` or `cmake`

# How to add Layouts
1. File must be created
 - `hw_config.h`
 - `hw_layout.h`
 - `hw_layout.cpp`
2. Optional Create File
 - `rgb_matrix_kb.inc` or `rgb_matrix_user.inc`
3. File Role
 - `hw_config.h` file
  The file contains necessary macro configurations
 - `hw_layout.h` file need `include` `hw_core.h`
  The file is Layouts Keymap
 - `hw_layout.cpp` file need `include` `hw_layout.h`
  The file is add some `extern` `var` and `rewrite` `method`


