#include "CodeWriter.h"
#include <vector>

void CodeWriter::writeCall(string fName, int nArgs)
{
	lines.push_back("// Call " + fName + " " + to_string(nArgs));
	string retAddr = fName + "$ret." + to_string(nextLabelCounter());

	// push return address, lcl, arg, this, that
	lines.push_back("@" + retAddr);
	lines.push_back("D=A");
	performPush();

	lines.push_back("@LCL");
	lines.push_back("D=M");
	performPush();

	lines.push_back("@ARG");
	lines.push_back("D=M");
	performPush();

	lines.push_back("@THIS");
	lines.push_back("D=M");
	performPush();

	lines.push_back("@THAT");
	lines.push_back("D=M");
	performPush();

	// set arg to current sp - 5 - nargs
	lines.push_back("@" + to_string(nArgs + 5));
	lines.push_back("D=A");
	lines.push_back("@SP");
	lines.push_back("D=M-D");
	lines.push_back("@ARG");
	lines.push_back("M=D");

	//LCL = SP
	lines.push_back("@SP");
	lines.push_back("D=M");
	lines.push_back("@LCL");
	lines.push_back("M=D");

	// goto func
	lines.push_back("@" + fName);
	lines.push_back("0;JMP");

	lines.push_back("(" + retAddr + ")");

	lines.push_back("\n");
}

void CodeWriter::writeFunction(string fName, int nVars)
{
	currentFuncName = fName;

	lines.push_back("// Function " + fName + " " + to_string(nVars));
	lines.push_back("(" + fName + ")");

	lines.push_back("@0");
	lines.push_back("D=A");

	for (int i = 0; i < nVars; i++)performPush();
	
	lines.push_back("\n");
}

void CodeWriter::writeReturn()
{
	lines.push_back("// Return");
	//endFrame = LCL
	lines.push_back("@LCL");
	lines.push_back("D=M");
	lines.push_back("@endFrame");
	lines.push_back("M=D");

	//retAddr = *(endFrame - 5);
	lines.push_back("@5");
	lines.push_back("D=A");
	lines.push_back("@endFrame");
	lines.push_back("A=M-D");
	lines.push_back("D=M");
	lines.push_back("@retAddr");
	lines.push_back("M=D");

	//*arg = pop()
	performPop();
	lines.push_back("@ARG");
	lines.push_back("A=M");
	lines.push_back("M=D");

	//SP = ARG + 1
	lines.push_back("@ARG");
	lines.push_back("D=M");
	lines.push_back("@SP");
	lines.push_back("M=D+1");

	//THAT = *(endFrame - 1);
	lines.push_back("@endFrame");
	lines.push_back("A=M-1");
	lines.push_back("D=M");
	lines.push_back("@THAT");
	lines.push_back("M=D");

	//THIS = *(endFrame - 2);
	lines.push_back("@2");
	lines.push_back("D=A");
	lines.push_back("@endFrame");
	lines.push_back("A=M-D");
	lines.push_back("D=M");
	lines.push_back("@THIS");
	lines.push_back("M=D");

	//ARG = *(endFrame - 3);
	lines.push_back("@3");
	lines.push_back("D=A");
	lines.push_back("@endFrame");
	lines.push_back("A=M-D");
	lines.push_back("D=M");
	lines.push_back("@ARG");
	lines.push_back("M=D");

	//LCL = *(endFrame - 4);
	lines.push_back("@4");
	lines.push_back("D=A");
	lines.push_back("@endFrame");
	lines.push_back("A=M-D");
	lines.push_back("D=M");
	lines.push_back("@LCL");
	lines.push_back("M=D");

	//goto retAddr
	lines.push_back("@retAddr");
	lines.push_back("A=M");
	lines.push_back("0;JMP");

	lines.push_back("\n");
}