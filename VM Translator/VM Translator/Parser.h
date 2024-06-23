#include <string>
#include "CommandTypes.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#pragma once
class Parser
{
	public:
		Parser(std::string fileName);
		bool hasMoreCommands();
		bool advance();
		CommandTypes commandType();
		std::string arg1();
		int arg2();
	
	private:
		void DecomposeString(string s, char delim, vector<string> &outVect);
		ifstream inputFile;
		map<string, CommandTypes> commandMap;
		string arg1Value;
		int arg2Value;
		CommandTypes commandTypeValue;
		string ToUpper(string str);
		string getNextValidLine();
		bool eof;
		std::string trim(const std::string& str, const std::string& whitespace);
};

