// Copyright (C) 2019, 2020  Keyboard.io, Inc
//
// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "keycodes.h"
#include "combos.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
         KC_Q, KC_W, KC_F, KC_P, KC_B,        KC_J, KC_L,    KC_U,   KC_Y,  KC_SCLN,
         KC_A, KC_R, KC_S, KC_T, KC_G,        KC_M, KC_N,    KC_E,   KC_I,     KC_O,
         KC_Z, KC_X, KC_C, KC_D, KC_V,        KC_K, KC_H, KC_COMM, KC_DOT,  KC_SLSH,
                    LA_FN, KC_SFT_SPC, KC_SFT_BSPC, LA_SYM ),

  [_SYM] = LAYOUT(
    _______, KC__AMPR, KC_CIRC, KC_TILD, _______,     KC_MINS, KC_7, KC_8, KC_9,  KC_DOT,
    KC_PERC,   KC_DLR, KC_HASH, KC_CAPS,  TG_MAC,     KC_PLUS, KC_1, KC_2, KC_3,    KC_0,
    QK_BOOT, KC__PIPE, KC_BSLS,  KC_APP, CG_TOGG,     KC_ASTR, KC_4, KC_5, KC_6, KC_SLSH,
                                TO(_BASE), _______, _______, TO(_BASE)),

  [_FN] = LAYOUT(
    _______, KC_HOME,   KC_UP,  KC_END, KC_PGUP,     _______, KC_F7, KC_F8, KC_F9, KC_F12,
     KC_ENT, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,     _______, KC_F4, KC_F5, KC_F6, KC_F10,
    KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______,     _______, KC_F1, KC_F2, KC_F3, KC_F11,
                               TO(_BASE), _______, _______, TO(_BASE)),
};

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
