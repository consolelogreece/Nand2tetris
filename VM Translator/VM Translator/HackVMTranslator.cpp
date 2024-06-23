#include <iostream>
#include <string>
#include "Parser.h"
#include "CodeWriter.h"
#include <filesystem>
using namespace std;

void processFile(string filepath, CodeWriter& c)
{
    Parser p(filepath);

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
            case CommandTypes::CALL:
                c.writeCall(arg1, arg2);
                break;
            case CommandTypes::FUNCTION:
                c.writeFunction(arg1, arg2);
                break;
            case CommandTypes::RETURN:
                c.writeReturn();
                break;
            case CommandTypes::LABEL:
                c.writeLabel(arg1);
                break;
            case CommandTypes::GOTO:
                c.writeGoto(arg1);
                break;
            case CommandTypes::IF:
                c.writeIf(arg1);
                break;
            default:
                break;
            }

            c.flush();
        }
    }
}

int main(int argc, char** argv)
{

    if (argc < 2)
    {
        cout << "Please provide a file to translate, and optionally an output file.\nUsage <source directory/filename> <output directory>.\n";
        return -1;
    }

    auto sourcePath = std::filesystem::path(argv[1]);
    auto outPath = std::filesystem::path(argv[1]);
    if (argc > 2) outPath = std::filesystem::path(argv[2]);

    if (sourcePath.has_extension() && sourcePath.extension() != ".vm")
    {
        cout << "Invalid file type. Must be .vm" << endl;
        return 1;
    }

    // Set to .asm just incase not provided.
    outPath = outPath.replace_extension(".asm").string();

    CodeWriter c(outPath.string());
    
    // Note: This will need to be commented out if translating a basic program with no sys.init defined.
    c.writeInit();

    if (!sourcePath.has_extension())
    {
        for (const auto& entry : std::filesystem::directory_iterator(sourcePath))
        {
            auto pathd = std::filesystem::path(entry);

            if (pathd.extension() == ".vm")
            {
                c.setFileName(pathd.filename().string());
                processFile(pathd.string(), c);
            }
        }
    }
    else
    {
        processFile(sourcePath.string(), c);
    }

    c.close();
}
