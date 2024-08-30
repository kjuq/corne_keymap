#!/usr/bin/env bash

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

MNT_DIR=/mnt/RPI-RP2
sudo umount $MNT_DIR
sudo rm -rf $MNT_DIR

while ! lsusb | grep "2e8a:0003" | grep 'Raspberry Pi RP2 Boot' ; do
	echo 'Waiting for device...' && sleep 1
done

sleep 4 && sudo mount --mkdir /dev/disk/by-label/RPI-RP2 $MNT_DIR
sleep 4 && sudo cp "$SCRIPT_DIR/firmware.uf2" $MNT_DIR
sleep 4 && sudo umount $MNT_DIR

echo 'Deploy successful'
