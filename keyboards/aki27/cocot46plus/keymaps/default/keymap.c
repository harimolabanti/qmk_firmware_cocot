/*
Copyright 2022 aki27

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "quantum.h"
#include "keycodes.h"
#include "combos.h"
#include "keymap_steno.h"
#include "oneshot.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(

        KC_NO, KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_NO,
        KC_NO, KC_A, KC_R, KC_S, KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O, KC_NO,
        KC_NO, KC_Z, KC_X, KC_C, KC_D, KC_V, KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
        _______, _______, KC_SFT_SPC, LA_SYM, KC_MS_BTN1, KC_MS_BTN2, LA_FN, KC_SFT_BSPC, _______, _______,
        KC_WH_U, KC_MS_BTN3, KC_WH_D, _______, _______, _______

        ),
    [_SYM] = LAYOUT(

        _______, _______, KC__AMPR, KC_CIRC, KC_TILD, _______, KC_MINS, KC_7, KC_8, KC_9, KC_DOT, _______,
        _______, KC_PERC,  KC_DLR, KC_HASH, KC_CAPS, TG_MAC, KC_PLUS, KC_1, KC_2, KC_3, KC_0, _______,
        _______, _______, KC__PIPE, KC_BSLS, KC_APP, CG_TOGG, KC_ASTR, KC_4, KC_5, KC_6, KC_SLSH, _______,
        _______, _______, _______, _______, KC_MS_BTN4, KC_MS_BTN5, _______, CANCEL, _______, _______,
        KC_PGUP, KC_MS_BTN3, KC_PGDN, _______, _______, _______

        ),
    [_FN] = LAYOUT(

        _______, KC_F11, KC_F9, KC_F8, KC_F7, _______, TO(_STENO), RGB_MOD, RGB_TOG, RGB_SAI, RGB_VAI, _______,
        _______, KC_F10, KC_F3, KC_F2, KC_F1, KC_CAPS, TO(_SYM), OS_CTRL, OS_SHFT, OS_ALT, OS_CMD, _______,
        _______, KC_F12, KC_F6, KC_F5, KC_F4, _______, TO(_FN), TG_MAC, ROT_R15, ROT_L15, CPI_SW, _______,
        _______, _______, CANCEL, _______, KC_MS_BTN4, KC_MS_BTN5, _______, _______, _______, _______,
                          KC_PGUP, KC_MS_BTN3, KC_PGDN, _______, _______, _______),

    [_STENO] = LAYOUT(
        KC_NO, STN_S1, STN_TL, STN_PL, STN_HL, STN_NUM, STN_ST4, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
        KC_NO, STN_S2, STN_KL, STN_WL, STN_RL, STN_NUM, STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
        KC_NO, CM_OFF, CM_ON, NK_OFF, NK_ON, TO(_BASE), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, STN_A, STN_O, KC_MS_BTN1, KC_MS_BTN2, STN_E, STN_U, KC_NO, KC_NO,
                     KC_PGUP, KC_MS_BTN3, KC_PGDN, KC_NO, KC_NO, KC_NO
        ),
};

#ifdef COMBO_ENABLE
uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        // Vertical combos, very relaxed
        case C_L_N:
        case C_U_E:
        case C_Y_I:
        case C_N_H:
        case C_R_F:
        case C_F_T:
        case C_E_DOT:
        case C_N_U:
        case C_U_I:
        // pinky
        case C_I_O:
        case C_A_R:
        case C_Q_W_F:
            return COMBO_TERM + 55;
        // Regular combos, slightly relaxed
        default:
            return COMBO_TERM;
    }
}
#endif

keyevent_t encoder1_ccw = {.key = (keypos_t){.row = 4, .col = 2}, .pressed = false};

keyevent_t encoder1_cw = {.key = (keypos_t){.row = 4, .col = 5}, .pressed = false};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time    = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time    = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    }

    return true;
}

void matrix_scan_user(void) {
    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time    = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time    = (timer_read() | 1);
        action_exec(encoder1_cw);
    }
}

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_FN:
        case CANCEL:
            return true;
        default:
            return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case LA_SYM:
        case LA_FN:
        case KC_LSFT:
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_CMD:
            return true;
        default:
            return false;
    }
}

void double_tap(uint16_t keycode) {
    tap_code16(keycode);
    tap_code16(keycode);
}

void double_tap_space(uint16_t keycode) {
    tap_code16(KC_SPC);
    double_tap(keycode);
    tap_code16(KC_SPC);
}

void triple_tap(uint16_t keycode) {
    tap_code16(keycode);
    tap_code16(keycode);
    tap_code16(keycode);
}

void double_tap_when_held(uint16_t keycode, keyrecord_t *record) {
  if(!record->tap.count) {
    double_tap_space(keycode);
  } else {
    tap_code16(keycode);
  }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state  = os_up_unqueued;
oneshot_state os_cmd_state  = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(&os_shft_state, KC_LSFT, OS_SHFT, keycode, record);
    update_oneshot(&os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record);
    update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
    update_oneshot(&os_cmd_state, KC_LCMD, OS_CMD, keycode, record);

    switch (keycode) {
        case TG_MAC:
            if (record->event.pressed) {
                _mac = !_mac;
            }
            return false;
        case KC__EQL:
            if (record->event.pressed) {
                double_tap_when_held(keycode, record);
                return false;
            }
            break;
        case KC__AMPR:
            if (record->event.pressed) {
                double_tap_when_held(KC_AMPR, record);
                return false;
            }
            break;
        case KC__PIPE:
            if (record->event.pressed) {
                double_tap_when_held(KC_PIPE, record);
                return false;
            }
            break;
        case KC__EXLM:
            if (record->event.pressed) {
                if(!record->tap.count) {
                  send_string(" != ");
                } else {
                  tap_code16(KC_EXLM);
                }
                return false;
            }
            break;
        case KC__GRV:
            if (!record->tap.count && record->event.pressed) {
                triple_tap(keycode);
                return false;
            }
            break;
        case KC_DEL_WORD:
            if (record->tap.count && record->event.pressed) {
                tap_code16(_mac ? A(KC_DEL) : C(KC_DEL));
                return false;
            }
            break;
        case KC_BSPC_WORD:
            if (record->tap.count && record->event.pressed) {
                tap_code16(_mac ? A(KC_BSPC) : C(KC_BSPC));
                return false;
            }
            break;
        case KC_SAVE_FILE:
            if (record->tap.count && record->event.pressed) {
                tap_code16(_mac ? G(KC_S) : C(KC_S));
                return false;
            }
            break;
        case KC__UNDS:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_UNDS);
                return false;
            }
            break;
        case KC__COLN:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_COLN);
                return false;
            }
            break;
        case KC__DQUO:
            if (record->tap.count && record->event.pressed) {
                tap_code16(KC_DQUO);
                return false;
            }
            break;
    }

    return true;
}

#ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _SYM:
            rgblight_sethsv_range(HSV_BLUE, 0, 2);
            cocot_set_scroll_mode(true);
            break;
        case _FN:
            rgblight_sethsv_range(HSV_RED, 0, 2);
            cocot_set_scroll_mode(true);
            break;
        case _STENO:
            rgblight_sethsv_range(HSV_GREEN, 0, 2);
            cocot_set_scroll_mode(false);
            break;
        default:
            rgblight_sethsv_range(0, 0, 0, 0, 2);
            cocot_set_scroll_mode(false);
            break;
    }
    rgblight_set_effect_range(2, 10);
    return state;
};
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    render_logo();
    oled_write_layer_state();
    return false;
}
#endif
