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
|`Fn` + `Left`|Lifting filter interval|complete|NO|
|`Fn` + `Right`|Reduce filter interval|complete|NO|
|`Fn` + `Left_Gui`|Exchange win mac layout|complete|Yes|
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
	KEYSET_LAYOUT_WIN_MAC = 0x6300
	/*------------------------- HID Consumer report data -------------------------*/
};
```

# Keyboard Layout

## Layout1(Win)

```shell
┌───┬───┬───┬───┬───┬───┬─┬───┬───┬───┬───┬─┬───┬───┬───┬───┬─┬───┐
│Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PS │
├───┼───┼───┼───┼───┼───┼─┴─┬─┴─┬─┴─┬─┴─┬─┴─┼───┼───┼───┴───┤ ├───┤
│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┤
│ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  |\ │ │Del│
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┤
│ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │   Ent  │ │Hom│
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤ ├───┤
│  Shft  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │ │End│
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼─┴─┬┬┤
│Ctrl│GUI │Alt │                        │Alt│FN │Ctl│ ← │ ↓ │ → │││
└────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┴┴┘
```

## Layout2(FN+)

```shell
┌───┬───┬───┬───┬───┬───┬─┬───┬───┬───┬───┬─┬───┬───┬───┬───┬─┬───┐
│Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PA │
├───┼───┼───┼───┼───┼───┼─┴─┬─┴─┬─┴─┬─┴─┬─┴─┼───┼───┼───┴───┤ ├───┤
│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┤
│ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  |\ │ │Del│
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┤
│ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │   Ent  │ │PKU│
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤ ├───┤
│  Shft  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │ │PKD│
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼─┴─┬┬┤
│Ctrl│GUI │Alt │                        │Alt│FN │Ctl│ ← │ ↓ │ → │││
└────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┴┴┘
```

## Layout3(Mac)

```shell
┌───┬───┬───┬───┬───┬───┬─┬───┬───┬───┬───┬─┬───┬───┬───┬───┬─┬───┐
│Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PA │
├───┼───┼───┼───┼───┼───┼─┴─┬─┴─┬─┴─┬─┴─┬─┴─┼───┼───┼───┴───┤ ├───┤
│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┤
│ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  |\ │ │Del│
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┤
│ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │   Ent  │ │PKU│
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤ ├───┤
│  Shft  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │ │PKD│
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼─┴─┬┬┤
│Ctrl│Alt │GUI │                        │GUI│FN │Alt│ ← │ ↓ │ → │││
└────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┴┴┘
```

# Task plan
|Task|Finished condition|
|---|---|
|HID Communication|in progress|
|Flash IO|in progress|
|Key Map|in progress|
|Touch Bar|in progress|
|Key Map On Host|in progress|
|Touch Bar On Host|in progress|
|LED Brightness|complete|
|Lighting Effect|in progress|
|Communication To Dynamic|in progress|

## Single Task By Lighting Effect
|Lighting Effect|Finished condition|
|---|---|
|TurnLight|complete|
|Breathing lamp By SinRgb|complete|
|One Button By SinRgb|complete|
|Button Range By SinRgb|complete|
|Gluttonous Snake By SinRgb|in progress|

# Participants
|Name|Code|Email/Git|
|---|---|---|
|Kerr|main|[KerrForLiu](KerrForLiu@gmail.com)|
|Mr. mysterious|Sin Rgb|[krakenCN](https://github.com/krakenCN)|
|Gralerfics|keyNearMap|[Gralerfics](https://github.com/Gralerfics)|
|俊杰|lastHidBuffer|null|
