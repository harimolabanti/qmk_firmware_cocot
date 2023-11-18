#pragma once

#ifdef COMBO_TERM
#undef COMBO_TERM
#endif

#define COMBO_ALLOW_ACTION_KEYS
#define COMBO_TERM 36
#define COMBO_TERM_PER_COMBO

#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif

#define TAPPING_TERM 170
#define TAPPING_TERM_PER_KEY
#define TAPPING_TOGGLE 3
