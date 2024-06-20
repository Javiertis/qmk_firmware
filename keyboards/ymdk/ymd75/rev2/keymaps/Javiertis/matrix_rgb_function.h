#pragma once
#include QMK_KEYBOARD_H

// FLAGS FOR LAYERS
#define LED_FLAG_FN 0x10
#define LED_FLAG_CONF 0x20

void rgb_matrix_set_drift_hue(int, int);
