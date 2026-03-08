#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int WIDTH = 640;
const int HEIGHT = 480;
const char TITLE[] = "Geometry Rendering SDL";

int main(){

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("Failed to initialize SDL video! Error: %s\n", SDL_GetError());
    }

    // window
    SDL_Window *window = SDL_CreateWindow(
        TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if ( window == NULL ) {
        printf("Failed to create SDL window! Error: %s\n", SDL_GetError());
    }

    // renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if ( renderer == NULL ) {
        printf("Renderer could not be initialized! Error: %s\n", SDL_GetError());
    }

    // loop
    bool running = true;
    SDL_Event event;

    while ( running ) {
        while ( SDL_PollEvent(&event) != 0 ){
            if ( event.type == SDL_QUIT ) {
                running = false;
            }
        }

        // clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(renderer);

        // draw red rectangle
        SDL_Rect fillRect = { WIDTH / 4, HEIGHT / 4, WIDTH / 2, HEIGHT / 2 };
        SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );        
        SDL_RenderFillRect( renderer, &fillRect );

        SDL_RenderPresent(renderer);

        // 60 fps cap
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}