#pragma once

#include QMK_KEYBOARD_H

#include "quantum.h"

// Can be toggled using TG_MAC key.
static bool _mac = false;

enum custom_keycodes {
    TG_MAC = SAFE_RANGE,
    CANCEL,

    DEL_WORD,
    BSPC_WORD,
    SAVE_FILE,
};

enum layer_number {
    _BASE      = 0,
    _SYM       = 1,
    _FN        = 2,
};

#define LA_FN TT(_FN)
#define LA_SYM TT(_SYM)

#define KC_SFT_SPC SFT_T(KC_SPC)
#define KC_SFT_BSPC SFT_T(KC_BSPC)
#define KC__TAB CTL_T(KC_TAB)
#define KC__ESC ALT_T(KC_ESC)
#define KC__UNDS GUI_T(KC_UNDS)
#define KC__DQUO CTL_T(KC_DQUO)
#define KC__COLN ALT_T(KC_COLN)
#define KC_SAVE_FILE GUI_T(SAVE_FILE)
#define KC_DEL_WORD LCA_T(DEL_WORD)
#define KC_BSPC_WORD LCA_T(BSPC_WORD)

#define KC__EQL LT(0, KC_EQL)
#define KC__EXLM LT(0, KC_EXLM)
#define KC__AMPR LT(0, KC_AMPR)
#define KC__PIPE LT(0, KC_PIPE)
#define KC__GRV LT(0, KC_GRV)
