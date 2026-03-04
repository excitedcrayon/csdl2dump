/**
 * Render BMP images to the screen
 */

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char WINDOW_TITLE[] = "SDL Image";
const char IMAGE_PATH[] = "image.bmp";
bool isRunning = true;

/**
 * Global variables to use in functions
 */
SDL_Window *globalWindow = NULL;
SDL_Surface *globalScreenSurface = NULL;
SDL_Surface *globalImage = NULL;

bool init();
bool loadMedia();
void mainLoop();
void close();

int main(){

    init();
    loadMedia();
    mainLoop();
    close();

    return 0;
}

bool init(){
    bool success = true;

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("SDL could not initialize video! Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // create window
        globalWindow = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        if ( globalWindow == NULL ) {
            printf("SDL Window failed to render! Error: %s\n", SDL_GetError());
            success = false;
        } else {
            globalScreenSurface = SDL_GetWindowSurface(globalWindow);
        }
    }

    return success;
}

bool loadMedia(){

    bool loaded = true;

    // load image (BMP format only)
    globalImage = SDL_LoadBMP(IMAGE_PATH);
    if ( globalImage == NULL ) {
        printf("Unable to load image resource: %s\n",SDL_GetError());
        loaded = false;
    }

    return loaded;
}

void mainLoop(){
    SDL_Event event;

    // main loop
    while ( isRunning ) {
        while ( SDL_PollEvent(&event) ){
            if ( event.type == SDL_QUIT ) {
                isRunning = false;
            }
        }

        // draw image to window surface
        SDL_BlitSurface(globalImage, NULL, globalScreenSurface, NULL);
        // update window
        SDL_UpdateWindowSurface(globalWindow);
    }
}

void close(){
    //deallocate surface
    SDL_FreeSurface(globalImage);
    globalImage = NULL;

    SDL_DestroyWindow(globalWindow);
    globalWindow = NULL;

    SDL_Quit();
}