// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//set up the limit i.e. this is how many 'words' there are (hack computer is 512 cols by 256 rows).
@8192
D=A
@n
M=D

(reset)
@i
M=0

// get keyboard value and determine paint colour
@KBD
D=M

@white
D;JEQ

// If it's keyboard character code is not 0, means a key is pressed, so set colour to black (-1 decimal = 1111111... in twos complement), then jump to paint.
@colour
M=-1
@paint
0;JMP

(white)
@colour
M=0

(paint)
// calculate which 'word' we need to paint
@SCREEN
D=A
@i
D=D+M
@currentWordLocation
M=D

// do the paint
@colour
D=M
// Remember this is a pointer to the 'word' to paint, and setting M is essentially M[A] so need to set M to the value 
// inside currentWordLocation so that M=D is thereforesaying M[currentWordLocation value]
@currentWordLocation
A=M 
M=D

//i++
@i
D=M
M=D+1

// check if i > n, and if so, done drawing all 'words' so go back to start, otherwise continue painting.
D=M
@n
D=D-M

@reset
D;JGE

@paint
0;JMP
