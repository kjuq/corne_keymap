#!/usr/bin/env bash

# cd to the directory where the script is located
cd "$(dirname "$0")" || exit 1

if command -v gsed &> /dev/null; then
    gsed -i 's/RGB_DISABLE_WHEN_USB_SUSPENDED/RGB_MATRIX_SLEEP/' ../../rev4/config.h
else
    sed -i 's/RGB_DISABLE_WHEN_USB_SUSPENDED/RGB_MATRIX_SLEEP/' ../../rev4/config.h
fi
