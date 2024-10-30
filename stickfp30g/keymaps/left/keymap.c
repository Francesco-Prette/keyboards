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
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │
     * ├───┼───┼───┼───┼───┼───┤
     * │ q │ w │ e │ r │ t │ g │
     * ├───┼───┼───┼───┼───┼───┤
     * │ h │ y │ u │ i │ o │ p │
     * ├───┼───┼───┼───┼───┼───┤
     * │SHI│ a │ s │ d │ f │ c │
     * ├───┼───┼───┼───┼───┼───┘
     * │CTL│Win│ALT│FN2│SPA│
     * └───┴───┴───┴───┴───┘
     */
    [2] = LAYOUT_tel(
        KC_ESC,         KC_1,   KC_2,   KC_3,    KC_4,    KC_5,
        KC_Q,           KC_W,   KC_E,   KC_R,    KC_T,    KC_G,
        KC_H,           KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,
        KC_LEFT_SHIFT,  KC_A,   KC_S,   KC_D,    KC_F,    KC_C,
        KC_LEFT_CTRL,   KC_LWIN, KC_LEFT_ALT,   TO(0),   KC_SPACE
    )
};

#ifdef OLED_ENABLE
    // RENDER QMK
    //static void render_logo(void) {
    //    static const char PROGMEM qmk_logo[] = {
    //        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    //        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    //        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    //    };
    //    oled_write_P(qmk_logo, false);
    //}

    enum layer_names {
        _L_DEFAULT,
        _L_1,
        _L_TEL
    };

    bool oled_task_user(void) {
        // RENDER QMK
        //render_logo();
        switch (get_highest_layer(layer_state)){
            case _L_DEFAULT:
                oled_write_ln("Default", false);
                break;
            case _L_1:
                oled_write_ln("Layer 1", false);
                break;
            case _L_TEL:
                oled_write_ln("Throne and Liberty", false);
                break;
        }
        return false;
    }
#endif

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
