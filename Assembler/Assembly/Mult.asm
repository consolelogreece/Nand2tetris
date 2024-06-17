// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//// Replace this comment with your code.


// need to loop and just add R0 to R2, R1 times.


@i
M=0
@R2
M=0

(loop)
// If i > r1, mult completed so end.
@i
D=M
@R1
D=D-M

@endloop
D;JGE

// add r0 to r2
@R0
D=M
@R2
M=M+D

// i++
@i
M=M+1

// repeat loop
@loop
0;JMP

(endloop)
@endloop
0;JMP
