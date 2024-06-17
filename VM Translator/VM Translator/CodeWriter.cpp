#include "CodeWriter.h"
#include <iostream>
#include <fstream>
#include <format>
using namespace std;

CodeWriter::CodeWriter(std::string outputFileName, string fn)
{
	outFile = ofstream();
	outFile.open(outputFileName);
	segmentMap["LOCAL"] = "LCL";
	segmentMap["ARGUMENT"] = "ARG";
	segmentMap["THIS"] = "THIS";
	segmentMap["THAT"] = "THAT";
	segmentMap["POINTER0"] = "3";
	segmentMap["POINTER1"] = "4";
	filename = fn;
	labelCount = 0;
}

void CodeWriter::writePushPop(CommandTypes type, std::string segment, int index)
{
	if (type == CommandTypes::POP) pop(segment, index);
	else if (CommandTypes::PUSH) push(segment, index);
}

void CodeWriter::push(string segment, int index)
{
	outFile << "// Push " << segment << " " << index << endl;

	pushSetup(segment, index);

	performPush();

	outFile << endl;

	outFile.flush();
}

// Write the assembly necessary to get the value to be pushed onto the stack.
void CodeWriter::pushSetup(string segment, int index)
{
	if (segment == "CONSTANT") setupPushConstant(index);
	else if (segment == "TEMP") setupPushTemp(index);
	else if (segment == "STATIC") setupPushStatic(index);
	else if (segment == "POINTER") setupPushPointer(index);
	else setupPushGeneric(segment, index);
}

void CodeWriter::setupPushConstant(int val)
{
	outFile << "@" << val << endl;
	outFile << "D=A" << endl;
}

void CodeWriter::setupPushTemp(int index)
{
	outFile << "@" << 5 + index << endl;
	outFile << "D=M" << endl;
}

void CodeWriter::setupPushStatic(int index)
{
	outFile << "@" << filename << "." << index << endl;
	outFile << "D=M" << endl;
}

void CodeWriter::setupPushPointer(int index)
{
	index += 3; // hack memory this is at ram 3, which we access with index 0, and that is at ram 4.
	outFile << "@" << index << endl;
	outFile << "D=M" << endl;
}

void CodeWriter::setupPushGeneric(string segment, int index)
{
	outFile << "@" << segmentMap[segment] << endl;
	outFile << "D=M" << endl;
	outFile << "@" << index << endl;
	outFile << "D=D+A" << endl;
	outFile << "A=D" << endl;
	outFile << "D=M" << endl;
}

// Puts value from D register at SP location and then increments SP
void CodeWriter::performPush()
{
	outFile << "@SP" << endl;
	outFile << "A=M" << endl;
	outFile << "M=D" << endl;
	outFile << "@SP" << endl;
	outFile << "M=M+1" << endl;
}

void CodeWriter::pop(string segment, int index)
{
	outFile << "// Pop " << segment << " " << index << endl;

	performPop();

	processPoppedValue(segment, index);

	outFile << endl;

	outFile.flush();
}

void CodeWriter::processPoppedValue(string segment, int index)
{
	if (segment == "TEMP") processPoppedTemp(index);
	else if (segment == "STATIC") processPoppedStatic(index);
	else if (segment == "POINTER") processPoppedPointer(index);
	else processPoppedGeneric(segment, index);
}

void CodeWriter::processPoppedGeneric(string segment, int index)
{
	outFile << "@R13" << endl;
	outFile << "M=D" << endl;
	outFile << "@" << index << endl;
	outFile << "D=A" << endl;
	outFile << "@" << segmentMap[segment] << endl;
	outFile << "D=M+D" << endl;
	outFile << "@R14" << endl;
	outFile << "M=D" << endl;
	outFile << "@R13" << endl;
	outFile << "D=M" << endl;
	outFile << "@R14" << endl;
	outFile << "A=M" << endl;
	outFile << "M=D" << endl;
}

void CodeWriter::processPoppedTemp(int index)
{
	outFile << "@" << 5 + index << endl;
	outFile << "M=D" << endl;
}

void CodeWriter::processPoppedStatic(int index)
{
	// Static segment starts at 16, which is the first address used for variables in hack asm, so no index manipulation needed.
	outFile << "@" << filename << "." << index << endl;
	outFile << "M=D" << endl;
}
void CodeWriter::processPoppedPointer(int index)
{
	index += 3;
	outFile << "@" << index << endl;
	outFile << "M=D" << endl;
}

// Decrements SP and puts popped value in D register
void CodeWriter::performPop()
{
	outFile << "@SP" << endl;
	outFile << "M=M-1" << endl;
	outFile << "A=M" << endl;
	outFile << "D=M" << endl;
}

string CodeWriter::newLabel()
{
	return "gen_UNIQUE_" + to_string(labelCount++);
}

void CodeWriter::add()
{
	outFile << "// Add" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "M=D" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "D=M+D" << endl;
	performPush();
	outFile << endl;
}

void CodeWriter::sub()
{
	outFile << "// Sub" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "M=D" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "D=D-M" << endl;
	performPush();
	outFile << endl;
}

void CodeWriter::neg()
{
	outFile << "// Neg" << endl;
	performPop();
	outFile << "D=-D" << endl;
	performPush();
	outFile << endl;
}

void CodeWriter::eq()
{
	string conditionalJumpLabel = newLabel();
	string pushLabel = newLabel();

	outFile << "// Eq" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "M=D" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "D=D-M" << endl;
	outFile << "@" << conditionalJumpLabel << endl;
	outFile << "D;JEQ" << endl;
	outFile << "D=0" << endl;
	outFile << "@" << pushLabel << endl;
	outFile << "0;JMP" << endl;
	outFile << "(" << conditionalJumpLabel << ")" << endl;
	outFile << "D=-1" << endl;
	outFile << "(" << pushLabel << ")" << endl;
	performPush();
	outFile << endl;
}

void CodeWriter::gt()
{
	string conditionalJumpLabel = newLabel();
	string pushLabel = newLabel();

	outFile << "// Gt" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "M=D" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "D=D-M" << endl;
	outFile << "@" << conditionalJumpLabel << endl;
	outFile << "D;JGT" << endl;
	outFile << "D=0" << endl;
	outFile << "@" << pushLabel << endl;
	outFile << "0;JMP" << endl;
	outFile << "(" << conditionalJumpLabel << ")" << endl;
	outFile << "D=-1" << endl;
	outFile << "(" << pushLabel << ")" << endl;
	performPush();
	outFile << endl;
}

void CodeWriter::lt()
{
	string conditionalJumpLabel = newLabel();
	string pushLabel = newLabel();

	outFile << "// Lt" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "M=D" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "D=D-M" << endl;
	outFile << "@" << conditionalJumpLabel << endl;
	outFile << "D;JLT" << endl;
	outFile << "D=0" << endl;
	outFile << "@" << pushLabel << endl;
	outFile << "0;JMP" << endl;
	outFile << "(" << conditionalJumpLabel << ")" << endl;
	outFile << "D=-1" << endl;
	outFile << "(" << pushLabel << ")" << endl;
	performPush();
	outFile << endl;
}

void CodeWriter::_and ()
{
	outFile << "// And" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "M=D" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "D=D&M" << endl;
	performPush();
	outFile << endl;
}

void CodeWriter::_or()
{
	outFile << "// Or" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "M=D" << endl;
	performPop();
	outFile << "@R13" << endl;
	outFile << "D=D|M" << endl;
	performPush();
	outFile << endl;
}

void CodeWriter::_not()
{
	outFile << "// Not" << endl;
	performPop();
	outFile << "D=!D" << endl;
	performPush();
	outFile << endl;
}

void CodeWriter::writeArithmetic(std::string op)
{
	if (op == "ADD") add();
	else if (op == "SUB") sub();
	else if (op == "NEG") neg();
	else if (op == "EQ") eq();
	else if (op == "GT") gt();
	else if (op == "LT") lt();
	else if (op == "AND") _and();
	else if (op == "OR") _or();
	else if (op == "NOT") _not();	
}

void CodeWriter::close()
{
	outFile.close();

	cout << "file closed";
}