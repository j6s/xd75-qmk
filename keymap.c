#include QMK_KEYBOARD_H
#include "sendstring_colemak.h"
#include "rgblight.h"

#define L0 0
#define L1 1

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here

  CUSTOM_TEST_KEY,
};

/*
 * A note about alternative keyboard layouts:
 * If you are using an alternative keyboard layout (e.g. colemak)
 * then you will still need to build your hardware layout based on QWERTY
 * since your custom layout is handled in software in your OS.
 * 
 * You can however build a keyboard emulation layer to emulate your
 * keyboard layout in hardware when the keyboard is being used on a
 * PC set to QWERTY.
 * 
 * This could be resolved by using `keymap_colemak.h` but that will make
 * the layout less portable in the end. Thus, this keyboard layout is
 * built for QWERTY despite being used in colemak. A notable excludsion is
 * `sendstring_colemak.h` which is being included in order for the `SEND_STRING`
 * macro to be used with colemak.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *
     * # Main Layer
     * Keys in square brackets `[L1]` indicate momentary layer switching to
     * The layer in brackets - that layer will be active while the key is
     * being held down.
     * 
     * For full documentation of available options
     * @see https://docs.qmk.fm/#/keycodes
     *
     * Double Bound keys:
     * Some keys in the middle of the keyboard (e.g. 5/6 and B/N) are bound to the left and
     * the right side in order to have them available to both hands.
     *
     * 
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | Esc    | 1      | 2      | 3      | 4      | 5      | 6      |        | 6      | 7      | 8      | 9      | 0      | -      | =      |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
     * | Tab    | Q      | W      | E      | R      | T      | F5     |        | F8     | Y      | U      | I      | O      | P      | \      |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
     * | BkSpc  | A      | S      | D      | F      | G      | F6     |        | F7     | H      | J      | K      | L      | ;      | '      |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
     * | LShift | Z      | X      | C      | V      | B      | N      | up     | B      | N      | M      | ,      | .      | /      | rShift |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
     * | LCtrl  | lWin   | lAlt   | Space   | Space  | Space  | left  | down   | right | Enter   | [L1]   | rAlt   | [      | ]      | rCtrl  |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     *
     * NOTE: Temporarily, the whole middle lower row is spaces to help with an injury
     */
    [L0] = LAYOUT_ortho_5x15(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQUAL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_F5,   _______, KC_F8,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        KC_BSPC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_F6,   _______, KC_F7,   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    _______, KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LWIN, KC_LALT, KC_SPC, KC_SPC,  KC_SPC,  KC_SPC,   KC_SPC,  KC_SPC,  KC_ENT,  MO(L1),  KC_RALT, KC_LBRC, KC_RBRC, KC_RCTL
    ),

    /*
     * .--------------------------------------------------------------------------------------------------------------------------------------.
     * | `~     | F1     | F2     | F3     | F4     | F5     | F6     | RESET  | F6     | F7     | F8     | F9     | F10    | F11    | F12    |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |  PgUp  |  up    | PgDn   |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        | left   | down   | right  |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        |        | Vol +  |        |        | home   |        |  end   |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * |        |        |        |        |        |        | prev   | Vol -  | next   |        |        | FN     |        |        |        |
     * '--------------------------------------------------------------------------------------------------------------------------------------'
     */
    [L1] = LAYOUT_ortho_5x15(
        KC_GRAVE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   RESET,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,  KC_F12,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_UP,   KC_PGDN,  _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______, KC_HOME, _______, KC_END,   _______, _______,
        _______,  MO(L1),  _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, MO(L1),  _______,  _______, CUSTOM_TEST_KEY
    ),

    // /*
    //  * Empty layer below. Copy & paste for quicker layer generation.
    //  * 
    //  * .--------------------------------------------------------------------------------------------------------------------------------------.
    //  * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    //  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    //  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    //  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    //  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
    //  * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
    //  * '--------------------------------------------------------------------------------------------------------------------------------------'
    //  */
    // [YOUR_LAYER_NAME] = LAYOUT_ortho_5x15(
    //     _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
    // ),

};

/*
 * This method can be used to add custom macros into the keyboard
 * layout. First, add your custom keycode name into `custom_keycodes`
 * then, you can react to the press event here.
 * 
 * Return `false` to not handle the event further, return `true` if you
 * want qmk to handle the keyboard event.
 * 
 * @see https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch (keycode) {

    case CUSTOM_TEST_KEY:
      if (record->event.pressed) {
        SEND_STRING("THIS IS A TEST");
      }
      return false;

    // Blue LED to indicate bootloader mode
    case RESET:
      rgblight_setrgb(0, 0, 255);
      return true;

  }
  return true;
}


/*
 * Runs just one time when the keyboard initializes.
 */
void matrix_init_user(void) {
  rgblight_setrgb(0, 0, 0);
};

/*
 * Runs constantly in the background, in a loop.
 */
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  switch (layer) {

    case L0:
      rgblight_setrgb(128, 128, 128);
      break;

    case L1:
      rgblight_setrgb(255, 0, 0);
      break;

  }
};
