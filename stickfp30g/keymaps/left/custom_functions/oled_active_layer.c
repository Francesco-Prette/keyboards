// Oled active layer
enum layer_names {
    _L_DEFAULT,
    _L_1
};

void layer_active() {
    switch (get_highest_layer(layer_state)){
        case _L_DEFAULT:
            oled_write_ln("Default", false);
            break;
        case _L_1:
            oled_write_ln("Layer 1", false);
            break
    }
}
