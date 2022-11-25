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
│Esc│F1&nbsp;│F2&nbsp;│F3&nbsp;│F4&nbsp;│F5&nbsp;│F6&nbsp;│F7&nbsp;│F8&nbsp;│F9&nbsp;│F10│F11│F12│&nbsp;&nbsp;&nbsp;│&nbsp;&nbsp;&nbsp;│PA&nbsp;│<br>
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤<br>
│&nbsp;`&nbsp;│&nbsp;1&nbsp;│&nbsp;2&nbsp;│&nbsp;3&nbsp;│&nbsp;4&nbsp;│&nbsp;5&nbsp;│&nbsp;6&nbsp;│&nbsp;7&nbsp;│&nbsp;8&nbsp;│&nbsp;9&nbsp;│&nbsp;0&nbsp;│&nbsp;-&nbsp;│&nbsp;=&nbsp;│&nbsp;Backsp│Ins│<br>
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤<br>
│&nbsp;Tab&nbsp;│&nbsp;Q&nbsp;│&nbsp;W&nbsp;│&nbsp;E&nbsp;│&nbsp;R&nbsp;│&nbsp;T&nbsp;│&nbsp;Y&nbsp;│&nbsp;U&nbsp;│&nbsp;I&nbsp;│&nbsp;O&nbsp;│&nbsp;P&nbsp;│&nbsp;[&nbsp;│&nbsp;]&nbsp;│&nbsp;&nbsp;|\&nbsp;│Del│<br>
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┴───┤<br>
│&nbsp;Caps&nbsp;│&nbsp;A&nbsp;│&nbsp;S&nbsp;│&nbsp;D&nbsp;│&nbsp;F&nbsp;│&nbsp;G&nbsp;│&nbsp;H&nbsp;│&nbsp;J&nbsp;│&nbsp;K&nbsp;│&nbsp;L&nbsp;│&nbsp;;&nbsp;│&nbsp;'&nbsp;│&nbsp;&nbsp;&nbsp;Ent&nbsp;&nbsp;│Hom│<br>
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤<br>
│Shft│&nbsp;\&nbsp;│&nbsp;Z&nbsp;│&nbsp;X&nbsp;│&nbsp;C&nbsp;│&nbsp;V&nbsp;│&nbsp;B&nbsp;│&nbsp;N&nbsp;│&nbsp;M&nbsp;│&nbsp;,&nbsp;│&nbsp;.&nbsp;│&nbsp;/&nbsp;│&nbsp;Shift│&nbsp;↑&nbsp;│End│<br>
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤<br>
│Ctrl│GUI&nbsp;│Alt&nbsp;│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│Alt│GUI│Ctl│&nbsp;←&nbsp;│&nbsp;↓&nbsp;│&nbsp;→&nbsp;│<br>
└────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘<br>

## Layout2(FN+)

┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐<br>
│Esc│F1&nbsp;│F2&nbsp;│F3&nbsp;│F4&nbsp;│F5&nbsp;│F6&nbsp;│F7&nbsp;│F8&nbsp;│F9&nbsp;│F10│F11│F12│&nbsp;&nbsp;&nbsp;│&nbsp;&nbsp;&nbsp;│PA&nbsp;│<br>
├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤<br>
│&nbsp;`&nbsp;│&nbsp;1&nbsp;│&nbsp;2&nbsp;│&nbsp;3&nbsp;│&nbsp;4&nbsp;│&nbsp;5&nbsp;│&nbsp;6&nbsp;│&nbsp;7&nbsp;│&nbsp;8&nbsp;│&nbsp;9&nbsp;│&nbsp;0&nbsp;│&nbsp;-&nbsp;│&nbsp;=&nbsp;│&nbsp;Backsp│Ins│<br>
├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤<br>
│&nbsp;Tab&nbsp;│&nbsp;Q&nbsp;│&nbsp;W&nbsp;│&nbsp;E&nbsp;│&nbsp;R&nbsp;│&nbsp;T&nbsp;│&nbsp;Y&nbsp;│&nbsp;U&nbsp;│&nbsp;I&nbsp;│&nbsp;O&nbsp;│&nbsp;P&nbsp;│&nbsp;[&nbsp;│&nbsp;]&nbsp;│&nbsp;&nbsp;|\&nbsp;│Del│<br>
├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┴───┤<br>
│&nbsp;Caps&nbsp;│&nbsp;A&nbsp;│&nbsp;S&nbsp;│&nbsp;D&nbsp;│&nbsp;F&nbsp;│&nbsp;G&nbsp;│&nbsp;H&nbsp;│&nbsp;J&nbsp;│&nbsp;K&nbsp;│&nbsp;L&nbsp;│&nbsp;;&nbsp;│&nbsp;'&nbsp;│&nbsp;&nbsp;&nbsp;Ent&nbsp;&nbsp;│PKU│<br>
├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤<br>
│Shft│&nbsp;\&nbsp;│&nbsp;Z&nbsp;│&nbsp;X&nbsp;│&nbsp;C&nbsp;│&nbsp;V&nbsp;│&nbsp;B&nbsp;│&nbsp;N&nbsp;│&nbsp;M&nbsp;│&nbsp;,&nbsp;│&nbsp;.&nbsp;│&nbsp;/&nbsp;│&nbsp;Shift│&nbsp;↑&nbsp;│PKD│<br>
├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤<br>
│Ctrl│GUI&nbsp;│Alt&nbsp;│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;│Alt│GUI│Ctl│&nbsp;←&nbsp;│&nbsp;↓&nbsp;│&nbsp;→&nbsp;│<br>
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
