// ===========================
// Date:              11/22/21
//
// Purpose: The purpose of this program is to emulate a CHIP-8 virtual machine.
//          It will feature Keyboard input, audio, and a monitor.
//
// Algorithm:
// 
// 
// 
// 
// 
// About: 
//        CHIP-8 is an an interpreted programming language that was developed by Joseph Weisbecker
//        in the 1970's. It was most commonly used on the COSMAC VIP and Telmac 1800 8-bit microcomputers. CHIP-8
//        was created to allow video games to be more easily programmed for these computers.
// 
// Architecture:
//              Registers:
//                        CHIP-8 has 16 8-bit data registers named from V0 to VF. 
// 
//                        VF:
//                           The VF register doubles as a flag
//                           for some instructions. In the addition operation, VF is for the carry flag. While in the subtraction
//                           operation, it is the "no-borrow" flag.
// 
//                        I: The address register. It is 16 bits wide and used with opcodes that involve memory operations.
//                 
//               NNN: Address
//                
//               NN:  8-bit constant
// 
//               N:   4-bit constant
// 
//               X and Y: 4-bit register identifier
// 
//               PC: Program counter
//  
//               The stack: 
//                         Used to store return addresses when subroutines are called.
// 
//               Timers:
//                      CHIP-8 has two timers that both count down at 60 hertz until they reach 0.
// 
//                      Delay Timer:
//                                  Used for timing the events of games. Its value can be set and read.
//                      
//                      Sound Timer: 
//                                  Used for sound effects. When its value is nonzero, a beeping sound is made.
// 
//               Input: 
//                      Input is done with a hex keyboard that has 16 keys which range from 0 to F. The '2', '4', '6', and '8' keys
//                      are typically used for directional input. Three opcodes are used to detect input. One skips an instruction
//                      if a specific key is pressed, while another does the same if a specific key is NOT pressed.The third opcode
//                      waits for a key press, and then stores it in one of the data registers.
// 
//               Graphics and sound:
// 
//               Opcode table: 
//                            CHIP-8 has 35 opcodes. All of them are two bytes long and stored big-endian. A table of all
//                            of the opcodes can be found at the following URL: https://en.wikipedia.org/wiki/CHIP-8 
// 
// Sources: https://en.wikipedia.org/wiki/CHIP-8 
// =============================================

//  ===================
#include "SDL.h"
#include <iostream>
#include <string>
#include <fstream>

#include <thread>
#include <chrono>
#include <vector>
#include <stdint.h>
#include "CPU.h"

//  ===================

using namespace std;

//  ==================================
int main(int argc, char* argv[]) {

   
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

        cout << "SDL failed to initialize." << endl; return 0;

    }

    SDL_Window* windowPtr = SDL_CreateWindow("Chip-8 Interpreter", 200, 200, 64 * 8, 32 * 8, SDL_WINDOW_RESIZABLE);

    SDL_Renderer* renderer = SDL_CreateRenderer(windowPtr, -1, SDL_RENDERER_ACCELERATED);

    CPU cpu;
    cpu.Reset();

    fstream file("heart_monitor.ch8", ios::in | ios::out | ios::binary);

    file.seekg(0);

    vector<unsigned char> program;

    while (!file.eof()) {

        unsigned char x;

        file.read(reinterpret_cast<char*>(&x), 1);

        program.push_back(x);

    }

    cpu.loadRom(program);

    SDL_Event sdlEvent;
    bool running = true;

    SDL_Surface* sdlSurface;
    SDL_Texture* sdlTexture;

    while (running) {

        cpu.Step();

        while (SDL_PollEvent(&sdlEvent) != 0) {

            if (sdlEvent.type == SDL_QUIT) {

                running = false;

            }

        }

        sdlSurface = SDL_CreateRGBSurfaceFrom(&cpu.Display, 64, 32, 32, 64 * 4, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

        sdlTexture = SDL_CreateTextureFromSurface(renderer, sdlSurface);

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, sdlTexture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    return 0;

} // Function main()
//  ====================