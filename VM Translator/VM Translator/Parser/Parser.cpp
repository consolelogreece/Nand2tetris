#include "Parser.h"
#include "CommandTypes.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


Parser::Parser(std::string fileName)
{
	arg2Value = 0;
	commandTypeValue = CommandTypes::UNKNOWN;

	inputFile = ifstream();
	inputFile.open(fileName);

	commandMap["PUSH"] = CommandTypes::PUSH;
	commandMap["POP"] = CommandTypes::POP;
	commandMap["ADD"] = CommandTypes::ARITHMETIC;
	commandMap["SUB"] = CommandTypes::ARITHMETIC;
	commandMap["NEG"] = CommandTypes::ARITHMETIC;
	commandMap["EQ"] = CommandTypes::ARITHMETIC;
	commandMap["GT"] = CommandTypes::ARITHMETIC;
	commandMap["LT"] = CommandTypes::ARITHMETIC;
	commandMap["AND"] = CommandTypes::ARITHMETIC;
	commandMap["OR"] = CommandTypes::ARITHMETIC;
	commandMap["NOT"] = CommandTypes::ARITHMETIC;
	commandMap["LABEL"] = CommandTypes::LABEL;
	commandMap["IF-GOTO"] = CommandTypes::IF;
	commandMap["GOTO"] = CommandTypes::GOTO;
	commandMap["CALL"] = CommandTypes::CALL;
	commandMap["FUNCTION"] = CommandTypes::FUNCTION;
	commandMap["RETURN"] = CommandTypes::RETURN;

	eof = false;
}

bool Parser::hasMoreCommands()
{
	return !eof;
}

bool Parser::advance()
{
	string line = getNextValidLine();

	line = trim(line, "\t");
	line = trim(line, " ");

	if (eof) return false;

	line = ToUpper(line);

	vector<string> symbols;
	DecomposeString(line, ' ', symbols);

	commandTypeValue = commandMap[symbols[0]];

	if (symbols.size() >= 2 && commandTypeValue != CommandTypes::ARITHMETIC) arg1Value = symbols[1];
	else arg1Value = symbols[0];

	if (symbols.size() >= 3) arg2Value = atoi(symbols[2].c_str());		

	return true;
}

string Parser::getNextValidLine()
{
	bool validLineFound = false;
	string line;

	do {
		if (inputFile.eof())
		{
			eof = true;
			break;
		}
		getline(inputFile, line);
		validLineFound = (line.size() > 0 && line[0] != '/');
	} while (validLineFound == false);

	return line;
}

string Parser::ToUpper(string str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);

	return str;
}

void Parser::DecomposeString(string line, char delimiter, vector<string> &outVect)
{
	int pos, i = 0;
	do {
		pos = line.find(delimiter, i);
		outVect.push_back(line.substr(i, pos - i));
		i = pos + 1;
	} while (pos != -1);
}

CommandTypes Parser::commandType()
{
	return commandTypeValue;
}

string Parser::arg1()
{
	return arg1Value;
}

int Parser::arg2()
{
	return arg2Value;
}

// copied from internet
std::string Parser::trim(const std::string& str, const std::string& whitespace = " \t") {
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return "";

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;
	return str.substr(strBegin, strRange);
}