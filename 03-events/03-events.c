/**
 * Get different types of events (keyboard, mouse etc)
 */

 #include <stdio.h>
 #include <stdbool.h>
 #include <SDL2/SDL.h>

 const int WINDOW_WIDTH = 640;
 const int WINDOW_HEIGHT = 480;
 const char WINDOW_TITLE[] = "Events SDL";

 bool isRunning = true;

 int main(){

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }


    SDL_Event event;
    while ( isRunning ) {
        while ( SDL_PollEvent(&event) != 0) {

            printf("Event: %d\n:", event.type);

            if ( event.type == SDL_QUIT ) {
                isRunning = false;
            } 
        } 

        SDL_Delay(16); // 60 fps cheap trick
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
 }