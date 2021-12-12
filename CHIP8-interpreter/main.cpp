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
    #include <iostream>
    #include <string>
    #include <fstream>
    
    #include <thread>
    #include <chrono>
    #include <vector>
    #include <stdint.h>
    #include <math.h>
    
    #include "CPU.h"
    #include "Audio.h"
    #include "../Display.h"
    #include "../Keyboard.h"
//  =======================

//  ====================
    using namespace std;
//  ====================
// 
//  ==================================
    int main(int argc, char* argv[]) {
    
        //Audio audio;
    
        Display display;
        Keyboard keyboard;
        CPU cpu;
    
        display.Initialize();
    
        cpu.Reset();
    
        fstream file("Brick (Brix hack, 1990).ch8", ios::in | ios::out | ios::binary);
    
        file.seekg(0);
    
        vector<unsigned char> program;
    
        while (!file.eof()) {
    
            unsigned char x;
    
            file.read(reinterpret_cast<char*>(&x), 1);
    
            program.push_back(x);
    
        }
    
        cpu.loadRom(program);
    
        bool running = true;
    
        std::chrono::time_point<std::chrono::system_clock> start;
    
        start = std::chrono::system_clock::now();
    
        while (running) {
    
            /*if (cpu.SoundTimer > 0) { 
           
                audio.playBeep();
           
            }
    
            else audio.stopAudio();*/
    
            cpu.Step();
    
            keyboard.GetKeyPress(display.sdlEvent, cpu, running);

            if (std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count() > 16) {

                display.Draw(cpu.Display);

                start = std::chrono::system_clock::now(); // restart timer

            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
    
        }
       
        return 0;
    
    } // Function main()
//  ====================
    
    