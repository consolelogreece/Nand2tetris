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

// Function CLASS1.SET 0
(CLASS1.SET)
@0
D=A

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

// Pop STATIC 0
@SP
M=M-1
A=M
D=M
@Class1.vm.0
M=D

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

// Pop STATIC 1
@SP
M=M-1
A=M
D=M
@Class1.vm.1
M=D

// Push CONSTANT 0
@0
D=A
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

// Function CLASS1.GET 0
(CLASS1.GET)
@0
D=A

// Push STATIC 0
@Class1.vm.0
D=M
@SP
A=M
M=D
@SP
M=M+1

// Push STATIC 1
@Class1.vm.1
D=M
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

// Function CLASS2.SET 0
(CLASS2.SET)
@0
D=A

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

// Pop STATIC 0
@SP
M=M-1
A=M
D=M
@Class2.vm.0
M=D

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

// Pop STATIC 1
@SP
M=M-1
A=M
D=M
@Class2.vm.1
M=D

// Push CONSTANT 0
@0
D=A
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

// Function CLASS2.GET 0
(CLASS2.GET)
@0
D=A

// Push STATIC 0
@Class2.vm.0
D=M
@SP
A=M
M=D
@SP
M=M+1

// Push STATIC 1
@Class2.vm.1
D=M
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

// Function SYS.INIT 0
(SYS.INIT)
@0
D=A

// Push CONSTANT 6
@6
D=A
@SP
A=M
M=D
@SP
M=M+1

// Push CONSTANT 8
@8
D=A
@SP
A=M
M=D
@SP
M=M+1

// Call CLASS1.SET 2
@CLASS1.SET$ret.1
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
@7
D=A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
@CLASS1.SET
0;JMP
(CLASS1.SET$ret.1)

// Pop TEMP 0
@SP
M=M-1
A=M
D=M
@5
M=D

// Push CONSTANT 23
@23
D=A
@SP
A=M
M=D
@SP
M=M+1

// Push CONSTANT 15
@15
D=A
@SP
A=M
M=D
@SP
M=M+1

// Call CLASS2.SET 2
@CLASS2.SET$ret.2
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
@7
D=A
@SP
D=M-D
@ARG
M=D
@SP
D=M
@LCL
M=D
@CLASS2.SET
0;JMP
(CLASS2.SET$ret.2)

// Pop TEMP 0
@SP
M=M-1
A=M
D=M
@5
M=D

// Call CLASS1.GET 0
@CLASS1.GET$ret.3
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
@CLASS1.GET
0;JMP
(CLASS1.GET$ret.3)

// Call CLASS2.GET 0
@CLASS2.GET$ret.4
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
@CLASS2.GET
0;JMP
(CLASS2.GET$ret.4)

// Label END
(SYS.INIT$END)

// Goto END
@SYS.INIT$END
0;JMP

