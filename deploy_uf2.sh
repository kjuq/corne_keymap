#!/usr/bin/env bash

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
FIRMWARE="$SCRIPT_DIR/firmware.uf2"
OS="$(uname -s)"

case "$OS" in
	Linux) MNT_DIR=/mnt/RPI-RP2 ;;
	Darwin) MNT_DIR=/Volumes/RPI-RP2 ;;
	*) echo "Unsupported OS: $OS" >&2 && exit 1 ;;
esac

is_bootloader_connected() {
	case "$OS" in
		Linux) lsusb | grep "2e8a:0003" | grep 'Raspberry Pi RP2 Boot' ;;
		# Match the "RP2 Boot" device with vendor ID 0x2e8a (= 11914)
		Darwin) ioreg -p IOUSB -r -l -w0 -n 'RP2 Boot' | grep -E '"idVendor" = 11914$' ;;
	esac
}

if [ "$OS" = Linux ]; then
	sudo umount $MNT_DIR
	sudo rm -rf $MNT_DIR
fi

while ! is_bootloader_connected ; do
	echo 'Waiting for device...' && sleep 1
done

case "$OS" in
	Linux)
		sleep 4 && sudo mount --mkdir /dev/disk/by-label/RPI-RP2 $MNT_DIR
		sleep 4 && sudo cp "$FIRMWARE" $MNT_DIR
		sleep 4 && sudo umount $MNT_DIR
		;;
	Darwin)
		# macOS mounts RPI-RP2 automatically
		while [ ! -d $MNT_DIR ] ; do
			echo 'Waiting for mount...' && sleep 1
		done
		# The device reboots itself after receiving the firmware, so no eject is needed
		cp "$FIRMWARE" $MNT_DIR || exit 1
		;;
esac

echo 'Deploy successful'
