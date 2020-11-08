#include <time.h>
#include "analog.h"
#include QMK_KEYBOARD_H

#define PWDLEN 14

char pwcharset[] = "wertypasdfhijkzxcvbnmQWERTYUPASFGHJKLXCVNM234579%&!#$";
char pw[PWDLEN+1] = {0};
bool seedisset = false;

enum custom_keycodes {
    OPMWP = SAFE_RANGE,
    MEME1,
    MEME2,
    MEME3,
    MEME4,
    MEME5,
    MEME6,
    MEME7
};

int rand_lim(int limit) {
    
    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}

void pwgen(char *pwbuf){
    if (!seedisset){
        seedisset = true;
        srand((timer_read32() >> 1) ^ (analogReadPin(F7) << 1)); 
    }
    for(int i = 0; i < PWDLEN; i++){
        if ((i+1) % 5 == 0) 
            pwbuf[i] = 45; // -
        else
            pwbuf[i] = pwcharset[rand_lim(sizeof(pwcharset)-2)];
    }
    return;
}

/*
 * 
 */

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case OPMWP:
      if (record->event.pressed) {
        send_string("Operator must wear protection! Serious eye damage may occur!");
      } else {
        // NOOP
      }
    break;
    
    case MEME1:
      if (record->event.pressed) {
        send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
      } else {
        // NOOP
      }
    break;
    
    case MEME2:
      if (record->event.pressed) {
        send_unicode_string("(づ￣ ³￣)づ");
      } else {
        // NOOP
      }
    break;
    
    case MEME3:
      if (record->event.pressed) {
        send_unicode_string("╭∩╮(-_-)╭∩╮");
      } else {
        // NOOP
      }
    break;
    
    case MEME4:
      if (record->event.pressed) {
        send_unicode_string("(╯°□°）╯彡 ┻━┻");
      } else {
        // NOOP
      }
    break;
    
    case MEME5:
      if (record->event.pressed) {
        send_unicode_string("(ㆆ_ㆆ)");
      } else {
        // NOOP
      }
    break;
    
    case MEME6:
      if (record->event.pressed) {
        send_unicode_string("(╥﹏╥)");
      } else {
        // NOOP
      }
    break;
    
    case MEME7:
      if (record->event.pressed) {
        pwgen(pw);
        send_string(pw);
        memset(pw, 0, sizeof(pw));
      } else {
        // NOOP
      }
    break;
  }
  return true;
}

void matrix_init_user(void) {
    set_unicode_input_mode(UC_LNX);
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = KEYMAP(KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, \
                 KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_LBRC, KC_RBRC, \
                 KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_SCLN, KC_QUOT, KC_SLSH, KC_ENT, \
                 KC_LCTL, KC_LALT, KC_LGUI, KC_APP, MO(1), KC_SPC, KC_SPC, MO(2), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),
	[1] = KEYMAP(KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
                 KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_UNDS, KC_PLUS, KC_PIPE, KC_LCBR, KC_RCBR, \
                 KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, LSFT(KC_NUHS), LSFT(KC_BSLS), KC_COMM, KC_DOT, KC_TRNS, \
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY),
	[2] = KEYMAP(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, \
                 KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_MINS, KC_EQL, KC_BSLS, KC_LBRC, KC_RBRC, \
                 KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NUHS, KC_BSLS, KC_COMM, KC_DOT, KC_TRNS, \
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS, KC_TRNS, KC_TRNS, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY),
	[3] = KEYMAP(KC_TRNS, RESET, OPMWP, KC_EXEC, KC_AGIN, AG_NORM, AG_SWAP, MEME1, KC_PSCR, KC_SLCK, KC_PAUS, KC_DEL, \
                 KC_TRNS, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, MEME2, MEME3, KC_INS, KC_HOME, KC_TRNS, \
                 KC_TRNS, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, MEME4, MEME5, MEME6, MEME7, KC_TRNS, KC_TRNS, \
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};


