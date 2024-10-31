// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "joystick.h"
#include "action.h"
#include "mousekey.h"
#include "print.h"

#define default 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │ 6 │ 7 │ 8 │ 9 │ 0 │BCK│
     * ├───┼───┼───┼───┼───┼───┤
     * │ y │ u │ i │ o │ p │ \ │
     * ├───┼───┼───┼───┼───┼───┤
     * │ h │ j │ k │ l │ ; │ENT│
     * ├───┼───┼───┼───┼───┼───┤
     * │ n │ m │ , │ . │ / │HOM│
     * └───┼───┼───┼───┼───┼───┤
     *     │LFT│RGT│FN3│ - │END│
     *     └───┴───┴───┴───┴───┘
     */
    [default] = LAYOUT_default(
        KC_6,         KC_7,    KC_8,                 KC_9,    KC_0,    KC_BSPC,
        KC_Y,         KC_U,    KC_I,                 KC_O,    KC_P,    KC_BSLS,
        KC_H,         KC_J,    KC_K,                 KC_L,    KC_SCLN, KC_ENT,
        KC_N,         KC_M,    KC_COMM,              KC_DOT,  KC_SLSH, KC_RSFT,
        QK_MOUSE_BUTTON_1,     QK_MOUSE_BUTTON_2,     MO(1),   KC_MINS,  KC_END
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┐
     * │F6 │F7 │F8 │F9 │F10│DEL│
     * ├───┼───┼───┼───┼───┼───┤
     * │ y │ u │ i │ o │ p │ \ │
     * ├───┼───┼───┼───┼───┼───┤
     * │ h │ j │ k │ l │ ' │ENT│
     * ├───┼───┼───┼───┼───┼───┤
     * │ n │ m │ , │ . │ / │HOM│
     * └───┼───┼───┼───┼───┼───┤
     *     │LFT│RGT│NO │ = │END│
     *     └───┴───┴───┴───┴───┘
     */
    [1] = LAYOUT_1(
        KC_F6,        KC_F7,   KC_F8,                KC_F9,    KC_F10,    KC_DEL,
        KC_Y,         KC_U,    KC_I,                 KC_LBRC,  KC_RBRC,   KC_BSLS,
        KC_H,         KC_J,    KC_K,                 KC_L,     KC_QUOT,   KC_ENT,
        KC_N,         KC_M,    KC_COMM,              KC_DOT,   KC_SLSH,   KC_HOME,
        QK_MOUSE_BUTTON_1,     QK_MOUSE_BUTTON_2,    KC_NO,   KC_NO,    KC_END
    )
};

#ifdef OLED_ENABLE
// Render QMK logo
//    static void render_logo(void) {
//        static const char PROGMEM qmk_logo[] = {
//            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
//            0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
//            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
//        }; 
//        oled_write_P(qmk_logo, false);
//    }

    bool oled_task_user(void) {
        render_logo();
        return false;
    }
#endif

#ifdef JOYSTICK_ENABLE

    // Joystick dead zone threshold (adjust as necessary)
    #define JOYSTICK_DEADZONE 5

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
        //uprintf("Joystick X: %d, Y: %d\n", x_axis, y_axis);

        // Handle Forward (W)
        if (y_axis > JOYSTICK_DEADZONE) {
            if (!w_pressed) {  // If W is not pressed, press it
                register_code(KC_UP);
                w_pressed = true;  // Mark W as pressed
            }
        } else {
            if (w_pressed) {  // If W is pressed, release it when moving back into deadzone
                unregister_code(KC_UP);
                w_pressed = false;  // Mark W as released
            }
        }

        // Handle Backward (S)
        if (y_axis < -JOYSTICK_DEADZONE) {
            if (!s_pressed) {  // If S is not pressed, press it
                register_code(KC_DOWN);
                s_pressed = true;  // Mark S as pressed
            }
        } else {
            if (s_pressed) {  // If S is pressed, release it when moving back into deadzone
                unregister_code(KC_DOWN);
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
                register_code(KC_RIGHT);
                a_pressed = true;  // Mark A as pressed
            }
        } else {
            if (a_pressed) {  // If A is pressed, release it when moving back into deadzone
                unregister_code(KC_RIGHT);
                a_pressed = false;  // Mark A as released
            }
        }
    }

    // In your matrix_scan_user function, you can add the joystick processing
    void matrix_scan_user(void) {
        process_joystick_input();  // Call the function to handle joystick input
    }
#endif
