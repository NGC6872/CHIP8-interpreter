# About
Just thought I'd make another CHIP-8 interpreter in c++


# Some CHIP-8 history: 
Initially used on the COSMAC VIP and Telmac 1800 microcomputers in the mid-1970s, CHIP-8 is an
interpreted programming language developed by Joseph Weisbecker. It was made to allow video games to
be more easily programmed for both microcomputers. In the early 1990s, the HP48 graphing calculator used
a CHIP-8 interpreter called CHIP-48 which allowed the calculator to easily create fast games.

# CHIP-8 Architecture: 

                    Memory:    4096 bytes (the first 512 bytes are reserved for the interpreter iteself, so most CHIP-8 programs start at memory location 512.)
                                           
                    Registers: CHIP-8 has 16 8-bit data registers names V0 to VF.

                    The stack: Only used to store return addresses when subroutines are called.

                    Timers:    Delay timer - Used for timing the events of games.
                               Sound timer - Used for sound effects.

                    Input:     A hex keyboard that has 16 keys ranging from 0 to F.

                    Graphics:  64 x 32 display resolution, and the color is monochrome.

                    Opcodes:   CHIP-8 has 35 opcodes, all of which are two bytes long and stored big-endian. 

# Setup (visual studio 2021):
git clone https://github.com/NGC6872/CHIP8-interpreter.git

File -> New -> Project from existing code -> select previously cloned repo

Install SDL2 - Here's a quick video on how to do that: https://www.youtube.com/watch?v=PrDdfALWH_4

# Resources: 
http://devernay.free.fr/hacks/chip8/C8TECH10.HTM

https://en.wikipedia.org/wiki/CHIP-8
