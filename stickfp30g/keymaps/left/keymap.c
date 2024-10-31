// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "joystick.h"
#include "action.h"
#include "print.h"

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
     * │TO2│ a │ s │ d │ f │ g │
     * ├───┼───┼───┼───┼───┼───┤
     * │SHI│ z │ x │ c │ v │ b │
     * ├───┼───┼───┼───┼───┼───┘
     * │CTL│Win│ALT│NO │SPA│
     * └───┴───┴───┴───┴───┘
     */
    [1] = LAYOUT_1(
        KC_GRV,         KC_F1,   KC_F2,         KC_F3,   KC_F4,   KC_F5,
        KC_TAB,         KC_F11,  KC_F12,        KC_E,    KC_R,    KC_T,
        TO(2),   KC_A,    KC_S,          KC_D,    KC_F,    KC_G,
        KC_LEFT_SHIFT,  KC_Z,    KC_X,          KC_C,    KC_V,    KC_B,
        KC_LEFT_CTRL,   KC_LWIN, KC_LEFT_ALT,   KC_NO,   KC_NUM
    )
};

#ifdef JOYSTICK_ENABLE
    // Joystick dead zone threshold (adjust as necessary)
    #define JOYSTICK_DEADZONE 25
    joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(F5, 0, 512, 1023),
    JOYSTICK_AXIS_IN(F4, 0, 512, 1023)
    };
     // Track the state of the joystick movement
    static bool w_pressed = false;
    static bool s_pressed = false;
    static bool a_pressed = false;
    static bool d_pressed = false;
    void process_joystick_input(void) {
        // Read joystick axis values
        int16_t x_axis = joystick_read_axis(0);  // 0 for X-axis
        int16_t y_axis = joystick_read_axis(1);  // 1 for Y-axis
        // Print the joystick values
        uprintf("Joystick X: %d, Y: %d\n", x_axis, y_axis);
        // Handle Forward (W)
        if (y_axis > JOYSTICK_DEADZONE) {
            if (!w_pressed) {  // If W is not pressed, press it
                register_code(KC_DOWN);
                w_pressed = true;  // Mark W as pressed
            }
        } else {
            if (w_pressed) {  // If W is pressed, release it when moving back into deadzone
                unregister_code(KC_DOWN);
                w_pressed = false;  // Mark W as released
            }
        }
        // Handle Backward (S)
        if (y_axis < -JOYSTICK_DEADZONE) {
            if (!s_pressed) {  // If S is not pressed, press it
                register_code(KC_UP);
                s_pressed = true;  // Mark S as pressed
            }
        } else {
            if (s_pressed) {  // If S is pressed, release it when moving back into deadzone
                unregister_code(KC_UP);
                s_pressed = false;  // Mark S as released
            }
        }
        // Handle Right (D)
        if (x_axis > JOYSTICK_DEADZONE) {
            if (!d_pressed) {  // If D is not pressed, press it
                register_code(KC_LEFT);
                d_pressed = true;  // Mark D as pressed
            }
        } else {
            if (d_pressed) {  // If D is pressed, release it when moving back into deadzone
                unregister_code(KC_LEFT);
                d_pressed = false;  // Mark D as released
            }
        }
        // Handle Left (A)
        if (x_axis < -JOYSTICK_DEADZONE) {
            if (!a_pressed) {  // If A is not pressed, press it
                register_code(KC_RGHT);
                a_pressed = true;  // Mark A as pressed
            }
        } else {
            if (a_pressed) {  // If A is pressed, release it when moving back into deadzone
                unregister_code(KC_RGHT);
                a_pressed = false;  // Mark A as released
            }
        }
    }
    // In your matrix_scan_user function, you can add the joystick processing
    void matrix_scan_user(void) {
        process_joystick_input();  // Call the function to handle joystick input
    }
#endif
