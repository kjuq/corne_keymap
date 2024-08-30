#!/usr/bin/env bash

KEYBOARD="crkbd"
TMP_KEYBOARD="tmp$KEYBOARD"
REVISION="rev4_0/mini"
KEYMAP="corne_keymap"
TARGET="$TMP_KEYBOARD/$REVISION:$KEYMAP"

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
cd "$SCRIPT_DIR/../../../../../.." || exit 1
KBD_BASE=$(pwd)
cd "$KBD_BASE/src/qmk/qmk_firmware" || exit 1
QMK_BASE=$(pwd)
TMP_KEYBOARD_PATH="$QMK_BASE/keyboards/$TMP_KEYBOARD"

# Update `kbd_firmware`
cd "$KBD_BASE" || exit 1
make git-submodule

[ ! -d "$TMP_KEYBOARD_PATH" ] && rm -fdr "$TMP_KEYBOARD_PATH"
cp -r "$KBD_BASE/keyboards/$KEYBOARD/qmk/qmk_firmware" "$TMP_KEYBOARD_PATH"

# Update `kbd_firmware/src/qmk/qmk_firmware`
cd "$QMK_BASE" || exit 1
git submodule init
git submodule update

cd "$QMK_BASE" || exit 1
sudo util/docker_build.sh $TARGET || exit 1

OUTPUT="${TMP_KEYBOARD}_$(echo $REVISION | sed 's/\//_/')_$KEYMAP.uf2"
[ ! -f "$OUTPUT" ] && exit 1
mv "$QMK_BASE/$OUTPUT" "$SCRIPT_DIR/firmware.uf2"

rm -fdr "$TMP_KEYBOARD_PATH"
