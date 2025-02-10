#!/usr/bin/env bash

KBD_BASE="$(ghq root)/github.com/foostan/kbd_firmware"
DST="$KBD_BASE/keyboards/crkbd/qmk/qmk_firmware/rev4_0/config.h"

if command -v gsed &>/dev/null; then
	gsed -i 's/RGB_DISABLE_WHEN_USB_SUSPENDED/RGB_MATRIX_SLEEP/' "$DST"
else
	sed -i 's/RGB_DISABLE_WHEN_USB_SUSPENDED/RGB_MATRIX_SLEEP/' "$DST"
fi
