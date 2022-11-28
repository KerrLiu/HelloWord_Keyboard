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
|`Fn` + `Space`|Chang Led Mode|complete|Yes|
|`Fn` + `Up`|Increase brightness|complete|Yes|
|`Fn` + `Down`|Decrease brightness|complete|Yes|
|`Fn` + `Left`|Lifting filter interval|complete|Yes|
|`Fn` + `Right`|Reduce filter interval|complete|Yes|
|`Fn` + `F1`|My Computer|complete|Yes|
|`Fn` + `F2`|Home(www)|complete|Yes|
|`Fn` + `F3`|Mail|complete|Yes|
|`Fn` + `F4`|Media Select|complete|Yes|
|`Fn` + `F5`|Prev|complete|Yes|
|`Fn` + `F6`|Next|complete|Yes|
|`Fn` + `F7`|Play/Pause|complete|Yes|
|`Fn` + `F8`|Stop|complete|Yes|
|`Fn` + `F9`|Volume up|complete|Yes|
|`Fn` + `F10`|Volume down|complete|Yes|
|`Fn` + `F11`|Mute|complete|Yes|
|`Fn` + `F12`|Calculator|complete|Yes|

# Keyboard Layout

## Layout1

```shell
┌───┬───┬───┬───┬───┬───┬─┬───┬───┬───┬───┬─┬───┬───┬───┬───┬─┬───┐
│Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PA │
├───┼───┼───┼───┼───┼───┼─┴─┬─┴─┬─┴─┬─┴─┬─┴─┼───┼───┼───┴───┤ ├───┤
│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┤
│ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  |\ │ │Del│
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ ├───┤
│ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │   Ent  │ │Hom│
├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤ ├───┤
│  Shft  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│ ↑ │ │End│
├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼─┴─┬┬┤
│Ctrl│GUI │Alt │                        │Alt│GUI│Ctl│ ← │ ↓ │ → │││
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
│Ctrl│GUI │Alt │                        │Alt│GUI│Ctl│ ← │ ↓ │ → │││
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
|俊杰|HID SendReport Status|null|
