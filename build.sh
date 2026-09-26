#!/usr/bin/env bash

set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
# shellcheck disable=SC1091
source "$SCRIPT_DIR/build.conf"

runtime="podman"

usage() {
	cat <<'EOF'
Usage: ./build.sh [--runtime podman|docker]

Build the Corne v4.1 mini firmware using the pinned QMK container.
EOF
}

while (($#)); do
	case "$1" in
		--runtime)
			(($# >= 2)) || { echo "--runtime requires podman or docker" >&2; exit 2; }
			runtime="$2"
			shift 2
			;;
		-h|--help)
			usage
			exit 0
			;;
		*)
			echo "unknown option: $1" >&2
			usage >&2
			exit 2
			;;
	esac
done

case "$runtime" in
	podman|docker) ;;
	*)
		echo "unsupported runtime: $runtime (use podman or docker)" >&2
		exit 2
		;;
esac

command -v "$runtime" >/dev/null 2>&1 || {
	echo "$runtime is not installed; choose the other runtime with --runtime" >&2
	exit 1
}

[[ -f "$SCRIPT_DIR/qmk_firmware/requirements.txt" ]] || {
	echo "qmk_firmware is not initialized; run: git submodule update --init --recursive" >&2
	exit 1
}

echo "Building $QMK_KEYBOARD:$QMK_KEYMAP with $runtime"
echo "QMK commit: $(git -C "$SCRIPT_DIR/qmk_firmware" rev-parse HEAD)"
echo "QMK image:  $QMK_IMAGE"

qmk_target_file="$(printf '%s' "$QMK_KEYBOARD" | tr '/' '_')_${QMK_KEYMAP}.uf2"

# Firmware files are build outputs and are ignored by git.
rm -f "$SCRIPT_DIR/$QMK_OUTPUT" "$SCRIPT_DIR/$qmk_target_file" "$SCRIPT_DIR/qmk_firmware/$qmk_target_file"

"$runtime" run --rm -i \
	-w /qmk_userspace \
	-v "$SCRIPT_DIR:/qmk_userspace:Z" \
	-v "$SCRIPT_DIR/qmk_firmware:/qmk_firmware:Z" \
	-e QMK_USERSPACE=/qmk_userspace \
	-e SKIP_GIT=yes \
	"$QMK_IMAGE" \
	bash -c "qmk config user.qmk_home=/qmk_firmware && qmk config user.overlay_dir=/qmk_userspace && qmk compile -kb '$QMK_KEYBOARD' -km '$QMK_KEYMAP'"

if [[ ! -f "$SCRIPT_DIR/$qmk_target_file" ]]; then
	echo "expected UF2 output not found: $qmk_target_file" >&2
	exit 1
fi

mv -- "$SCRIPT_DIR/$qmk_target_file" "$SCRIPT_DIR/$QMK_OUTPUT"
echo "Wrote $SCRIPT_DIR/$QMK_OUTPUT"
