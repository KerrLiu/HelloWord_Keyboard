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
	echo "Delete map file"
	[ -f HelloWord-Keyboard-fw.map ] && rm HelloWord-Keyboard-fw.map
	exit 0
}

[ "$1" = "clean" ] && clean

cmake ./CMakeLists.txt
make

