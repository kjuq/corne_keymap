# My Planck Layout

## Usage

Clone `qmk/qmk_firmware` first

```bash
git clone --recursive https://github.com/qmk/qmk_firmware
```

Then clone `foostan/kdb_firmware`

```bash
git clone --recursive https://github.com/foostan/kbd_firmware
```

Copy components in `kbd_firmware` to `qmk_firmware`

```bash
cd qmk_firmware/keyboards
mkdir crkbd
cd crkbd
cp -r kbd_firmware/keyboards/crkbd/qmk/qmk_firmware/* .
```

Clone this repository

```bash
cd qmk_firmware/keyboards/crkbd
git clone https://github.com/kjuq/corne_keymap
```

Build

```bash
./build.sh
```

## TODO list

- Add the way to supress warnings when development
- Add the way to build the firmware with docker
