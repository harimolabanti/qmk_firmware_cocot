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

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _BASE = 0,
    _SYM = 1,
    _FN = 2,
    _TRACKBALL = 3,
    _STENO = 4,
};

/*
#define CPI_SW USER00
#define SCRL_SW USER01
#define ROT_R15 USER02
#define ROT_L15 USER03
#define SCRL_MO USER04
#define SCRL_TO USER05
#define SCRL_IN USER06
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
       KC_NO,     KC_Q,     KC_W,     KC_F,     KC_P, KC_B,                                         KC_J,     KC_L,       KC_U,        KC_Y,     KC_DQUO, KC_NO,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
       KC_NO,     KC_A,     KC_R,     KC_S,     KC_T, KC_G,                                         KC_M,     KC_N,        KC_E,       KC_I,        KC_O, KC_NO,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
       KC_NO, KC_Z, KC_X, KC_C, KC_D, KC_V,                                         KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH, KC_NO,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                  _______, _______,  KC_SPC, LT(_FN, KC_ENT), KC_MS_BTN1, KC_MS_BTN2, LT(_SYM, KC_BSPC), KC_LSFT, _______,  _______,
                                                                 KC_WH_U, KC_MS_BTN3,  KC_WH_D, _______, _______, _______
    ),
  [_SYM] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      _______, KC_CIRC, KC_TILD, KC_HASH,  KC_DLR, _______,                                       KC_MINS, KC_7, KC_8, KC_9,  KC_DOT, _______,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      _______, KC_BSLS, KC_AT, KC_EXLM, KC_EQL, _______,                                          KC_PLUS, KC_0, KC_1, KC_2, KC_3,   _______,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      _______, KC_PERC, KC_PIPE, KC_AMPR,  KC_APP, _______,                                       KC_ASTR, KC_4, KC_5, KC_6, KC_SLSH, _______,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                        _______, _______, _______,  _______,  KC_MS_BTN4,             KC_MS_BTN5,  _______,   _______, _______,  _______,
                                                                 KC_PGUP, KC_MS_BTN3,  KC_PGDN, _______, _______, _______
                                                            //`--------------'  `--------------'
    ),
  [_FN] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
     _______, RGB_VAI, RGB_SAI, RGB_TOG, RGB_MOD, TO(_STENO),                                    KC_F13, KC_F7, KC_F8, KC_F9, KC_F11, _______,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
     _______, OSM(MOD_LSFT), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LGUI), SCRL_SW,               KC_F14,KC_F10, KC_F1, KC_F2,  KC_F3, _______,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
     _______,  CPI_SW, ROT_L15, ROT_R15, SCRL_MO, SCRL_TO,                                       KC_F15, KC_F4, KC_F5, KC_F6, KC_F12, _______,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                       _______, _______, _______,  _______,   KC_MS_BTN4,             KC_MS_BTN5,  _______,   _______, _______,  _______,
                                                                 KC_PGUP, KC_MS_BTN3,  KC_PGDN, _______, _______, _______
                                                            //`--------------'  `--------------'
    ),
  [_STENO] = LAYOUT(
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_NO, STN_S1,  STN_TL,  STN_PL,  STN_HL, STN_ST4,                                        STN_NUM, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_NO, STN_S2,  STN_KL,  STN_WL,  STN_RL, STN_ST4,                                        STN_NUM, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
      KC_NO, KC_NO, KC_NO, NK_OFF, NK_ON, TO(_BASE),                                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  //|-------------------------------------------------------|                                   |-------------------------------------------------------|
                           KC_NO, KC_NO, STN_A, STN_O,    KC_MS_BTN4,             KC_MS_BTN5, STN_E, STN_U, KC_NO,  KC_NO,
                                                                 KC_PGUP, KC_MS_BTN3,  KC_PGDN, KC_NO, KC_NO, KC_NO
                                                            //`--------------'  `--------------'
    ),
};

bool get_combo_must_tap(uint16_t index, combo_t *combo) {
    switch (index) {
        case C_N_I:
            return true;
        default:
            return false;
    }
}

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
        // Home-row and other tight combos
        case C_R_S:
        case C_S_T:
            return COMBO_TERM;
        // Vertical combos, very relaxed
        case C_L_N:
        case C_U_E:
        case C_Y_I:
        case C_N_H:
        case C_E_DOT:
            return COMBO_TERM + 55;
        // Regular combos, slightly relaxed
        default:
            return COMBO_TERM + 25;
    }
}

keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 4, .col = 2},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 4, .col = 5},
    .pressed = false
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    }

    return true;
}


void matrix_scan_user(void) {

    if (IS_PRESSED(encoder1_ccw)) {
        encoder1_ccw.pressed = false;
        encoder1_ccw.time = (timer_read() | 1);
        action_exec(encoder1_ccw);
    }

    if (IS_PRESSED(encoder1_cw)) {
        encoder1_cw.pressed = false;
        encoder1_cw.time = (timer_read() | 1);
        action_exec(encoder1_cw);
    }

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
        rgblight_sethsv_range( 0, 0, 0, 0, 2);
        cocot_set_scroll_mode(false);
        break;
    }
    rgblight_set_effect_range( 2, 10);
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

