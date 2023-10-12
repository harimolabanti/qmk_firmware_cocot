#pragma once

#ifdef COMBO_ENABLE

#ifdef C2
#undef C2
#endif

#ifdef C2A
#undef C2A
#endif

#ifdef C3
#undef C3
#endif

#ifdef C3A
#undef C3A
#endif

#define MS(ms, s) if(_mac) {SEND_STRING(ms);} else {SEND_STRING(s);}
#define PS(s) if(p) {SEND_STRING(s);}
#define PNPMS(ms, mns, s, ns) if(p) {MS(ms, s)} else {MS(mns, ns)}

#define C2(k1, k2, kr)  C_##k1##_##k2,
#define C3(k1, k2, k3, kr) C_##k1##_##k2##_##k3,
#define C2A(k1, k2, act)  C_##k1##_##k2,
#define C3A(k1, k2, k3, act) C_##k1##_##k2##_##k3,
#define C4A(k1, k2, k3, k4, act) C_##k1##_##k2##_##k3##_##k4,
enum myCombos {
#include "combos.def"
    COMBO_LENGTH
};
#undef C2
#undef C2A
#undef C3
#undef C3A
#undef C4A
uint16_t COMBO_LEN = COMBO_LENGTH;

#define C2(k1, k2, kr)  const uint16_t PROGMEM k1##_##k2##_combo[] = {KC_##k1, KC_##k2, COMBO_END};
#define C3(k1, k2, k3, kr)  const uint16_t PROGMEM k1##_##k2##_##k3##_combo[] = {KC_##k1, KC_##k2, KC_##k3, COMBO_END};
#define C2A(k1, k2, act)  const uint16_t PROGMEM k1##_##k2##_combo[] = {KC_##k1, KC_##k2, COMBO_END};
#define C3A(k1, k2, k3, act) const uint16_t PROGMEM k1##_##k2##_##k3##_combo[] = {KC_##k1, KC_##k2, KC_##k3, COMBO_END};
#define C4A(k1, k2, k3, k4, act) const uint16_t PROGMEM k1##_##k2##_##k3##_##k4##_combo[] = {KC_##k1, KC_##k2, KC_##k3, KC_##k4, COMBO_END};
#include "combos.def"
#undef C2
#undef C2A
#undef C3
#undef C3A
#undef C4A

#define C2(k1, k2, kr)  [C_##k1##_##k2] = COMBO(k1##_##k2##_combo, KC_##kr),
#define C3(k1, k2, k3, kr)  [C_##k1##_##k2##_##k3] = COMBO(k1##_##k2##_##k3##_combo, KC_##kr),
#define C2A(k1, k2, act)  [C_##k1##_##k2] = COMBO_ACTION(k1##_##k2##_combo),
#define C3A(k1, k2, k3, act) [C_##k1##_##k2##_##k3] = COMBO_ACTION(k1##_##k2##_##k3##_combo),
#define C4A(k1, k2, k3, k4, act) [C_##k1##_##k2##_##k3##_##k4] = COMBO_ACTION(k1##_##k2##_##k3##_##k4##_combo),
combo_t key_combos[] = {
#include "combos.def"
};
#undef C2
#undef C2A
#undef C3
#undef C3A
#undef C4A

#define C2(k1, k2, kr) 
#define C3(k1, k2, k3, kr)
#define C2A(k1, k2, act)  case C_##k1##_##k2: act break;
#define C3A(k1, k2, k3, act) case C_##k1##_##k2##_##k3: act break;
#define C4A(k1, k2, k3, k4, act) case C_##k1##_##k2##_##k3##_##k4: act break;
void process_combo_event(uint16_t combo_index, bool p) {
  switch(combo_index) {
  #include "combos.def"
  }
}
#undef C2
#undef C2A
#undef C3
#undef C3A
#undef C4A

#undef PS
#undef MS
#undef PNPMS

#endif