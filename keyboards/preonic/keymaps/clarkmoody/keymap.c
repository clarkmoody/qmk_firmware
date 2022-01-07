/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"

#define W_SWP G(KC_GRV)

enum preonic_layers {
  _COLEMAK,
  _QWERTY,
  _LWR, // Lower
  _RSE, // Raise
  _ADJ, // Adjust
  _MSE, // Mouse
  _LGT  // Light
};

enum preonic_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY
};

// Tap Dance States
typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD
} td_state_t;

// Tap Dance declarations
enum {
  X_MS // Mouse when tapped, Right GUI when held
};

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance function signatures
td_state_t cur_dance(qk_tap_dance_state_t *state);
void mouse_finished(qk_tap_dance_state_t *state, void *user_data);
void mouse_reset(qk_tap_dance_state_t *state, void *user_data);

// Tap dance definitions. Use TD(X_MS) as keycode.
qk_tap_dance_action_t tap_dance_actions[] = {
  [X_MS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mouse_finished, mouse_reset),
};

// Keymap layouts
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  \|  |   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   D  |   V  |   K  |   H  |   ,  |   .  |   /  |Sh/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Alt | GUI  |      |>LOWER|    Space    |>RAISE| Left | Down |  Up  | Rght |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_1x2uC(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
  KC_BSLS, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
  KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, MO(_LWR),      KC_SPC,     MO(_RSE),KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  \|  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Sh/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Alt | GUI  |      |>LOWER|    Space    |>RAISE| Left | Down |  Up  | Rght |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_1x2uC(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_BSLS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
  KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, MO(_LWR),      KC_SPC,     MO(_RSE),KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower (left thumb)
 * ,-----------------------------------------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ^  |   &  |   *  |   (  |   )  |      |   _  |   +  |   {  |   }  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CAPS |   !  |   @  |   #  |   $  |   %  |      |   -  |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |   `  |   ~  |   (  |   )  |Sh/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Alt | GUI  |      |      |             |>ADJ  | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LWR] = LAYOUT_preonic_1x2uC(
  XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
  KC_CAPS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, XXXXXXX,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_GRV,  KC_TILD, KC_LPRN, KC_RPRN, _______,
  _______, _______, _______, _______, XXXXXXX,      XXXXXXX,     MO(_ADJ),KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Raise (right thumb)
 * ,-----------------------------------------------------------------------------------.
 * | WSWP | F11  | F12  | F13  | F14  | F15  | F16  | F17  | F18  | F19  | F20  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   _  |   +  |   {  |   }  |      |   !  |   @  |   #  |   $  |   %  | Del  |
 * |------+------+------+------+------+------+------+------+------+-------------+------|
 * | CAPS |   -  |   =  |   [  |   ]  |      |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------+------+------+------+------|------+------|
 * | Shift|   `  |   ~  |   (  |   )  |      |      |      |      |   |  |   \  |Sh/Ent|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Alt | GUI  |      |>ADJ  |             |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RSE] = LAYOUT_preonic_1x2uC(
  W_SWP,   KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  _______,
  XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______,
  KC_CAPS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX,
  _______, KC_GRV,  KC_TILD, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, KC_BSLS, _______,
  _______, _______, _______, _______, MO(_ADJ),     XXXXXXX,     XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Adjust & Media (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Reset |      |      |      |      |      |      |      |      |      |      |Debug |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Prev | Next |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Qwerty|Colemk|AGnorm| Audio| Play | Vol- | Vol+ | Mute |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |AGswap|      |      |      |      |      | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |   >MOUSE    |      |      |      |      |>LIGHT|
 * `-----------------------------------------------------------------------------------'
 */
[_ADJ] = LAYOUT_preonic_1x2uC(
  RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DEBUG,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, QWERTY,  COLEMAK, AG_NORM, AU_TOG,  KC_MPLY, KC_VOLD, KC_VOLU, KC_MUTE, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      TO(_MSE),    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(_LGT)
),

/* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |>BASE |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | W LF | W DN | W UP | W RT |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Acc 0 |Acc 1 |Acc 2 |      |      | M LF | M DN | M UP | M RT |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      | BTN1 | BTN2 | BTN3 | BTN4 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Alt | GUI  |      |>LOWER|   Mouse 1   |>RAISE|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MSE] = LAYOUT_preonic_1x2uC(
  TG(_MSE),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX,
  KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, XXXXXXX,
  KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, TG(_MSE),     KC_BTN1,     TG(_MSE),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Lighting
 * ,-----------------------------------------------------------------------------------.
 * |>BASE | RGB1 | RGB2 | RGB3 | RGB4 | RGB5 | RGB6 | RGB7 | RGB8 | RGB9 |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | <RGB>|Toggle|      |      |Toggle|<Back>|      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Eff+ | Bri+ | Sat+ | Hue+ |      |      | BL+  | Step |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Eff- | Bri- | Sat- | Hue- |      |      | BL-  | Brth |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |>LOWER|             |>RAISE|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LGT] = LAYOUT_preonic_1x2uC(
  TG(_LGT),RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,RGB_M_SN,RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, BL_TOGG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, RGB_SPI, RGB_VAI, RGB_SAI, RGB_HUI, XXXXXXX, XXXXXXX, BL_INC,  BL_STEP, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, RGB_SPD, RGB_VAD, RGB_SAD, RGB_HUD, XXXXXXX, XXXXXXX, BL_DEC,  BL_BRTG, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TG(_LGT),     XXXXXXX,     TG(_LGT),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RSE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

// bool music_mask_user(uint16_t keycode) {
//   switch (keycode) {
//     case RAISE:
//     case LOWER:
//       return false;
//     default:
//       return true;
//   }
// }

// Tap Dance state machine that activates the hold mode if interrupted
td_state_t mouse_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      return TD_SINGLE_HOLD;
    } else {
      if (!state->pressed) {
        return TD_SINGLE_TAP;
      } else {
        return TD_SINGLE_HOLD;
      }
    }
  } else {
    return TD_UNKNOWN;
  }
}

// Create an instance of 'td_tap_t' for the 'mouse' tap dance.
static td_tap_t mouse_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void mouse_finished(qk_tap_dance_state_t *state, void *user_data) {
  mouse_tap_state.state = mouse_dance(state);
  switch (mouse_tap_state.state) {
    case TD_SINGLE_TAP:
      layer_on(_MSE);
      break;
    case TD_SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LGUI));
      break;
    default:
      break;
  }
}

void mouse_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (mouse_tap_state.state) {
    case TD_SINGLE_TAP:
      break;
    case TD_SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LGUI));
      break;
    default:
      break;
  }
  mouse_tap_state.state = TD_NONE;
}
