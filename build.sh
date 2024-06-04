#!/usr/bin/env bash

cd "$(dirname "$0")" || exit 1

cd ../../../../../..

make git-submodule
make qmk-clean
kb=crkbd make qmk-init
kb=crkbd kr=rev4_0/mini km=corne_keymap make qmk-compile
xdg-open ./keyboards/crkbd/qmk/qmk_firmware/.build
