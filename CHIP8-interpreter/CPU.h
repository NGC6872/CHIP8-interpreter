//  ============  
    #pragma once
//  ============

//  ===================
    
    #include <iostream>
    #include <stack>
    #include <vector>
//  =================

//  ====================
    using namespace std;
//  ====================

//      ===========
        class CPU {
        
            public:
        
                CPU();
                ~CPU();
    
        	    unsigned char RAM[4096];
        	    unsigned char Registers[16];
                
                stack<unsigned short> Stack;
    
                unsigned short I = 0;
                unsigned short PC = 0;
                
        	    unsigned char DelayTimer;
        	    unsigned char SoundTimer;
        	    unsigned short Keyboard;
                unsigned int Display[64 * 32];
        
                void Step();
                void InitializeFont();
                void Reset();
                void DrawDisplay();
                int  KeyCodeToKey(int keycode);
                
                bool loadRom(vector<unsigned char>);
                
                bool WaitingForKeyPress = false;
                
        
        }; // Class CPU()
//      =================
