#!/usr/bin/env bash

# @file		build.sh
# @author	Kerr
# @date		Wed, Nov  2, 2022  6:02:10 PM
# @pkgs		base
# @version	1.0

function clean(){
	echo "Delete CMakeFiles Dirtory"
	rm -rf ./CMakeFiles/
	echo "Delete elf file"
	rm ./HelloWord-Keyboard-fw.elf
	echo "Delete CMakeCache.txt"
	rm CMakeCache.txt
	echo "Delete Makefile.txt"
	rm Makefile
}
[ "$1_1" = "clean_1" ] && clean && exit

cmake ./CMakeList.txt
make

