/**
 * Create a simple window
 */
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char TITLE[] = "Hello SDL";
bool isRunning = false;

int main(){

    // check if SDL video is initialized
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf("SDL could not initialize! Error: %s\n", SDL_GetError());
        //SDL_Quit();
        return -1;
    }

    // create window
    SDL_Window *window = SDL_CreateWindow(
        TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if ( !window ) {
        printf("Could not create SDL Window! Error: %s\n", SDL_GetError());
    }

    SDL_Event event;

    // loop
    while ( !isRunning ) {

        while ( SDL_PollEvent(&event) ) {
            if (event.type == SDL_QUIT) {
                isRunning = true;
            }
        }

    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}