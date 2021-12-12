//  ====================
    #include "Display.h"
//  ====================

//  ===================
    #include <iostream>
//  ===================

//  ====================
    using namespace std;
//  ====================

//  ============================
    void Display::Initialize() {

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

            cout << "SDL failed to initialize." << endl;

        }

        windowPtr = SDL_CreateWindow("Chip-8 Interpreter", 200, 200, 64 * 8, 32 * 8, SDL_WINDOW_RESIZABLE);

        renderer = SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_ACCELERATED);

    } // Function Initialize()
//  ==========================

//  ========================================
    void Display::Draw(unsigned int arr[]) {

        sdlSurface = SDL_CreateRGBSurfaceFrom(arr, 64, 32, 32, 64 * 4, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

        sdlTexture = SDL_CreateTextureFromSurface(renderer, sdlSurface);

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);

        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(sdlTexture);

    } // Function Draw()
//  =====================

//  ==========================
    void Display::Destroy() {

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(windowPtr);

        SDL_FreeSurface(sdlSurface);

    } // Function Destroy()
//  =======================
