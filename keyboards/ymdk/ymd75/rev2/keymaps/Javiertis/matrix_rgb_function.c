#include QMK_KEYBOARD_H
#include "matrix_rgb_function.h"

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
    static int  default_diff = 255 / 5;
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
