#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * prototype functions
 */
void init();
bool loadedMedia();
void updateAndClear();
void close();
void renderError(const char *path);
void renderIMGError(const char *path);
SDL_Texture* loadTexture(const char *path);
SDL_Window* globalWindow = NULL;
SDL_Renderer* globalRenderer = NULL;
SDL_Texture* currentTexture = NULL;

const int WIDTH = 640;
const int HEIGHT = 480;
const char TITLE[] = "Textures SDL";
const char IMG_PATH[] = "../07-textures/texture.png";

int main(){

    bool running = true;
    SDL_Event event;

    init();
    loadedMedia();

    while ( running ) {
        while ( SDL_PollEvent(&event) != 0) {
            if ( event.type == SDL_QUIT ) {
                running = false;
            }
        }

        updateAndClear();

        SDL_Delay(16);
    }

    close();

    return 0;
}

void init(){

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        renderError("SDL video could not be initiated! ");
    }

    globalWindow = SDL_CreateWindow(
        TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if ( globalWindow == NULL ) {
        renderError("SDL window could not be initiated! ");
    }

    globalRenderer = SDL_CreateRenderer(
        globalWindow,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if ( globalRenderer == NULL ) {
        renderError("SDL global renderer could not be initiated! ");
    } else {
        SDL_SetRenderDrawColor(globalRenderer, 0xFF,0xFF,0xFF,0xFF);

        // init PNG loading
        if ( !( IMG_Init(IMG_INIT_PNG) ) ) {
            renderIMGError("SDL PNG image could not be initiated! ");
        }

    }

}

bool loadedMedia(){

    bool loaded = true;

    currentTexture = loadTexture(IMG_PATH);
    if ( currentTexture == NULL ) {
        renderError("Failed to load texture image! ");
        loaded = false;
    }

    return loaded;
}

void updateAndClear(){
    SDL_RenderClear(globalRenderer);
    SDL_RenderCopy(globalRenderer, currentTexture, NULL, NULL);
    SDL_RenderPresent(globalRenderer);
}

void close(){
    SDL_DestroyTexture(currentTexture);
    SDL_DestroyRenderer(globalRenderer);
    SDL_DestroyWindow(globalWindow);
    currentTexture = NULL;
    globalRenderer = NULL;
    globalWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(const char *path){
    SDL_Texture* newTexture = NULL;

    // load image from specific path
    SDL_Surface* loadedSurface = IMG_Load(path);
    if ( loadedSurface == NULL ) {
        renderIMGError("Failed to load surface! ");
    } else {
        newTexture = SDL_CreateTextureFromSurface(globalRenderer, loadedSurface);
        if ( newTexture == NULL ) {
            renderError("Failed to create texture from image! ");
        }
        // remove old surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void renderError(const char *path){
    printf("%s%s\n", path, SDL_GetError());
}
void renderIMGError(const char *path){
    printf("%s%s\n", path, IMG_GetError());
}