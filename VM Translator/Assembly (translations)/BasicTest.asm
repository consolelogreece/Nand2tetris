// Push CONSTANT 10
@10
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

// Push CONSTANT 21
@21
D=A
@SP
A=M
M=D
@SP
M=M+1

// Push CONSTANT 22
@22
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop ARGUMENT 2
@SP
M=M-1
A=M
D=M
@R13
M=D
@2
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

// Pop ARGUMENT 1
@SP
M=M-1
A=M
D=M
@R13
M=D
@1
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

// Push CONSTANT 36
@36
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop THIS 6
@SP
M=M-1
A=M
D=M
@R13
M=D
@6
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

// Push CONSTANT 42
@42
D=A
@SP
A=M
M=D
@SP
M=M+1

// Push CONSTANT 45
@45
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop THAT 5
@SP
M=M-1
A=M
D=M
@R13
M=D
@5
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

// Push CONSTANT 510
@510
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop TEMP 6
@SP
M=M-1
A=M
D=M
@11
M=D

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

// Push THAT 5
@THAT
D=M
@5
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

// Push THIS 6
@THIS
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

// Push THIS 6
@THIS
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

// Push TEMP 6
@11
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

