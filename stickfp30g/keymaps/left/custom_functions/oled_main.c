// OLED functions main
#ifdef OLED_ENABLE
    #include "oled_active_layer.c"
    #include "oled_suspended.c"
    #define SWITCH_INTERVAL 60000
    uint32_t oled_timer = 0;
    bool switch_to_suspend = true;

    void oled_switch_active_suspended(void) {
        // Check if the interval has passed
        if (timer_elapsed(oled_timer) > SWITCH_INTERVAL) {
            // Reset the timer and switch the display function
            oled_timer = timer_read();
            switch_to_suspend = !switch_to_suspend;  // Toggle the display mode
        }
        // Choose which display function to show
        if (switch_to_suspend) {
            suspended_display();
        } else {
            layer_active();
        }
    }
#endif
