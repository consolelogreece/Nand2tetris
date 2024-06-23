#include "CodeWriter.h"
#include <iostream>
#include <fstream>
#include <format>
using namespace std;

CodeWriter::CodeWriter(std::string outputFileName)
{
	outFile = ofstream();
	outFile.open(outputFileName);
	segmentMap["LOCAL"] = "LCL";
	segmentMap["ARGUMENT"] = "ARG";
	segmentMap["THIS"] = "THIS";
	segmentMap["THAT"] = "THAT";
	segmentMap["TEMP"] = "TEMP";
	segmentMap["STATIC"] = "STATIC";
	segmentMap["POINTER"] = "POINTER";
	segmentMap["CONSTANT"] = "CONSTANT";
	filename = "";
	currentFuncName = "NULL";
	labelCount = 0;
}

void CodeWriter::writePushPop(CommandTypes type, std::string segment, int index)
{
	if (type == CommandTypes::POP) pop(segment, index);
	else if (CommandTypes::PUSH) push(segment, index);
}

int CodeWriter::nextLabelCounter()
{
	return labelCount++;
}

string CodeWriter::newLabel()
{
	return "gl_" + currentFuncName + "." + to_string(nextLabelCounter());
}

void CodeWriter::close()
{
	outFile.close();
}

void CodeWriter::setFileName(string name)
{
	currentFuncName = "NULL";
	filename = name;
}

void CodeWriter::writeInit()
{
	lines.push_back("// Init");
	lines.push_back("@256");
	lines.push_back("D=A");
	lines.push_back("@SP");
	lines.push_back("M=D");
	lines.push_back("\n");

	writeCall("SYS.INIT", 0);
	lines.push_back("\n");
}

void CodeWriter::flush()
{
	for (auto& line : lines) outFile << line << endl;

	lines.clear();
}
