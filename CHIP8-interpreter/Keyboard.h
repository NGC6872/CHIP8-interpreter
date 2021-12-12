//  ============
    #pragma once
//  ============

//  ================
    #include "SDL.h"
    #include "CHIP8-interpreter/CPU.h"
//  ==================================

//  ================
    class Keyboard {
    
        public:

            void GetKeyPress(SDL_Event&, CPU&, bool&);
    
    }; // CLass Keyboard()
//  ======================
    
    