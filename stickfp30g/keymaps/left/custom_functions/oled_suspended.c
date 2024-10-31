// Oled suspended layer
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define POINT_COUNT 20
#define MAX_BRIGHTNESS 255

// Constants to control fade-in and fade-out speed
#define FADE_IN_SPEED 5     // Brightness increase per update for fade-in
#define FADE_OUT_SPEED 3    // Brightness decrease per update for fade-out

typedef struct {
    int x;
    int y;
    int brightness;
    bool fading_out;
    int delay;
} Point;

static Point points[POINT_COUNT];

void init_points() {
    for (int i = 0; i < POINT_COUNT; i++) {
        points[i].x = rand() % SCREEN_WIDTH;
        points[i].y = rand() % SCREEN_HEIGHT;
        points[i].brightness = 0;
        points[i].fading_out = false;
        points[i].delay = rand() % 100;
    }
}

void update_points() {
    for (int i = 0; i < POINT_COUNT; i++) {
        if (points[i].delay > 0) {
            points[i].delay--;
            continue;
        }

        if (points[i].fading_out) {
            // Fade out the point
            if (points[i].brightness > 0) {
                points[i].brightness -= FADE_OUT_SPEED;
                if (points[i].brightness < 0) points[i].brightness = 0; // Prevent underflow
            } else {
                // Reset the point after fully fading out
                points[i].fading_out = false;
                points[i].x = rand() % SCREEN_WIDTH;
                points[i].y = rand() % SCREEN_HEIGHT;
                points[i].delay = rand() % 100;
            }
        } else {
            // Fade in the point
            if (points[i].brightness < MAX_BRIGHTNESS) {
                points[i].brightness += FADE_IN_SPEED;
                if (points[i].brightness > MAX_BRIGHTNESS) points[i].brightness = MAX_BRIGHTNESS; // Cap at max brightness
            } else {
                // Start fading out once max brightness is reached
                points[i].fading_out = true;
            }
        }
    }
}

void draw_random_points() {
    update_points();  // Update points' brightness and position

    for (int i = 0; i < POINT_COUNT; i++) {
        int brightness = points[i].brightness;

        // Set brightness and draw the point on the OLED
        oled_write_pixel(points[i].x, points[i].y, brightness);
    }

    oled_update();  // Refresh the OLED display
}
