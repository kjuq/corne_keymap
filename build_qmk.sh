#!/usr/bin/env bash

# cd to the directory where the script is located
cd "$(dirname "$0")" || exit 1

export PATH="$HOME/Library/xPacks/@xpack-dev-tools/arm-none-eabi-gcc/11.3.1-1.1.2/.content/bin:$PATH"

# kb=crkbd kr=rev4/mini km=corne_keymap make qmk-flash

if command -v qmk > /dev/null 2>&1 ; then
	qmk flash -kb crkbd/rev4_0/mini -km corne_keymap
else
	echo "qmk command not found"
	cd ../../../.. || exit 1
	make crkbd/rev4_0:corne_keymap:dfu-util
fi
