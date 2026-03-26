#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;
const char TITLE[] = "Viewport SDL";
bool isRunning = true;

int main(){

    // initialize video
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        printf("Error in SDL video init! Error: %s\n", SDL_GetError());
    }

    SDL_Window *window = SDL_CreateWindow(
        TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if ( window == NULL ) {
        printf("Error creating SDL window! Error: %s\n", SDL_GetError());
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    SDL_Event event;

    while ( isRunning ) {
        while ( SDL_PollEvent(&event) != 0) {
            if ( event.type == SDL_QUIT ) {
                isRunning = false;
            }
        }
    }


    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}