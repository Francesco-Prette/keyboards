// Joystick functions
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
