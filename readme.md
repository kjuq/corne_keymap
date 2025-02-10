# My ultimate Corne keymap

---

# Build with docker

```bash
ghq get --no-recursive https://github.com/foostan/kbd_firmware
cd $GHQ_ROOT/github.com/foostan/kbd_firmware
git reset --hard e9e0dd694f4fc92249a4b161fa4387339d9bc420
bash $GHQ_ROOT/github.com/kjuq/corne_keymap/build_docker.sh
```

# Development

To use clangd and suppress inconpatible flags' errors

```bash
nvim qmk_firmware/.clangd
```

Append them to `CompileFlags/Remove`

```yaml
---
CompileFlags:
  Remove:
    - -mcpu=*
    - -mfpu=*
    - -mfloat-abi=*
    - -mno-unaligned-access
```

It should be like below

```yaml
CompileFlags:
  Add: [-Wno-unknown-attributes, -Wno-maybe-uninitialized, -Wno-unknown-warning-option]
  Remove: [-W*, -mcall-prologues]
  Compiler: clang
---
CompileFlags:
  Remove:
    - -mcpu=*
    - -mfpu=*
    - -mfloat-abi=*
    - -mno-unaligned-access
```

# TODO list

#todo

- Build with latest qmk_firmware
- Build with GitHub Actions

---

**The instructions below *are outdated.***

<details>
	<summary>Outdated instructions. Do ignore.</summary>

## Usage (`foostan/kbd_firmware`)

Clone `foostan/kbd_firmware`

```sh
git clone --recursive https://github.com/foostan/kbd_firmware
```

Clone this repository

```sh
cd kbd_firmware/keyboards/crkbd/qmk/qmk_firmware/keymaps
git clone https://github.com/kjuq/corne_keymap
```

Build

```sh
cd corne_keymap
./build.sh
```

## Usage (`qmk/qmk_firmware`)

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
cd qmk_firmware/keyboards/crkbd/keymaps
git clone https://github.com/kjuq/corne_keymap
```

Build

```bash
./build_qmk.sh
```
