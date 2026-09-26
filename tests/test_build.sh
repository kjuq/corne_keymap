#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd -- "$SCRIPT_DIR/.." && pwd)"

fail() {
	echo "FAIL: $*" >&2
	exit 1
}

pass() {
	echo "PASS: $*"
}

# Purpose: prevent a build from silently targeting a different keyboard,
# keymap, output file, or mutable container image.
# Checks: the build target/output values and the QMK image digest are fixed.
# shellcheck disable=SC1091
source "$ROOT_DIR/build.conf"
[[ "$QMK_KEYBOARD" == "crkbd/rev4_1/mini" ]] || fail "unexpected QMK keyboard: $QMK_KEYBOARD"
[[ "$QMK_KEYMAP" == "corne_keymap" ]] || fail "unexpected QMK keymap: $QMK_KEYMAP"
[[ "$QMK_OUTPUT" == "firmware.uf2" ]] || fail "unexpected QMK output: $QMK_OUTPUT"
[[ "$QMK_IMAGE" =~ @sha256:[0-9a-f]{64}$ ]] || fail "QMK image is not digest-pinned"
pass "build target and digest-pinned image"

expected_qmk_commit="$(git -C "$ROOT_DIR" ls-tree HEAD qmk_firmware | awk '{print $3}')"
actual_qmk_commit="$(git -C "$ROOT_DIR/qmk_firmware" rev-parse HEAD)"
# Purpose: keep local builds reproducible with the QMK revision committed here.
# Check: the checked-out submodule commit matches the repository's gitlink.
[[ -n "$expected_qmk_commit" && "$actual_qmk_commit" == "$expected_qmk_commit" ]] || \
	fail "QMK submodule is not at the repository's pinned commit"
pass "QMK submodule is at the pinned commit"

# Purpose: catch shell syntax errors before invoking a container or hardware.
# Check: all build, deploy, and test scripts pass Bash's parser.
bash -n "$ROOT_DIR/build.sh" "$ROOT_DIR/deploy_uf2.sh" "$SCRIPT_DIR/test_build.sh"
pass "Bash syntax"

# Purpose: preserve the documented command-line interface of build.sh.
# Checks: help succeeds and unsupported runtimes are rejected.
"$ROOT_DIR/build.sh" --help >/dev/null
pass "build.sh help"

if "$ROOT_DIR/build.sh" --runtime invalid >/dev/null 2>&1; then
	fail "build.sh accepted an unsupported runtime"
fi
pass "unsupported runtime is rejected"

if (($#)); then
	firmware="$1"
	# Purpose: ensure the build produced a usable UF2 rather than an arbitrary file.
	# Checks: the file exists, has complete 512-byte blocks, and has UF2 magic values.
	[[ -f "$firmware" ]] || fail "missing firmware: $firmware"

	size="$(stat -c '%s' "$firmware")"
	((size > 0 && size % 512 == 0)) || fail "UF2 size is not a positive multiple of 512: $size"

	magic_start="$(od -An -tx4 -N4 "$firmware" | tr -d '[:space:]')"
	magic_flags="$(od -An -tx4 -j4 -N4 "$firmware" | tr -d '[:space:]')"
	magic_end="$(od -An -tx4 -j$((size - 4)) -N4 "$firmware" | tr -d '[:space:]')"
	[[ "$magic_start" == "0a324655" ]] || fail "invalid UF2 start magic: $magic_start"
	[[ "$magic_flags" == "9e5d5157" ]] || fail "invalid UF2 flags magic: $magic_flags"
	[[ "$magic_end" == "0ab16f30" ]] || fail "invalid UF2 end magic: $magic_end"

	pass "UF2 format ($firmware, $size bytes)"
else
	echo "Build configuration checks completed"
fi
