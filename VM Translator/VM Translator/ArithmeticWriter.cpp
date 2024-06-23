#include "CodeWriter.h"
#include <vector>

void CodeWriter::writeArithmetic(std::string op)
{
	lines.push_back("// " + op);
	if (op == "ADD") add();
	else if (op == "SUB") sub();
	else if (op == "NEG") neg();
	else if (op == "EQ") eq();
	else if (op == "GT") gt();
	else if (op == "LT") lt();
	else if (op == "AND") _and();
	else if (op == "OR") _or();
	else if (op == "NOT") _not();
	lines.push_back("\n");
}

void CodeWriter::add()
{
	performPop();
	lines.push_back("@R13");
	lines.push_back("M=D");
	performPop();
	lines.push_back("@R13");
	lines.push_back("D=M+D");
	performPush();
}

void CodeWriter::sub()
{
	performPop();
	lines.push_back("@R13");
	lines.push_back("M=D");
	performPop();
	lines.push_back("@R13");
	lines.push_back("D=D-M");
	performPush();
}

void CodeWriter::neg()
{
	performPop();
	lines.push_back("D=-D");
	performPush();
}

void CodeWriter::eq()
{
	string conditionalJumpLabel = newLabel();
	string pushLabel = newLabel();

	performPop();
	lines.push_back("@R13");
	lines.push_back("M=D");
	performPop();
	lines.push_back("@R13");
	lines.push_back("D=D-M");
	lines.push_back("@" + conditionalJumpLabel);
	lines.push_back("D;JEQ");
	lines.push_back("D=0");
	lines.push_back("@" + pushLabel);
	lines.push_back("0;JMP");
	lines.push_back("(" + conditionalJumpLabel + ")");
	lines.push_back("D=-1");
	lines.push_back("(" + pushLabel + ")");
	performPush();
}

void CodeWriter::gt()
{
	string conditionalJumpLabel = newLabel();
	string pushLabel = newLabel();

	performPop();
	lines.push_back("@R13");
	lines.push_back("M=D");
	performPop();
	lines.push_back("@R13");
	lines.push_back("D=D-M");
	lines.push_back("@" + conditionalJumpLabel);
	lines.push_back("D;JGT");
	lines.push_back("D=0");
	lines.push_back("@" + pushLabel);
	lines.push_back("0;JMP");
	lines.push_back("(" + conditionalJumpLabel + ")");
	lines.push_back("D=-1");
	lines.push_back("(" + pushLabel + ")");
	performPush();
}

void CodeWriter::lt()
{
	string conditionalJumpLabel = newLabel();
	string pushLabel = newLabel();

	performPop();
	lines.push_back("@R13");
	lines.push_back("M=D");
	performPop();
	lines.push_back("@R13");
	lines.push_back("D=D-M");
	lines.push_back("@" + conditionalJumpLabel);
	lines.push_back("D;JLT");
	lines.push_back("D=0");
	lines.push_back("@" + pushLabel);
	lines.push_back("0;JMP");
	lines.push_back("(" + conditionalJumpLabel + ")");
	lines.push_back("D=-1");
	lines.push_back("(" + pushLabel + ")");
	performPush();
}

void CodeWriter::_and()
{
	performPop();
	lines.push_back("@R13");
	lines.push_back("M=D");
	performPop();
	lines.push_back("@R13");
	lines.push_back("D=D&M");
	performPush();
}

void CodeWriter::_or()
{
	performPop();
	lines.push_back("@R13");
	lines.push_back("M=D");
	performPop();
	lines.push_back("@R13");
	lines.push_back("D=D|M");
	performPush();
}

void CodeWriter::_not()
{
	performPop();
	lines.push_back("D=!D");
	performPush();
}