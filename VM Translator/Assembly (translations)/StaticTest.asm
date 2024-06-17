// Push CONSTANT 111
@111
D=A
@SP
A=M
M=D
@SP
M=M+1

// Push CONSTANT 333
@333
D=A
@SP
A=M
M=D
@SP
M=M+1

// Push CONSTANT 888
@888
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop STATIC 8
@SP
M=M-1
A=M
D=M
@StaticTest.8
M=D

// Pop STATIC 3
@SP
M=M-1
A=M
D=M
@StaticTest.3
M=D

// Pop STATIC 1
@SP
M=M-1
A=M
D=M
@StaticTest.1
M=D

// Push STATIC 3
@StaticTest.3
D=M
@SP
A=M
M=D
@SP
M=M+1

// Push STATIC 1
@StaticTest.1
D=M
@SP
A=M
M=D
@SP
M=M+1

// Sub
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

// Push STATIC 8
@StaticTest.8
D=M
@SP
A=M
M=D
@SP
M=M+1

// Add
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

