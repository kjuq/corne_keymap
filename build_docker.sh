#!/usr/bin/env bash

KEYBOARD="crkbd"
TMP_KEYBOARD="tmp$KEYBOARD"
REVISION="rev4_0/mini"
KEYMAP="corne_keymap"
TARGET="$TMP_KEYBOARD/$REVISION:$KEYMAP"

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)"
KBD_BASE="$GHQ_ROOT/github.com/foostan/kbd_firmware"
QMK_BASE="$KBD_BASE/src/qmk/qmk_firmware"
TMP_KEYBOARD_PATH="$QMK_BASE/keyboards/$TMP_KEYBOARD"

# Update `kbd_firmware`
cd "$KBD_BASE" || exit 1
make git-submodule

[ -d "$TMP_KEYBOARD_PATH" ] && rm -fdr "$TMP_KEYBOARD_PATH"
cp -r "$KBD_BASE/keyboards/$KEYBOARD/qmk/qmk_firmware" "$TMP_KEYBOARD_PATH"

mkdir "$TMP_KEYBOARD_PATH/keymaps/corne_keymap"
cp "$SCRIPT_DIR"/* "$TMP_KEYBOARD_PATH"/keymaps/corne_keymap

# Update `kbd_firmware/src/qmk/qmk_firmware`
cd "$QMK_BASE" || exit 1
git submodule init
git submodule update

# Use past version of Docker image (https://github.com/FrameworkComputer/qmk_firmware/issues/42)
cd $QMK_BASE && git restore util/docker_build.sh # Reset just in case
sed -i 's|ghcr.io/qmk/qmk_cli|ghcr.io/qmk/qmk_cli@sha256:d8ebfab96c46d3ab948dd4e87be8a976095bd31268700021a74716cbd6e5b4c1|' $GHQ_ROOT/github.com/foostan/kbd_firmware/src/qmk/qmk_firmware/util/docker_build.sh

export RUNTIME=docker
sudo util/docker_build.sh $TARGET

cd $QMK_BASE && git restore util/docker_build.sh

OUTPUT="${TMP_KEYBOARD}_$(echo $REVISION | sed 's/\//_/')_$KEYMAP.uf2"
[ ! -f "$OUTPUT" ] && exit 1
mv --force "$QMK_BASE/$OUTPUT" "$SCRIPT_DIR/firmware.uf2"

rm -fdr "$TMP_KEYBOARD_PATH"
