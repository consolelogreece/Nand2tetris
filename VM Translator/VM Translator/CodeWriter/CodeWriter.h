#include <string>
#include "CommandTypes.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

#pragma once
class CodeWriter
{
public:
	CodeWriter(std::string outputFileName);
	void writeArithmetic(std::string s);
	void writePushPop(CommandTypes type, std::string segment, int index);
	void setFileName(string name);
	void writeInit();
	void writeLabel(string label);
	void writeGoto(string label);
	void writeIf(string label);
	void writeFunction(string fName, int nVars);
	void writeCall(string fName, int nArgs);
	void writeReturn();
	void close();
	void flush();

private:
	ofstream outFile;
	int labelCount;
	string newLabel();
	int nextLabelCounter();
	string filename;
	map<string, string> segmentMap;
	string currentFuncName;
	vector<string> lines;

	void push(string segment, int index);
	void pushSetup(string segment, int index);
	void setupPushConstant(int val);
	void setupPushGeneric(string segment, int index);
	void setupPushTemp(int index);
	void setupPushStatic(int index);
	void setupPushPointer(int index);
	void performPush();

	void pop(string segment, int index);
	void processPoppedValue(string segment, int index);
	void processPoppedGeneric(string segment, int index);
	void processPoppedTemp(int index);
	void processPoppedStatic(int index);
	void processPoppedPointer(int index);
	void performPop();

	void add();
	void sub();
	void neg();
	void eq();
	void gt();
	void lt();
	void _and();
	void _or();
	void _not();
};

