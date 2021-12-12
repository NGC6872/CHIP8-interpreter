//  ============
    #pragma once
//  ============

//  ================
    #include "SDL.h"
//  ================

//  ===============
    class Display {
    
        public:

            void Initialize();
            void Draw(unsigned int[]);
            void Destroy();
    
            SDL_Window* windowPtr;
            SDL_Renderer* renderer;
            SDL_Event sdlEvent;

            SDL_Surface* sdlSurface;
            SDL_Texture* sdlTexture;

    
    
    }; // Class Display()
//  =====================
    
    