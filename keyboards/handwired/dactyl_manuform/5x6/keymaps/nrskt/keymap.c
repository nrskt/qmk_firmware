/* A standard layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H

// Define tap
typedef enum {
    TD_NONE,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
  CT_A_F10,
  CT_S_F7,
  CT_LY_1_2,
  CT_LY_2_3,
  CT_MOD,
  CT_XM_SFT,
};

// define custom key
#define TAP_SPC TD(CT_MOD)
#define LY_12   TD(CT_LY_1_2)
#define LY_23   TD(CT_LY_2_3)
#define XM_SW   LGUI(KC_SPC)
#define XM_RST  LGUI(LALT(LSFT(KC_SPC)))
#define XM_60   LGUI(LALT(KC_V))
#define XM_50   LGUI(LALT(KC_SPC))
#define XM_SFT TD(CT_XM_SFT)

td_state_t cur_dance(qk_tap_dance_state_t *state);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_5x6(
        KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5,                           KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_BSPC,
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T,                           KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_MINS, 
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G,                           KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, 
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,                           KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_BSLS, 
                       KC_LBRC, KC_GRV,                                              KC_PLUS, KC_EQL, 
                                  LY_12,       LY_12,            LY_23,           LY_23, 
                                  KC_LCTL,     TAP_SPC,          RSFT_T(KC_BSPC), TD(CT_A_F10), 
                                  XM_SFT,      KC_SPC,           KC_ENT,          TD(CT_S_F7)),

  [1] = LAYOUT_5x6(
        RESET,   KC_F1,   KC_F2,   KC_F3,       KC_F4,       KC_F5,              KC_F6,       KC_F7,       KC_F8,   KC_F9,   KC_F10,  KC_F11, 
        _______, _______, _______, _______,     _______,     _______,            KC_CIRC,     KC_AMPR,     KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, 
        _______, _______, _______, LCTL(KC_F6), LCTL(KC_F7), _______,            KC_LCBR,     KC_RCBR,     KC_LBRC, KC_RBRC, KC_GRV,  KC_RBRC, 
        _______, _______, _______, _______,     _______,     _______,            KC_PLUS,     KC_EQL,      KC_LABK, KC_RABK, KC_QUES, KC_PIPE, 
                          _______, _______,                                                        _______, _______, 
                                              _______, _______,         _______, _______, 
                                              _______, KC_SPC,          _______, KC_F10, 
                                              _______, _______,         _______, KC_F7),
	
  [2] = LAYOUT_5x6(
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, 
        KC_MPRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    _______, _______, _______, _______, _______, _______, 
        KC_MPLY, _______, _______, _______, _______, _______,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, 
        KC_MNXT, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, KC_SLEP, 
                          _______, _______,                                                        _______, _______, 
                                              _______, _______,         _______, _______, 
                                              XM_RST,  XM_SW,           _______, _______, 
                                              XM_60,   XM_50,           _______, _______),

  [3] = LAYOUT_5x6(
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, 
        KC_MPRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    _______, _______, _______, _______, _______, _______, 
        KC_MPLY, _______, _______, _______, _______, _______,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, 
        KC_MNXT, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, KC_SLEP, 
                          _______, _______,                                                        _______, _______, 
                                              _______, _______,            _______, _______, 
                                              _______, _______,            _______, _______, 
                                              _______, _______,            _______, _______)
};

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    bool is_new_dance = QK_TAP_DANCE <= state->interrupting_keycode && state->interrupting_keycode <= QK_TAP_DANCE_MAX;
    if (state->count == 1) {
        if (state->pressed && !is_new_dance) {
            return TD_SINGLE_HOLD;
        } else {
            return TD_SINGLE_TAP;
        }
        // if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        // else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_DOUBLE_HOLD;
    } else return TD_NONE;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t ct_mod_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};


// Tap Dance for space
void ct_mod_finished(qk_tap_dance_state_t *state, void *user_data) {
    ct_mod_tap_state.state = cur_dance(state);
    switch (ct_mod_tap_state.state) {
        case TD_SINGLE_TAP: set_oneshot_mods(MOD_LSFT); break;
        case TD_SINGLE_HOLD: register_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: set_oneshot_layer(1, ONESHOT_START); break;
        case TD_DOUBLE_HOLD: layer_on(1); break;
        case TD_NONE: break;
    }
}

void ct_mod_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (ct_mod_tap_state.state) {
        case TD_SINGLE_TAP: clear_oneshot_mods(); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LSFT); break;
        case TD_DOUBLE_TAP: clear_oneshot_layer_state(ONESHOT_PRESSED); break;
        case TD_DOUBLE_HOLD: layer_off(1); break;
        case TD_NONE: break;
    }
    ct_mod_tap_state.state = TD_NONE;
}

static td_tap_t ct_12_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Tap Dance for mo-1-2
void ct_12_finished(qk_tap_dance_state_t *state, void *user_data) {
    ct_12_tap_state.state = cur_dance(state);
    switch (ct_12_tap_state.state) {
        case TD_SINGLE_TAP: layer_on(1); break;
        case TD_SINGLE_HOLD: layer_on(1); break;
        case TD_DOUBLE_TAP: layer_on(2); break;
        case TD_DOUBLE_HOLD: layer_on(2); break;
        case TD_NONE: break;
    }
}

void ct_12_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (ct_12_tap_state.state) {
        case TD_SINGLE_TAP: layer_off(1); break;
        case TD_SINGLE_HOLD: layer_off(1); break;
        case TD_DOUBLE_TAP: layer_off(2); break;
        case TD_DOUBLE_HOLD: layer_off(2); break;
        case TD_NONE: break;
    }
    ct_12_tap_state.state = TD_NONE;
}

static td_tap_t ct_23_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Tap Dance for mo-2-3
void ct_23_finished(qk_tap_dance_state_t *state, void *user_data) {
    ct_23_tap_state.state = cur_dance(state);
    switch (ct_23_tap_state.state) {
        case TD_SINGLE_TAP: layer_on(2); break;
        case TD_SINGLE_HOLD: layer_on(2); break;
        case TD_DOUBLE_TAP: layer_on(3); break;
        case TD_DOUBLE_HOLD: layer_on(3); break;
        case TD_NONE: break;
    }
}

void ct_23_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (ct_23_tap_state.state) {
        case TD_SINGLE_TAP: layer_off(2); break;
        case TD_SINGLE_HOLD: layer_off(2); break;
        case TD_DOUBLE_TAP: layer_off(3); break;
        case TD_DOUBLE_HOLD: layer_off(3); break;
        case TD_NONE: break;
    }
    ct_23_tap_state.state = TD_NONE;
}

static td_tap_t ct_xm_sft_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};


// Tap Dance for lgui
void ct_xm_sft_finished(qk_tap_dance_state_t *state, void *user_data) {
    ct_xm_sft_tap_state.state = cur_dance(state);
    switch (ct_xm_sft_tap_state.state) {
        case TD_SINGLE_TAP: register_mods(MOD_BIT(KC_LGUI)); break;
        case TD_SINGLE_HOLD: register_mods(MOD_BIT(KC_LGUI)); break;
        case TD_DOUBLE_TAP: 
            register_mods(MOD_BIT(KC_LGUI));
            register_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_DOUBLE_HOLD: 
            register_mods(MOD_BIT(KC_LGUI));
            register_mods(MOD_BIT(KC_LSFT));
            break;
        case TD_NONE: break;
    }
}

void ct_xm_sft_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (ct_xm_sft_tap_state.state) {
        case TD_SINGLE_TAP: clear_mods(); break;
        case TD_SINGLE_HOLD: clear_mods(); break;
        case TD_DOUBLE_TAP: clear_mods(); break;
        case TD_DOUBLE_HOLD: clear_mods(); break;
        case TD_NONE: break;
    }
    ct_xm_sft_tap_state.state = TD_NONE;
}

// All TapDance functions
qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_A_F10] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_F10),
    [CT_S_F7] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_F7),
    [CT_LY_1_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ct_12_finished, ct_12_reset),
    [CT_LY_2_3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ct_23_finished, ct_23_reset),
    [CT_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ct_mod_finished, ct_mod_reset),  
    [CT_XM_SFT] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, RSFT(KC_LGUI)),
};
