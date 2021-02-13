KEYMAP_NAME=j6s-default

QMK_DIR=${CURDIR}/qmk_firmware

# See qmk_firmware/util/docker_build.sh
# This is a slightly modified version of that script, that
# mounts this folder into the container instead of only
# qmk_firmware. That way the symlink to the keymap works
# correctly.
#
# Note: Building in an extra step is not really required,
#       it would work without. However, it is done to prevent
#       the instructions from being hidden on first build.
flash: ${QMK_DIR} build
	@cat bootloader-mode-instructions.txt
	docker run --rm -it \
		--privileged -v /dev:/dev \
		--user $$(id -u):$$(id -g) \
		-v "$$(pwd):/build" \
		-w /build/qmk_firmware \
		-e ALT_GET_KEYBOARDS=true \
		qmkfm/base_container \
		make "xd75:${KEYMAP_NAME}:flash"

# Flashes the firmware with a forced rebuild before
reflash: | clean flash

# Removes previous builds
clean:
	rm -Rf ${QMK_DIR}/.build/*

# Removes all build dependencies
fullclean:
	rm -Rf ${QMK_DIR}

# Fetches QMK and links the current directory as a keymap
${QMK_DIR}:
	git clone https://github.com/qmk/qmk_firmware.git ${QMK_DIR} --recursive
	cd ${QMK_DIR}/keyboards/xd75/keymaps && ln -s ../../../../ ${KEYMAP_NAME}

# Only builds the firmware locally, does not attempt to flash it
build: ${QMK_DIR}
	docker run --rm -it \
		--privileged -v /dev:/dev \
		--user $$(id -u):$$(id -g) \
		-v "$$(pwd):/build" \
		-w /build/qmk_firmware \
		-e ALT_GET_KEYBOARDS=true \
		qmkfm/base_container \
		make "xd75:${KEYMAP_NAME}"
