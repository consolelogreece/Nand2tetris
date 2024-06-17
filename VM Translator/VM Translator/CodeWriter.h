#include <string>
#include "CommandTypes.h"
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#pragma once
class CodeWriter
{
	public:
		CodeWriter(std::string outputFileName, string fn);
		void writeArithmetic(std::string s);
		void writePushPop(CommandTypes type, std::string segment, int index);
		void close();
	private:
		ofstream outFile;
		int labelCount;
		string newLabel();
		string filename;
		map<string, string> segmentMap;

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

