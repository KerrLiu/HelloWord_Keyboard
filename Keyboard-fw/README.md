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
|Keys|Effect|Finished condition|
|---|---|---|
|`Fn` + `Space`|Chang Led Mode|complete|
|`Fn` + `Up`|Increase brightness|complete|
|`Fn` + `Down`|Decrease brightness|complete|
|`Fn` + `Left`|Lifting filter interval|complete|
|`Fn` + `Right`|Reduce filter interval|complete|
|`Fn` + `F1`|Open Computer|in progress|
|`Fn` + `F2`|Go DeskTop|in progress|
|`Fn` + `F3`|Open Email|in progress|
|`Fn` + `F4`|Open Music Player|in progress|
|`Fn` + `F5`|Prev|in progress|
|`Fn` + `F6`|Next|in progress|
|`Fn` + `F7`|Play/Pause|in progress|
|`Fn` + `F8`|Stop|in progress|
|`Fn` + `F9`|Volume up|in progress|
|`Fn` + `F10`|Volume down|in progress|
|`Fn` + `F11`|Mute|in progress|
|`Fn` + `F12`|Open Calc|in progress|

# Keyboard Layout

## Layout1

┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐<br>
│Esc│F1&nbsp│F2&nbsp│F3&nbsp│F4&nbsp│F5&nbsp│F6&nbsp│F7&nbsp│F8&nbsp│F9&nbsp│F10│F11│F12│&nbsp&nbsp&nbsp│&nbsp&nbsp&nbsp│PA&nbsp│<br>
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤<br>
│&nbsp`&nbsp│&nbsp1&nbsp│&nbsp2&nbsp│&nbsp3&nbsp│&nbsp4&nbsp│&nbsp5&nbsp│&nbsp6&nbsp│&nbsp7&nbsp│&nbsp8&nbsp│&nbsp9&nbsp│&nbsp0&nbsp│&nbsp-&nbsp│&nbsp=&nbsp│&nbspBacksp│Ins│<br>
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤<br>
│&nbspTab&nbsp│&nbspQ&nbsp│&nbspW&nbsp│&nbspE&nbsp│&nbspR&nbsp│&nbspT&nbsp│&nbspY&nbsp│&nbspU&nbsp│&nbspI&nbsp│&nbspO&nbsp│&nbspP&nbsp│&nbsp[&nbsp│&nbsp]&nbsp│&nbsp&nbsp|\&nbsp│Del│<br>
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┴───┤<br>
│&nbspCaps&nbsp│&nbspA&nbsp│&nbspS&nbsp│&nbspD&nbsp│&nbspF&nbsp│&nbspG&nbsp│&nbspH&nbsp│&nbspJ&nbsp│&nbspK&nbsp│&nbspL&nbsp│&nbsp;&nbsp│&nbsp'&nbsp│&nbsp&nbsp&nbspEnt&nbsp&nbsp│Hom│<br>
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤<br>
│Shft│&nbsp\&nbsp│&nbspZ&nbsp│&nbspX&nbsp│&nbspC&nbsp│&nbspV&nbsp│&nbspB&nbsp│&nbspN&nbsp│&nbspM&nbsp│&nbsp,&nbsp│&nbsp.&nbsp│&nbsp/&nbsp│&nbspShift│&nbsp↑&nbsp│End│<br>
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤<br>
│Ctrl│GUI&nbsp│Alt&nbsp│&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp│Alt│GUI│Ctl│&nbsp←&nbsp│&nbsp↓&nbsp│&nbsp→&nbsp│<br>
└────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘<br>

## Layout2(FN+)

┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐<br>
│Esc│F1&nbsp│F2&nbsp│F3&nbsp│F4&nbsp│F5&nbsp│F6&nbsp│F7&nbsp│F8&nbsp│F9&nbsp│F10│F11│F12│&nbsp&nbsp&nbsp│&nbsp&nbsp&nbsp│PA&nbsp│<br>
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤<br>
│&nbsp`&nbsp│&nbsp1&nbsp│&nbsp2&nbsp│&nbsp3&nbsp│&nbsp4&nbsp│&nbsp5&nbsp│&nbsp6&nbsp│&nbsp7&nbsp│&nbsp8&nbsp│&nbsp9&nbsp│&nbsp0&nbsp│&nbsp-&nbsp│&nbsp=&nbsp│&nbspBacksp│Ins│<br>
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤<br>
│&nbspTab&nbsp│&nbspQ&nbsp│&nbspW&nbsp│&nbspE&nbsp│&nbspR&nbsp│&nbspT&nbsp│&nbspY&nbsp│&nbspU&nbsp│&nbspI&nbsp│&nbspO&nbsp│&nbspP&nbsp│&nbsp[&nbsp│&nbsp]&nbsp│&nbsp&nbsp|\&nbsp│Del│<br>
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┴───┤<br>
│&nbspCaps&nbsp│&nbspA&nbsp│&nbspS&nbsp│&nbspD&nbsp│&nbspF&nbsp│&nbspG&nbsp│&nbspH&nbsp│&nbspJ&nbsp│&nbspK&nbsp│&nbspL&nbsp│&nbsp;&nbsp│&nbsp'&nbsp│&nbsp&nbsp&nbspEnt&nbsp&nbsp│PKU│<br>
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤<br>
│Shft│&nbsp\&nbsp│&nbspZ&nbsp│&nbspX&nbsp│&nbspC&nbsp│&nbspV&nbsp│&nbspB&nbsp│&nbspN&nbsp│&nbspM&nbsp│&nbsp,&nbsp│&nbsp.&nbsp│&nbsp/&nbsp│&nbspShift│&nbsp↑&nbsp│PKD│<br>
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤<br>
│Ctrl│GUI&nbsp│Alt&nbsp│&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp│Alt│GUI│Ctl│&nbsp←&nbsp│&nbsp↓&nbsp│&nbsp→&nbsp│<br>
└────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘<br>

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
