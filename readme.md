# My ultimate Corne keymap

Latest firmware: [firmware.uf2](https://github.com/kjuq/corne_keymap/releases/download/latest/firmware.uf2)

## Build

Initialize the pinned QMK submodule after cloning:

```bash
git submodule update --init --recursive
```

Build with Podman (the default):

```bash
./build.sh
```

Use Docker explicitly when needed:

```bash
./build.sh --runtime docker
```

The result is written to `firmware.uf2`. The build uses the Corne v4.1 mini target
`crkbd/rev4_1/mini` and the QMK commit and container image pinned by this repository.

Run the dependency-free smoke tests with:

```bash
./tests/test_build.sh
```

Enter bootloader mode and use:

```bash
./deploy_uf2.sh
```

## Updating QMK

QMK is tracked as a submodule. Update it deliberately, build with both Podman and
Docker, and verify the GitHub Actions build before committing the new submodule
pointer. Keep the container image digest in `build.conf` fixed as well.

## Actions

```bash
gh run download -n firmware
gh run list
gh run watch
```
