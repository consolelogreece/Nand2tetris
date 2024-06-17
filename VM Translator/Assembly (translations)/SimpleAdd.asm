////////////// Push CONSTANT 7 //////////////
@7
D=A
@SP
A=M
M=D
@SP
M=M+1
////////////// Push CONSTANT 8 //////////////
@8
D=A
@SP
A=M
M=D
@SP
M=M+1
////////////// Pop LOCAL 15 //////////////
@SP
M=M-1
A=M
D=M
@R13
M=D
@15
D=A
@LOCAL
D=A+D
@R14
M=D
@R13
D=M
@R14
A=M
M=D
