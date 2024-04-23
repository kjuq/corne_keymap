#!/usr/bin/env bash

# cd to the directory where the script is located
cd "$(dirname "$0")" || exit 1

export PATH="$HOME/Library/xPacks/@xpack-dev-tools/arm-none-eabi-gcc/11.3.1-1.1.2/.content/bin:$PATH"

cd ../../../../../..
kb=crkbd kr=rev4/mini km=corne_keymap make qmk-flash
