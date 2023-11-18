// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later
 
#include QMK_KEYBOARD_H
#include "keymap_steno.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _STENO,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(                                                                                   
    KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,     KC_Y, KC_U,    KC_I,   KC_O,    KC_P, KC_DEL,
    KC_TAB, KC_A, KC_X, KC_C, KC_V, KC_B,     KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
                RGB_TOG, KC_SPC, RGB_MOD,     KC_NO, KC_BSPC, KC_NO
    ),
    [_STENO] = LAYOUT(
    TO(_BASE), STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,     STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR,
    KC_TRNS, STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,     STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR,
                            STN_N1,  STN_A,   STN_O,       STN_E,  STN_U, STN_N2
    )
};
