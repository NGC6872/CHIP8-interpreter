//  ====================
    #include "Keyboard.h"
    #include "SDL.h"
    #include "../CHIP8-interpreter/CHIP8-interpreter/CPU.h"
//  ====================

//  ===================
    #include <iostream>
//  ===================

//  ====================
    using namespace std;
//  ====================

//  ==========================================================================
    void Keyboard::GetKeyPress(SDL_Event& sdlEvent, CPU& cpu, bool& running) {

        while (SDL_PollEvent(&sdlEvent) != 0) {

            if (sdlEvent.type == SDL_QUIT) {

                running = false;

            }

            else if (sdlEvent.type == SDL_KEYDOWN) {

                auto key = cpu.KeyCodeToKey((int)sdlEvent.key.keysym.sym);
                cpu.Keyboard |= (unsigned short)key;

            }

            else if (sdlEvent.type == SDL_KEYUP) {

                auto key = cpu.KeyCodeToKey((int)sdlEvent.key.keysym.sym);
                cpu.Keyboard &= (unsigned short)~key;

            }

        }

    } // Function Initialize()
//  ==========================