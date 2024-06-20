#include QMK_KEYBOARD_H
#include "keymap_spanish.h"
#include "config.h"
#include "matrix_rgb_function.h"

void keyboard_post_init_user(void) {
    // Call the post init code.
     rgb_matrix_reload_from_eeprom();
     rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
};
enum custom_keycodes { // Make sure have the awesome keycode ready
  RGB_RESET = SAFE_RANGE,
    RGB_SAVE,
};
enum {
    TD_LSFT_CAPS,
    TD_END_HOME,
    TD_PGDN_PGUP,
};
// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_END_HOME]  = ACTION_TAP_DANCE_DOUBLE(KC_END, KC_HOME),
    [TD_PGDN_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_PAGE_DOWN, KC_PAGE_UP),
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_75_iso(
        //-------------
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SCRL, KC_PAUS,
        //-------------
        ES_MORD, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, ES_QUOT, ES_IEXL, KC_BSPC, KC_INS,
        //-------------
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, ES_GRV, ES_PLUS, KC_DEL,
        //-------------
        TD(TD_LSFT_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, ES_NTIL, ES_ACUT, ES_CCED, KC_ENT, TD(TD_PGDN_PGUP),
                            //-------------
                            KC_LSFT, ES_LABK, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, ES_COMM, ES_DOT, ES_MINS, KC_RSFT, KC_UP, TD(TD_END_HOME),
                            //-------------
                            KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
                            //-------------
    ),
    [_FN] = LAYOUT_75_iso(
        //-------------
        _______, _______, _______, _______, _______, QK_MACRO_1, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_VOLD, KC_MUTE,
        //-------------
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_CALC,
        //-------------
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG,
        //-------------
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAI, RGB_RESET, KC_PGUP,
        //-------------
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_VAI, KC_HOME,
        //-------------
        _______, _______, _______, OSL(_CONF), _______, _______, _______, RGB_HUD, RGB_VAD, RGB_HUI),
        [_CONF] = LAYOUT_75_iso(
            //-------------
            QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PWR,
            //-------------
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            //-------------
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            //-------------
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAVE, _______,
            //-------------
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            //-------------
            QK_REBOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case RGB_RESET:
            if (record->event.pressed)  rgb_matrix_reload_from_eeprom();
            return false;
        case RGB_SAVE:
            if (record->event.pressed)  rgb_matrix_sethsv( rgb_matrix_get_hue(),  rgb_matrix_get_sat(),  rgb_matrix_get_val());
            return false;
        case RGB_HUI:
            if (record->event.pressed)  rgb_matrix_increase_hue_noeeprom();
            return false;
        case RGB_HUD:
            if (record->event.pressed)  rgb_matrix_decrease_hue_noeeprom();
            return false;
        case RGB_SAI:
            if (record->event.pressed)  rgb_matrix_increase_sat_noeeprom();
            return false;
        case RGB_SAD:
            if (record->event.pressed)  rgb_matrix_decrease_sat_noeeprom();
            return false;
        case RGB_VAI:
            if (record->event.pressed)  rgb_matrix_increase_val_noeeprom();
            return false;
        case RGB_VAD:
            if (record->event.pressed)  rgb_matrix_decrease_val_noeeprom();
            return false;
        case RGB_TOG:
            if (record->event.pressed)  rgb_matrix_toggle_noeeprom();
            return false;
        case QK_MACRO_1:
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LSFT("s")) SS_LCTL("j") "qmk compile");
                tap_code(KC_ENTER);
            }
            return false;
    }
    return true;
};


led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {0, 1, 2, 3, 4, 5, 6},
        {0, 1, 2, 3, 4, 5, 6},
    },
    {
        // LED Index to Physical Position
        {16, 13},
        {48, 13},
        {80, 13},
        {112, 13},
        {144, 13},
        {176, 13},
        {208, 13},
        {208, 51},
        {176, 51},
        {144, 51},
        {112, 51},
        {80, 51},
        {48, 51},
        {16, 51},
    },
    {
        // LED Index to Flag
        LED_FLAG_ALL,
        LED_FLAG_FN,
        LED_FLAG_CONF,
        LED_FLAG_ALL,
        LED_FLAG_CONF,
        LED_FLAG_FN,
        LED_FLAG_ALL,
        LED_FLAG_MODIFIER,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_INDICATOR,
        LED_FLAG_ALL,
        LED_FLAG_INDICATOR,
        LED_FLAG_KEYLIGHT,
        LED_FLAG_MODIFIER,
    },
};


void  rgb_matrix_set_drift_hue(int index, int diff) {
    RGB rgb = hsv_to_rgb((HSV){h :  rgb_matrix_get_hue() + diff, s :  rgb_matrix_get_sat(), v :  rgb_matrix_get_val()});
     rgb_matrix_set_color( index,rgb.r, rgb.g, rgb.b);
};

bool  rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // default state of mods
    static bool shift        = false;
    static bool ctrl         = false;
    static bool alt          = false;
    static int  default_diff = 256 / 6;
    // checks if pressed either key
    shift = get_mods() & MOD_MASK_SHIFT;
    ctrl  = get_mods() & MOD_MASK_CTRL;
    alt   = get_mods() & MOD_MASK_ALT;
    // loops over led matrix checks if led has flag and key is pressed or layer active:
    //  change current color hue and set it to the led
    for (uint8_t i = led_min; i <= led_max; i++) {
        if ((shift ^ host_keyboard_led_state().caps_lock) && HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
             rgb_matrix_set_drift_hue(i, default_diff * 3);
        }
        if (ctrl && HAS_FLAGS(g_led_config.flags[i], LED_FLAG_KEYLIGHT)) {
             rgb_matrix_set_drift_hue(i, default_diff * 1);
        }
        if (alt && HAS_FLAGS(g_led_config.flags[i], LED_FLAG_INDICATOR)) {
             rgb_matrix_set_drift_hue(i, default_diff * -2);
        }
        if (IS_LAYER_ON(_FN) && HAS_FLAGS(g_led_config.flags[i], LED_FLAG_FN)) {
             rgb_matrix_set_drift_hue(i, default_diff * -1);
        }
        if (IS_LAYER_ON(_CONF) && HAS_FLAGS(g_led_config.flags[i], LED_FLAG_CONF)) {
             rgb_matrix_set_drift_hue(i, default_diff * 2);
        }
    }
    return false;
}
