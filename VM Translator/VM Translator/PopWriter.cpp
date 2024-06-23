#include "CodeWriter.h"
#include <vector>

void CodeWriter::pop(string segment, int index)
{
	lines.push_back("// Pop " + segment + " " + to_string(index));
	performPop();
	processPoppedValue(segment, index);
	lines.push_back("\n");
}

void CodeWriter::processPoppedValue(string segment, int index)
{
	if (segment == "TEMP") processPoppedTemp(index);
	else if (segment == "STATIC") processPoppedStatic(index);
	else if (segment == "POINTER") processPoppedPointer(index);
	else processPoppedGeneric(segmentMap[segment], index);
}

void CodeWriter::processPoppedGeneric(string segment, int index)
{
	lines.push_back("@R13");
	lines.push_back("M=D");
	lines.push_back("@" + to_string(index));
	lines.push_back("D=A");
	lines.push_back("@" + segment);
	lines.push_back("D=M+D");
	lines.push_back("@R14");
	lines.push_back("M=D");
	lines.push_back("@R13");
	lines.push_back("D=M");
	lines.push_back("@R14");
	lines.push_back("A=M");
	lines.push_back("M=D");
}

void CodeWriter::processPoppedTemp(int index)
{
	lines.push_back("@" + to_string(5 + index));
	lines.push_back("M=D");
}

void CodeWriter::processPoppedStatic(int index)
{
	// Static segment starts at 16, which is the first address used for variables in hack asm, so no index manipulation needed.
	lines.push_back("@" + filename + "." + to_string(index));
	lines.push_back("M=D");
}

void CodeWriter::processPoppedPointer(int index)
{
	index += 3;
	lines.push_back("@" + to_string(index));
	lines.push_back("M=D");
}

// Decrements SP and puts popped value in D register
void CodeWriter::performPop()
{
	lines.push_back("@SP");
	lines.push_back("M=M-1");
	lines.push_back("A=M");
	lines.push_back("D=M");
}
