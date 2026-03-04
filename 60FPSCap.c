#include <SDL2/SDL.h>
#include <stdbool.h>

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

Uint32 frameStart;
int frameTime;

int main(){

    bool running = true;

    while (running) {
        frameStart = SDL_GetTicks();
        /**
         * - Handle Events
         * - Update
         * - Render
         */

        frameTime = SDL_GetTicks() - frameStart;

        if ( FRAME_DELAY > frameTime ) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 0;
}