// Push ARGUMENT 1
@ARG
D=M
@1
D=D+A
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// Pop POINTER 1
@SP
M=M-1
A=M
D=M
@4
M=D

// Push CONSTANT 0
@0
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop THAT 0
@SP
M=M-1
A=M
D=M
@R13
M=D
@0
D=A
@THAT
D=M+D
@R14
M=D
@R13
D=M
@R14
A=M
M=D

// Push CONSTANT 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop THAT 1
@SP
M=M-1
A=M
D=M
@R13
M=D
@1
D=A
@THAT
D=M+D
@R14
M=D
@R13
D=M
@R14
A=M
M=D

// Push ARGUMENT 0
@ARG
D=M
@0
D=D+A
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// Push CONSTANT 2
@2
D=A
@SP
A=M
M=D
@SP
M=M+1

// SUB
@SP
M=M-1
A=M
D=M
@R13
M=D
@SP
M=M-1
A=M
D=M
@R13
D=D-M
@SP
A=M
M=D
@SP
M=M+1

// Pop ARGUMENT 0
@SP
M=M-1
A=M
D=M
@R13
M=D
@0
D=A
@ARG
D=M+D
@R14
M=D
@R13
D=M
@R14
A=M
M=D

// Label LOOP
(NULL$LOOP)

// Push ARGUMENT 0
@ARG
D=M
@0
D=D+A
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// If-goto COMPUTE_ELEMENT
@SP
M=M-1
A=M
D=M
@NULL$COMPUTE_ELEMENT
D;JNE

// Goto END
@NULL$END
0;JMP

// Label COMPUTE_ELEMENT
(NULL$COMPUTE_ELEMENT)

// Push THAT 0
@THAT
D=M
@0
D=D+A
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// Push THAT 1
@THAT
D=M
@1
D=D+A
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// ADD
@SP
M=M-1
A=M
D=M
@R13
M=D
@SP
M=M-1
A=M
D=M
@R13
D=M+D
@SP
A=M
M=D
@SP
M=M+1

// Pop THAT 2
@SP
M=M-1
A=M
D=M
@R13
M=D
@2
D=A
@THAT
D=M+D
@R14
M=D
@R13
D=M
@R14
A=M
M=D

// Push POINTER 1
@4
D=M
@SP
A=M
M=D
@SP
M=M+1

// Push CONSTANT 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1

// ADD
@SP
M=M-1
A=M
D=M
@R13
M=D
@SP
M=M-1
A=M
D=M
@R13
D=M+D
@SP
A=M
M=D
@SP
M=M+1

// Pop POINTER 1
@SP
M=M-1
A=M
D=M
@4
M=D

// Push ARGUMENT 0
@ARG
D=M
@0
D=D+A
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// Push CONSTANT 1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1

// SUB
@SP
M=M-1
A=M
D=M
@R13
M=D
@SP
M=M-1
A=M
D=M
@R13
D=D-M
@SP
A=M
M=D
@SP
M=M+1

// Pop ARGUMENT 0
@SP
M=M-1
A=M
D=M
@R13
M=D
@0
D=A
@ARG
D=M+D
@R14
M=D
@R13
D=M
@R14
A=M
M=D

// Goto LOOP
@NULL$LOOP
0;JMP

// Label END
(NULL$END)