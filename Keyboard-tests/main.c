#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define POINT_COUNT 100

typedef struct {
    int x;
    int y;
    int brightness;   // Brightness level from 0 to 255
    bool fading_out;  // Whether the point is currently fading out
    int delay;        // Random delay before starting fade-in
} Point;

Point points[POINT_COUNT];

// Initialize random points with positions, brightness, and random delays
void init_points() {
    for (int i = 0; i < POINT_COUNT; i++) {
        points[i].x = rand() % SCREEN_WIDTH;
        points[i].y = rand() % SCREEN_HEIGHT;
        points[i].brightness = 0;
        points[i].fading_out = false;
        points[i].delay = rand() % 100;  // Random delay before starting fade-in (0 to 99 frames)
    }
}

// Update points to simulate fade-in and fade-out effect with random delays
void update_points() {
    for (int i = 0; i < POINT_COUNT; i++) {
        if (points[i].delay > 0) {
            // Count down the delay before starting fade-in
            points[i].delay--;
            continue;
        }

        if (points[i].fading_out) {
            // Fade out by decreasing brightness
            if (points[i].brightness > 0) {
                points[i].brightness--;
            } else {
                // Reset the point when fully faded out
                points[i].fading_out = false;
                points[i].x = rand() % SCREEN_WIDTH;
                points[i].y = rand() % SCREEN_HEIGHT;
                points[i].delay = rand() % 100;  // New random delay before next fade-in
            }
        } else {
            // Fade in by increasing brightness
            if (points[i].brightness < 255) {
                points[i].brightness++;
            } else {
                // Switch to fade-out once fully bright
                points[i].fading_out = true;
            }
        }
    }
}

// Draw points onto the SDL renderer
void draw_points(SDL_Renderer *renderer) {
    for (int i = 0; i < POINT_COUNT; i++) {
        int brightness = points[i].brightness;
        SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, 255);
        SDL_RenderDrawPoint(renderer, points[i].x, points[i].y);
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("QMK OLED Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * 4, SCREEN_HEIGHT * 4, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand(time(NULL));

    init_points();

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        update_points();
        draw_points(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(10); // Control frame rate
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
