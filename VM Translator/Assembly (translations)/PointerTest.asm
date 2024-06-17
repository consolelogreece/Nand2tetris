// Push CONSTANT 3030
@3030
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop POINTER 0
@SP
M=M-1
A=M
D=M
@3
M=D

// Push CONSTANT 3040
@3040
D=A
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

// Push CONSTANT 32
@32
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop THIS 2
@SP
M=M-1
A=M
D=M
@R13
M=D
@2
D=A
@THIS
D=M+D
@R14
M=D
@R13
D=M
@R14
A=M
M=D

// Push CONSTANT 46
@46
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop THAT 6
@SP
M=M-1
A=M
D=M
@R13
M=D
@6
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

// Push POINTER 0
@3
D=M
@SP
A=M
M=D
@SP
M=M+1

// Push POINTER 1
@4
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

// Push THIS 2
@THIS
D=M
@2
D=D+A
A=D
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

// Push THAT 6
@THAT
D=M
@6
D=D+A
A=D
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

