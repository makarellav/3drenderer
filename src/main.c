#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

bool init_window(void);
void setup(void);
void process_input(void);
void update(void);
void render(void);

SDL_Window *window;
SDL_Renderer *renderer;
bool is_running;

int main(void) {
    is_running = init_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    return 0;
}

bool init_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "error initializing SDL\n");

        return false;
    }

    window =
        SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         1280, 960, SDL_WINDOW_BORDERLESS);

    if (!window) {
        fprintf(stderr, "error creating SDL window\n");

        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (!renderer) {
        fprintf(stderr, "error creating SDL renderer\n");

        return false;
    }

    return true;
}

void setup(void) {};
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
void update(void) {};
void render(void) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
};