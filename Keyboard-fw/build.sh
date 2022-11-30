#!/usr/bin/env bash

# @file		build.sh
# @author	Kerr
# @date		Wed, Nov  2, 2022  6:02:10 PM
# @pkgs		base
# @version	1.0

function clean(){
	echo "Delete CMakeFiles Dirtory"
	[ -d ./CMakeFiles ] && rm -rf ./CMakeFiles/
	echo "Delete elf file"
	[ -f ./HelloWord-Keyboard-fw.elf ] && rm ./HelloWord-Keyboard-fw.elf
	echo "Delete CMakeCache.txt"
	[ -f ./CMakeCache.txt ] && rm CMakeCache.txt
	echo "Delete Makefile.txt"
	[ -f Makefile ] && rm Makefile
	echo "Delete bin file"
	[ -f HelloWord-Keyboard-fw.bin ] && rm HelloWord-Keyboard-fw.bin
	echo "Delete hex file"
	[ -f HelloWord-Keyboard-fw.hex ] && rm HelloWord-Keyboard-fw.hex
}

[ "$1_1" = "clean_1" ] && clean && exit

cmake ./CMakeLists.txt
make

