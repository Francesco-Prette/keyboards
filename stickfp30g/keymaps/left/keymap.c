// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

//#include QMK_KEYBOARD_H
//#include "action.h"
//#include "joystick.h"
//#include "mousekey.h"
//#include "print.h"
#include "custom-functions/joystick.c"
#include "custom-functions/oled.c"
#define default 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │
     * ├───┼───┼───┼───┼───┼───┤
     * │TAB│ q │ w │ e │ r │ t │
     * ├───┼───┼───┼───┼───┼───┤
     * │SHI│ a │ s │ d │ f │ g │
     * ├───┼───┼───┼───┼───┼───┤
     * │SHI│ z │ x │ c │ v │ b │
     * ├───┼───┼───┼───┼───┼───┘
     * │CTL│Win│ALT│FN2│SPA│
     * └───┴───┴───┴───┴───┘
     */
    [default] = LAYOUT_default(
        KC_ESC,         KC_1,    KC_2,          KC_3,    KC_4,    KC_5,
        KC_TAB,         KC_Q,    KC_W,          KC_E,    KC_R,    KC_T,
        KC_RIGHT_SHIFT,   KC_A,    KC_S,          KC_D,    KC_F,    KC_G,
        KC_LEFT_SHIFT,  KC_Z,    KC_X,          KC_C,    KC_V,    KC_B,
        KC_LEFT_CTRL,   KC_LWIN, KC_LEFT_ALT,   MO(1),   KC_SPACE
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │`~ │F1 │F2 │F3 │F4 │F5 │
     * ├───┼───┼───┼───┼───┼───┤
     * │TAB│F11│F12│ e │ r │ t │
     * ├───┼───┼───┼───┼───┼───┤
     * │SHI│ a │ s │ d │ f │ g │
     * ├───┼───┼───┼───┼───┼───┤
     * │SHI│ z │ x │ c │ v │ b │
     * ├───┼───┼───┼───┼───┼───┘
     * │CTL│Win│ALT│NO │SPA│
     * └───┴───┴───┴───┴───┘
     */
    [1] = LAYOUT_1(
        KC_GRV,         KC_F1,   KC_F2,         KC_F3,   KC_F4,   KC_F5,
        KC_TAB,         KC_F11,  KC_F12,        KC_E,    KC_R,    KC_T,
        KC_RIGHT_SHIFT,   KC_A,    KC_S,          KC_D,    KC_F,    KC_G,
        KC_LEFT_SHIFT,  KC_Z,    KC_X,          KC_C,    KC_V,    KC_B,
        KC_LEFT_CTRL,   KC_LWIN, KC_LEFT_ALT,   KC_NO,   KC_NUM
    )
}
