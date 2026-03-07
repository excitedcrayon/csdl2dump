#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum KeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
char const WINDOW_TITLE[] = "Keypress SDL";

bool init(); //init SDL
bool loadMedia(); // load nedia (images)
void close(); // close application

// load individual image
SDL_Surface* loadSurface(const char *path);
// window to render to
SDL_Window* globalWindow = NULL;
// surface contained by window
SDL_Surface* globalScreenSurface = NULL;
// image corresponding to a keypress
SDL_Surface* globalKeyPressSurface[ KEY_PRESS_SURFACE_TOTAL ];
// current displayed image
SDL_Surface* globalCurrentSurface = NULL;


int main(){

    init();

    loadMedia();

    bool isRunning = true;
    SDL_Event event;

    // set default current surface
    globalCurrentSurface = globalKeyPressSurface[ KEY_PRESS_SURFACE_DEFAULT ];

    while ( isRunning ) {
        
        while ( SDL_PollEvent(&event) != 0 ) {
            if ( event.type == SDL_QUIT ){
                isRunning = false;
            }

            // handle key down events
            if ( event.type == SDL_KEYDOWN ) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        globalCurrentSurface = globalKeyPressSurface[ KEY_PRESS_SURFACE_UP ];
                        break;
                    case SDLK_DOWN:
                        globalCurrentSurface = globalKeyPressSurface[ KEY_PRESS_SURFACE_DOWN ];
                        break;
                    case SDLK_LEFT:
                        globalCurrentSurface = globalKeyPressSurface[ KEY_PRESS_SURFACE_LEFT ];
                        break;
                    case SDLK_RIGHT:
                        globalCurrentSurface = globalKeyPressSurface[ KEY_PRESS_SURFACE_RIGHT ];
                        break;
                    default:
                        globalCurrentSurface = globalKeyPressSurface[ KEY_PRESS_SURFACE_DEFAULT ];
                        break;
                }
            }
        }

        // apply current image
        SDL_BlitSurface(globalCurrentSurface, NULL, globalScreenSurface, NULL);
        // update surface
        SDL_UpdateWindowSurface(globalWindow);

        SDL_Delay(16);
    }

    close();

    return 0;
}

bool init(){

    bool loaded = true;
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        printf("Failed to load video! Error: %s\n",SDL_GetError());
        loaded = false;
    }
    
    if ( loaded ) {
        globalWindow = SDL_CreateWindow(
            WINDOW_TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        if ( !globalWindow ) {
            printf("Failed to create window! Error: %s\n: ", SDL_GetError());
            loaded = false;
        } else {
            globalScreenSurface = SDL_GetWindowSurface(globalWindow);
        }
    }

    return loaded;
}

bool loadMedia(){

    bool success = true;

    // declare images
    globalKeyPressSurface[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface("../04-keypress/images/press.bmp");
    globalKeyPressSurface[ KEY_PRESS_SURFACE_UP ] = loadSurface("../04-keypress/images/up.bmp");
    globalKeyPressSurface[ KEY_PRESS_SURFACE_DOWN ] = loadSurface("../04-keypress/images/down.bmp");
    globalKeyPressSurface[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface("../04-keypress/images/right.bmp");
    globalKeyPressSurface[ KEY_PRESS_SURFACE_LEFT ] = loadSurface("../04-keypress/images/left.bmp");

    for (enum KeyPressSurfaces k = KEY_PRESS_SURFACE_DEFAULT; k < KEY_PRESS_SURFACE_TOTAL; k++){
        if ( globalKeyPressSurface[k] == NULL ) {
            printf("Failed to loaded load image! Error: %s\n: ", SDL_GetError());
            success = false;
        }
    }

    return success;
}

SDL_Surface* loadSurface(const char *path){
    // load image at specified path
    SDL_Surface* getSurface = SDL_LoadBMP(path);
    if ( getSurface == NULL ) {
        printf("Failed to load surface! Error: %s\n", SDL_GetError());
    }
    return getSurface;
}

void close(){

    // free surfaces
    for ( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; i++ ) {
        if ( globalKeyPressSurface[i] != NULL ) {
            SDL_FreeSurface(globalKeyPressSurface[i]);
            globalKeyPressSurface[i] = NULL;
        }
    }

    SDL_DestroyWindow(globalWindow);
    SDL_Quit();
}