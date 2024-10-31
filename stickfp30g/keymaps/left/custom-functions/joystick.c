// Joystick functions
#ifdef JOYSTICK_ENABLE
    // Joystick dead zone threshold (adjust as necessary)
    #define JOYSTICK_DEADZONE 25
    joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_IN(F5, 0, 512, 1023),
    JOYSTICK_AXIS_IN(F4, 0, 512, 1023)
    };
     // Track the state of the joystick movement
    static bool down_pressed = false;
    static bool up_pressed = false;
    static bool right_pressed = false;
    static bool left_pressed = false;
    void process_joystick_input(void) {
        // Read joystick axis values
        int16_t x_axis = joystick_read_axis(0);  // 0 for X-axis
        int16_t y_axis = joystick_read_axis(1);  // 1 for Y-axis
        // Print the joystick values
        uprintf("Joystick X: %d, Y: %d\n", x_axis, y_axis);
        // Handle Forward (UP)
        if (y_axis > JOYSTICK_DEADZONE) {
            if (!down_pressed) {  // If DOWN is not pressed, press it
                register_code(KC_DOWN);
                down_pressed = true;  // Mark DOWN as pressed
            }
        } else {
            if (down_pressed) {  // If DOWN is pressed, release it when moving back into deadzone
                unregister_code(KC_DOWN);
                down_pressed = false;  // Mark DOWN as released
            }
        }
        // Handle Backward (S)
        if (y_axis < -JOYSTICK_DEADZONE) {
            if (!up_pressed) {  // If UP is not pressed, press it
                register_code(KC_UP);
                up_pressed = true;  // Mark UP as pressed
            }
        } else {
            if (up_pressed) {  // If UP is pressed, release it when moving back into deadzone
                unregister_code(KC_UP);
                up_pressed = false;  // Mark UP as released
            }
        }
        // Handle Right (D)
        if (x_axis > JOYSTICK_DEADZONE) {
            if (!left_pressed) {  // If LEFT is not pressed, press it
                register_code(KC_LEFT);
                left_pressed = true;  // Mark LEFT as pressed
            }
        } else {
            if (left_pressed) {  // If LEFT is pressed, release it when moving back into deadzone
                unregister_code(KC_LEFT);
                left_pressed = false;  // Mark LEFT as released
            }
        }
        // Handle Left (A)
        if (x_axis < -JOYSTICK_DEADZONE) {
            if (!right_pressed) {  // If RIGHT is not pressed, press it
                register_code(KC_RGHT);
                right_pressed = true;  // Mark RIGHT as pressed
            }
        } else {
            if (right_pressed) {  // If RIGHT is pressed, release it when moving back into deadzone
                unregister_code(KC_RGHT);
                right_pressed = false;  // Mark RIGHT as released
            }
        }
    }
    // In your matrix_scan_user function, you can add the joystick processing
    void matrix_scan_user(void) {
        process_joystick_input();  // Call the function to handle joystick input
    }
#endif
