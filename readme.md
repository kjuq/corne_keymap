# My Planck Layout

## Usage

Clone `kdb_firmware` first

```bash
git clone --recursive https://github.com/foostan/kbd_firmware
```

Clone this repository

```bash
cd kbd_firmware/keyboards/crkbd/qmk/qmk_firmware/keymaps
git clone https://github.com/kjuq/corne_keymap
```

Build

```bash
./build.sh
# or if you prefer docker
./build_docker.sh
```

## TODO list

- Add the way to supress warnings when development
- Add the way to build the firmware with docker
