#include <iostream>
#include <string>
#include "Parser.h"
#include "CodeWriter.h"
using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cout << "Please provide a file to translate, and an output file.\n";

        return -1;
    }
    
    Parser p(argv[0]);
    CodeWriter c(argv[1], argv[0]);  

    while (p.hasMoreCommands())
    {
        if (p.advance())
        {
            CommandTypes ct = p.commandType();
            string arg1 = p.arg1();
            int arg2 = p.arg2();

            switch (ct) {
                case CommandTypes::ARITHMETIC:
                    c.writeArithmetic(arg1);
                    break;
                case CommandTypes::POP:
                case CommandTypes::PUSH:
                    c.writePushPop(ct, arg1, arg2);
                    break;
                default:
                    break;
            }
        }
    }

    c.close();
}
