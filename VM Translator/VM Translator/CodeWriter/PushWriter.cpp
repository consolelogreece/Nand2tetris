#include "CodeWriter.h"
#include <vector>

void CodeWriter::push(string segment, int index)
{
	lines.push_back("// Push " + segment + " " + to_string(index));
	pushSetup(segment, index);
	performPush();
	lines.push_back("\n");
}

// Write the assembly necessary to get the value to be pushed onto the stack.
void CodeWriter::pushSetup(string segment, int index)
{
	if (segment == "CONSTANT") setupPushConstant(index);
	else if (segment == "TEMP") setupPushTemp(index);
	else if (segment == "STATIC") setupPushStatic(index);
	else if (segment == "POINTER") setupPushPointer(index);
	else setupPushGeneric(segmentMap[segment], index);
}

void CodeWriter::setupPushConstant(int val)
{
	lines.push_back("@" + to_string(val));
	lines.push_back("D=A");
}

void CodeWriter::setupPushTemp(int index)
{
	lines.push_back("@" + to_string(5 + index));
	lines.push_back("D=M");
}

void CodeWriter::setupPushStatic(int index)
{
	lines.push_back("@" + filename + "." + to_string(index));
	lines.push_back("D=M");
}

void CodeWriter::setupPushPointer(int index)
{
	index += 3; //pointer[0] is 3, pointer[1] is 4, hence offset.
	lines.push_back("@" + to_string(index));
	lines.push_back("D=M");
}

void CodeWriter::setupPushGeneric(string segment, int index)
{
	lines.push_back("@" + segment);
	lines.push_back("D=M");
	lines.push_back("@" + to_string(index));
	lines.push_back("D=D+A");
	lines.push_back("A=D");
	lines.push_back("D=M");
}

// Puts value from D register at SP location and then increments SP
void CodeWriter::performPush()
{
	lines.push_back("@SP");
	lines.push_back("A=M");
	lines.push_back("M=D");
	lines.push_back("@SP");
	lines.push_back("M=M+1");
}