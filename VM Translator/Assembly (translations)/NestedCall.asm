// Init
@256
D=A
@SP
M=D

// Call SYS.INIT 0
@SYS.INIT$ret.0
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@5
D=A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
@SYS.INIT
0;JMP
(SYS.INIT$ret.0)


// Function SYS.INIT 0
(SYS.INIT)
@0
D=A

// Push CONSTANT 4000
@4000
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

// Push CONSTANT 5000
@5000
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

// Call SYS.MAIN 0
@SYS.MAIN$ret.1
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@5
D=A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
@SYS.MAIN
0;JMP
(SYS.MAIN$ret.1)

// Pop TEMP 1
@SP
M=M-1
A=M
D=M
@6
M=D

// Label LOOP
(SYS.INIT$LOOP)

// Goto LOOP
@SYS.INIT$LOOP
0;JMP

// Function SYS.MAIN 5
(SYS.MAIN)
@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M
M=D
@SP
M=M+1

// Push CONSTANT 4001
@4001
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

// Push CONSTANT 5001
@5001
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

// Push CONSTANT 200
@200
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop LOCAL 1
@SP
M=M-1
A=M
D=M
@R13
M=D
@1
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

// Push CONSTANT 40
@40
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop LOCAL 2
@SP
M=M-1
A=M
D=M
@R13
M=D
@2
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

// Push CONSTANT 6
@6
D=A
@SP
A=M
M=D
@SP
M=M+1

// Pop LOCAL 3
@SP
M=M-1
A=M
D=M
@R13
M=D
@3
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

// Push CONSTANT 123
@123
D=A
@SP
A=M
M=D
@SP
M=M+1

// Call SYS.ADD12 1
@SYS.ADD12$ret.2
D=A
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@SP
A=M
M=D
@SP
M=M+1
@ARG
D=M
@SP
A=M
M=D
@SP
M=M+1
@THIS
D=M
@SP
A=M
M=D
@SP
M=M+1
@THAT
D=M
@SP
A=M
M=D
@SP
M=M+1
@6
D=A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
@SYS.ADD12
0;JMP
(SYS.ADD12$ret.2)

// Pop TEMP 0
@SP
M=M-1
A=M
D=M
@5
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

// Push LOCAL 1
@LCL
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

// Push LOCAL 2
@LCL
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

// Push LOCAL 3
@LCL
D=M
@3
D=D+A
A=D
D=M
@SP
A=M
M=D
@SP
M=M+1

// Push LOCAL 4
@LCL
D=M
@4
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

// Return
@LCL
D=M
@endFrame
M=D
@5
D=A
@endFrame
A=M-D
D=M
@retAddr
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M
@SP
M=D+1
@endFrame
A=M-1
D=M
@THAT
M=D
@2
D=A
@endFrame
A=M-D
D=M
@THIS
M=D
@3
D=A
@endFrame
A=M-D
D=M
@ARG
M=D
@4
D=A
@endFrame
A=M-D
D=M
@LCL
M=D
@retAddr
A=M
0;JMP

// Function SYS.ADD12 0
(SYS.ADD12)
@0
D=A

// Push CONSTANT 4002
@4002
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

// Push CONSTANT 5002
@5002
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

// Push CONSTANT 12
@12
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

// Return
@LCL
D=M
@endFrame
M=D
@5
D=A
@endFrame
A=M-D
D=M
@retAddr
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M
@SP
M=D+1
@endFrame
A=M-1
D=M
@THAT
M=D
@2
D=A
@endFrame
A=M-D
D=M
@THIS
M=D
@3
D=A
@endFrame
A=M-D
D=M
@ARG
M=D
@4
D=A
@endFrame
A=M-D
D=M
@LCL
M=D
@retAddr
A=M
0;JMP