#pragma once

#include QMK_KEYBOARD_H

#include "quantum.h"

// Can be toggled using TG_MAC key.
static bool _mac = true;

enum custom_keycodes {
    // Direct dead keys ~`^
    TG_MAC = SAFE_RANGE,

    // Vim
    SAVE_VIM,
    VIM_VS,
    VIM_SP,
    CLOSE_WIN,

    // Smart caps lock and layers that turn off on certain keys
    CAPSWORD,
    NUMWORD,

    // Instant leader key
    LEADER,
};

#define KC_GUI_H GUI_T(KC_H)
#define KC_CTL_COMM CTL_T(KC_COMM)
#define KC_ALT_DOT ALT_T(KC_DOT)
#define KC_SFT_SLSH SFT_T(KC_SLSH)

#define KC_GUI_D GUI_T(KC_D)
#define KC_CTL_C CTL_T(KC_C)
#define KC_ALT_X ALT_T(KC_X)
#define KC_SFT_Z SFT_T(KC_Z)