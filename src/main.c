#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "display.h"
#include "vector.h"

#define N_POINTS (9 * 9 * 9)

void update(void);
void process_input(void);
void setup(void);
void render(void);
vec2_t project(vec3_t point);

bool is_running;

const int FOV_FACTOR = 256;

vec3_t cube_points[N_POINTS];
vec2_t projected_points[N_POINTS];

int main(void) {
    is_running = init_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    destroy_window();

    return 0;
}

void setup(void) {
    color_buffer =
        (uint32_t *)malloc(window_width * window_height * sizeof(uint32_t));

    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             window_width, window_height);

    int current_point = 0;

    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                vec3_t point = {x, y, z};
                cube_points[current_point] = point;

                current_point++;
            }
        }
    }
}
void process_input(void) {
    SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;

            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            }

            break;
    }
};

void update(void) {
    for (int i = 0; i < N_POINTS; i++) {
        projected_points[i] = project(cube_points[i]);
    }
};

void render(void) {
    clear_color_buffer(0xFF000000);
    draw_grid(0xFF484848);
    for (int i = 0; i < N_POINTS; i++) {
        vec2_t point = projected_points[i];

        draw_rect(point.x + window_width / 2, point.y + window_height / 2, 4, 4,
                  0xFFFFFF00);
    }
    render_color_buffer();

    SDL_RenderPresent(renderer);
};

vec2_t project(vec3_t point) {
    vec2_t projected_point = {(FOV_FACTOR * point.x), (FOV_FACTOR * point.y)};

    return projected_point;
}