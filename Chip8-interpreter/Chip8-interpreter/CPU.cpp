#include "CPU.h"
#include <iostream>
#include <stack>
#include <cstdint>
#include <fstream>
#include <stdlib.h>  
#include <conio.h>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <thread>
#include <time.h>

//  ==========
    CPU::CPU() {
    
    
    
    
    } // Constructor CPU()
//  ======================
   
//  =============
    CPU::~CPU() {
    
    
    
    
    } // Deconstructor ~CPU()
//  =========================

    std::chrono::time_point<std::chrono::system_clock> start, end;

//  ==================
    void CPU::Step() {
    
        start = std::chrono::system_clock::now();

        if (std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count() > 0) {

            if (DelayTimer > 0) DelayTimer--;
            if (SoundTimer > 0) SoundTimer--;
            start = std::chrono::system_clock::now(); // reset clock

        }

        auto Opcode = (unsigned short)((RAM[PC] << 8) | RAM[PC + 1]); // First instruction: (0x00 >> 8) | 0xe0 
                                                                      // 0x00000000 | 0xe0
        if (WaitingForKeyPress) {                                     // 00000000 | 11100000
                                                                      // 11100000
           // Registers[(Opcode & 0x0F00) >> 8] = Keyboard;             
            return;
    
        }
    
    	unsigned short nibble = (unsigned short)(Opcode & 0xF000); // First instruction: nibble = 0x0000
    
        PC += 2;
    
    	switch (nibble) {
    
        case 0x0000: {
    
            //cout << endl << "CASE: 0x0000" << endl << endl << "    ";
    
            if (Opcode == 0x00e0) {
    
                //cout << "OPCODE: 0x00e0" << endl << endl << "        Resetting Display...";
    
                for (unsigned int ii : Display) { // Fixed an error: I assumed that sizeof(Display) returned the number of elements in the array when that is not the case - I was incorrectly iterating through the array.
    
                    Display[ii] = 0;
    
                }
    
            }
    
            else if (Opcode == 0x00ee) { //return from subroutine
    
                //cout << "Popping stack" << endl;
                PC = Stack.top();
                Stack.pop();
    
            }
    
            else {
    
                std::cout << "UNSUPPORTED OPCODE IN CASE 0x0000: " << to_string(Opcode) << std::endl;
    
            }
    
        }
    
    	break;
    
        case 0x1000: {
    
            //cout << endl << "CASE: 0x1000" << endl << endl << "    ";
    
            PC = (unsigned short)(Opcode & 0x0FFF);
        }
    
        break;
    
        case 0x2000: {
    
            //cout << endl << "CASE: 0x2000" << endl << endl << "    ";
    
            Stack.push(PC);
            PC = (unsigned short)(Opcode & 0x0FFF);
    
        }
    
        break;
    
        case 0x3000: {
    
            //cout << endl << "CASE: 0x3000" << endl << endl << "    ";
    
            if (Registers[(Opcode & 0x0F00) >> 8] == (Opcode & 0x00FF)) {
    
                PC += 2;
    
            }
    
        }
    
        break;
    
        case 0x4000: {
    
            //cout << endl << "CASE: 0x4000" << endl << endl << "    ";
    
            if (Registers[(Opcode & 0x0F00) >> 8] != (Opcode & 0x00FF)) {
    
                PC += 2;
    
            }
    
        }
    
        break;
    
        case 0x5000: {
    
            //cout << endl << "CASE: 0x5000" << endl << endl << "    ";
    
            if (Registers[(Opcode & 0x0F00) >> 8] == Registers[(Opcode & 0x00F0) >> 4]) {
    
                PC += 2;
    
            }
    
        }
    
        break;
    
        case 0x6000: {
    
            //cout << endl << "CASE: 0x6000" << endl << endl << "    ";
    
            Registers[(Opcode & 0x0F00) >> 8] = (unsigned char)(Opcode & 0x00FF);
           
        }
    
        break;
    
        case 0x7000: {
    
            //cout << endl << "CASE: 0x7000" << endl << endl << "    ";
    
            Registers[(Opcode & 0x0F00) >> 8] += (unsigned char)(Opcode & 0x00FF);
    
           
        }
    
        break;
    
        case 0x8000: {
    
            //cout << endl << "CASE: 0x8000" << endl << endl << "    ";
    
            int vx = (Opcode & 0x0F00) >> 8;
            int vy = (Opcode & 0x00F0) >> 4; 
    
            switch (Opcode & 0x000F) {
    
                case 0: {
                
                    Registers[vx] = Registers[vy];
    
                }
    
                break;
    
                case 1: {
    
                    Registers[vx] = (unsigned char)(Registers[vx] | Registers[vy]);
    
                }
                break;
    
                case 2: {
    
                    Registers[vx] = (unsigned char)(Registers[vx] & Registers[vy]);
    
                }
                break;
    
                case 3: {
    
                    Registers[vx] = (unsigned char)(Registers[vx] ^ Registers[vy]);
    
                }
                break;
    
                case 4: {
    
                    Registers[15] = (unsigned char)(Registers[vx] + Registers[vy] > 255 ? 1 : 0);
                    Registers[vx] = (unsigned char)((Registers[vx] + Registers[vy]) & 0x00FF);
    
                }
                break;
    
                case 5: {
                   
                    Registers[15] = (unsigned char)(Registers[vx] > Registers[vy] ? 1 : 0);
                    Registers[vx] = (unsigned char)((Registers[vx] - Registers[vy]) & 0x00FF);
    
                }
                break;
    
                case 6: {
                    
                    Registers[15] = (unsigned char)(Registers[vx] & 0x0001);
                    Registers[vx] = (unsigned char)(Registers[vx] >> 1);
                }
                break;
    
                case 7: {
    
                    Registers[15] = (unsigned char)(Registers[vy] > Registers[vx] ? 1 : 0);
                    Registers[vx] = (unsigned char)((Registers[vy] - Registers[vx]) & 0x00FF);
    
                }
                break;
    
                case 14: {
    
                    Registers[15] = (unsigned char)(((Registers[vx] & 0x80) == 0x80) ? 1 : 0);
                    Registers[vx] = (unsigned char)(Registers[vx] << 1);
    
                }
                break;
    
                default:
                    cout << endl << "CASE: 0x8000 - Reached unsupported opcode" << endl << endl << "    ";
    
            }
    
            break;
    
        } // End case 0x8000
    
        break;
    
        case 0x9000: {
    
            //cout << endl << "CASE: 0x9000" << endl << endl << "    ";
    
            if (Registers[(Opcode & 0x0F00) >> 8] != Registers[(Opcode & 0x00F0) >> 4]) {
    
                PC += 2;
    
            }
        }
        break;
    
        case 0xA000: {
        
            //cout << endl << "CASE: 0xA000" << endl << endl << "    ";
    
            I = (unsigned short)(Opcode & 0x0FFF);
    
        }
        break;
    
        case 0xB000: {
    
            //cout << endl << "CASE: 0xB000" << endl << endl << "    ";
    
            PC = (unsigned short)((Opcode & 0x0FFF) + Registers[0]);
    
        }
        break;
    
        case 0xC000: { // ERROR HERE?
            
            //cout << endl << "CASE: 0xC000" << endl << endl << "    ";
    
            Registers[(Opcode & 0x0F00) >> 8] = (unsigned char)((rand()) & (Opcode & 0x00FF));
    
        }
        break;
    
        case 0xD000: { 
    
            //cout << endl << "CASE: 0xD000" << endl << endl << "    ";
    
            int x = Registers[(Opcode & 0x0F00) >> 8];
            int y = Registers[(Opcode & 0x00F0) >> 4];
    
            int n = Opcode & 0x000F;
    
            Registers[15] = 0;

            bool shouldSleep = false;
    
            for (int ii = 0; ii < n; ii++) {
    
                unsigned char mem = RAM[I + ii];
    
                for (int jj = 0; jj < 8; jj++) {
    
                    unsigned char pixel = (unsigned char)((mem >> (7 - jj)) & 0x01);
                    int index = x + jj + (y + ii) * 64;
    
                    if (index > 2047) continue;

                    if (pixel == 1 && Display[index] != 0) Registers[15] = 1;

                    if (Display[index] != 0 && pixel == 1) {
                    
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        COORD pos = { x + jj, y + ii};
                        SetConsoleCursorPosition(hConsole, pos);

                        cout << " ";

                        shouldSleep = true;

                    }
                    else if (Display[index] == 0 && pixel == 1) {

                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        COORD pos = { x + jj, y + ii };
                        SetConsoleCursorPosition(hConsole, pos);

                        cout << "*";

                        shouldSleep = true;

                    }

                    Display[index] = (Display[index] != 0 && pixel == 0) || (Display[index] == 0 && pixel == 1) ? 0xffffffff : 0;
                    
                }
            }

           // if (shouldSleep) std::this_thread::sleep_for(std::chrono::milliseconds(0));

        }
        break;
    
        case 0xE000: {
    
            //cout << endl << "CASE: 0xE000" << endl << endl << "    ";
    
            if ((Opcode & 0x00FF) == 0x009E) {
    
                if (((Keyboard >> Registers[(Opcode & 0x0F00) >> 8]) & 0x01) == 0x01) PC += 2;
                break;
            }
          
            else if ((Opcode & 0x00FF) == 0x00A1) {
    
                if (((Keyboard >> Registers[(Opcode & 0x0F00) >> 8]) & 0x01) != 0x01) PC += 2;
                break;
    
            }
    
            else {
    
                cout << endl << "CASE: 0xE000" << endl << endl << "    Unsupported opcode in case 0xE000";
    
            }
    
        }
        break;
    
        case 0xF000: {
    
            //cout << endl << "CASE: 0xF000" << endl << endl << "    ";
    
            int tx = (Opcode & 0x0F00) >> 8;
    
            switch (Opcode & 0x00FF) {
    
                case 0x07: {
    
                    //cout << endl << "CASE: 0x07 WITHIN CASE: 0xF000" << endl << endl << "    ";
    
                    Registers[tx] = DelayTimer;
    
                }
                break;
    
                case 0x0A: {
                    //cout << endl << "CASE: 0x0A WITHIN CASE: 0xF000" << endl << endl << "    ";
                    WaitingForKeyPress = true;
                    PC -= 2;
    
    
                }
                break;
    
                case 0x15: {
    
                    //cout << endl << "CASE: 0x15 WITHIN CASE: 0xF000" << endl << endl << "    ";
                    DelayTimer = Registers[tx];
    
                }
                break;
    
                case 0x18: {
    
                    //cout << endl << "CASE: 0x18 WITHIN CASE: 0xF000" << endl << endl << "    ";
                    SoundTimer = Registers[tx];
    
                }
                break;
    
                case 0x1E: {
    
                    //cout << endl << "CASE: 0x1E WITHIN CASE: 0xF000" << endl << endl << "    ";
                    
    
                    I = (unsigned short)(I + Registers[tx]);
    
                }
                break;
    
                case 0x29: {
    
                    //cout << endl << "CASE: 0x29 WITHIN CASE: 0xF000" << endl << endl << "    ";
    
    
                    I = (unsigned short)(Registers[tx] * 5);
    
                }
                break;
    
                case 0x33: {
    
                    //cout << endl << "CASE: 0x33 WITHIN CASE: 0xF000" << endl << endl << "    ";
    
    
                    RAM[I] = (unsigned char)(Registers[tx] / 100);
                    RAM[I + 1] = (unsigned char)((Registers[tx] % 100) / 10);
                    RAM[I + 2] = (unsigned char)(Registers[tx] % 10);
                }
                break;
    
                case 0x55: {
    
                    //cout << endl << "CASE: 0x55 WITHIN CASE: 0xF000" << endl << endl << "    ";
    
    
                    for (int ii = 0; ii <= tx; ii++) {
    
                        RAM[I + ii] = Registers[ii];
    
                    }
                }
                break;
    
                case 0x65: {
    
                    //cout << endl << "CASE: 0x65 WITHIN CASE: 0xF000" << endl << endl << "    ";
    
                    for (int ii = 0; ii <= tx; ii++) {
    
                        Registers[ii] = RAM[I + ii];
    
                    }
                    
    
                }
                break;
    
                default: {
    
                    cout << endl << "UNSUPPORTED OPCODE WITHIN CASE: 0xF000" << endl << endl << "    ";
    
                }
    
            } // End switch within case 0x7000
    
            break;
    
        } // End case 0x7000
    
        break;
    
    	} // End switch
    
    } // Function Step()
//  ====================
 
//  ============================
    void CPU::InitializeFont() {

        unsigned char characters[] = { 0xF0, 0x90, 0x90, 0x90, 0xF0, 0x20, 0x60, 0x20, 0x20, 0x70, 0xF0, 0x10, 0xF0, 0x80, 0xF0, 0xF0, 0x10, 0xF0, 0x10, 0xF0,
                                       0x90, 0x90, 0xF0, 0x10, 0x10, 0xF0, 0x80, 0xF0, 0x10, 0xF0, 0xF0, 0x80, 0xF0, 0x90, 0xF0, 0xF0, 0x10, 0x20, 0x40, 0x40,
                                       0xF0, 0x90, 0xF0, 0x90, 0xF0, 0xF0, 0x90, 0xF0, 0x10, 0xF0, 0xF0, 0x90, 0xF0, 0x90, 0x90, 0xE0, 0x90, 0xE0, 0x90, 0xE0,
                                       0xF0, 0x80, 0x80, 0x80, 0xF0, 0xE0, 0x90, 0x90, 0x90, 0xE0, 0xF0, 0x80, 0xF0, 0x80, 0xF0, 0xF0, 0x80, 0xF0, 0x80, 0x80 };

        // copy Font into RAM starting at 0x00

        for (int ii = 0; ii < sizeof(characters); ii++) {

            RAM[ii] = characters[ii];

        }

    } // Function InitializeFont()
//  ==============================

//  ==================================================
    bool CPU::loadRom(vector<unsigned char> program) {
    
        memset(RAM, 0, sizeof(RAM));
        memset(Display, 0, sizeof(Display));

        InitializeFont();

        for (int ii = 0; ii < program.size(); ii++) {
            
            RAM[512 + ii] = program[ii];
    
        }
    
        PC = 512;
    
      return true;

    } // Function loadRom()
//  =======================

//  ===================
    void CPU::Reset() {

        PC = 0;    // The first 512(0x200) bytes of memory are reserved
        
        I = 0;        // Reset index register
        
        // Reset the timers
        DelayTimer = 0;
        SoundTimer = 0;

        // reset RAM
        
        memset(RAM, 0, sizeof(RAM));
    
    } // Function Reset()
//  =====================

//  =========================
    void CPU::DrawDisplay() {
    
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos = { 0, 0 };
        SetConsoleCursorPosition(hConsole, pos);

        for (int y = 0; y < 32; y++) {
    
            string line = ""; 

            for (int x = 0; x < 64; x++) {
    
                if (Display[x + y * 64] != 0) {

                    line += "*";
                }

                else {
                    line += " ";
                }
                
            }
    
            cout << line << endl;
    
        }

        //std::this_thread::sleep_for(std::chrono::milliseconds(5));
     
    } // Function DrawDisplay()
//  ===========================

    int CPU::KeyCodeToKey(int keycode) {

        int keyIndex = 0;

        if (keycode < 58) {

            keyIndex = keycode - 48;

        }

        else {

            keyIndex = keycode - 87;

        }

        return (1 << keyIndex);

    }
