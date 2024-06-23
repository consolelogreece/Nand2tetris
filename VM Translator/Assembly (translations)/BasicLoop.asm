// Push CONSTANT 0
@0
D=A
@SP
A=M
M=D
@SP
M=M+1


// Pop LOCAL 0
@SP
M=M-1
A=M
D=M
@R13
M=D
@0
D=A
@LCL
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


// Push LOCAL 0
@LCL
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


// Pop LOCAL 0
@SP
M=M-1
A=M
D=M
@R13
M=D
@0
D=A
@LCL
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


// If-goto LOOP
@SP
M=M-1
A=M
D=M
@NULL$LOOP
D;JNE


// Push LOCAL 0
@LCL
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


