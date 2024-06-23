#include "CodeWriter.h"
#include <vector>

void CodeWriter::writeLabel(string label)
{
	lines.push_back("// Label " + label);
	lines.push_back("(" + currentFuncName + "$" + label + ")");
	lines.push_back("\n");
}

void CodeWriter::writeGoto(string label)
{
	lines.push_back("// Goto " + label);
	lines.push_back("@" + currentFuncName + "$" + label);
	lines.push_back("0;JMP");
	lines.push_back("\n");
}

void CodeWriter::writeIf(string label)
{
	lines.push_back("// If-goto " + label);
	performPop();
	lines.push_back("@" + currentFuncName + "$" + label);
	lines.push_back("D;JNE");
	lines.push_back("\n");
}
