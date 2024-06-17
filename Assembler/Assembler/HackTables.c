#include "HashMap.h"

HashMap* InitializeSymbolTable()
{
    HashMap* symboltbl = NewHashMap();

    SetItem(symboltbl, "R0\0", "0\0", 1, 1);
    SetItem(symboltbl, "R1\0", "1\0", 1, 1);
    SetItem(symboltbl, "R2\0", "2\0", 1, 1);
    SetItem(symboltbl, "R3\0", "3\0", 1, 1);
    SetItem(symboltbl, "R4\0", "4\0", 1, 1);
    SetItem(symboltbl, "R5\0", "5\0", 1, 1);
    SetItem(symboltbl, "R6\0", "6\0", 1, 1);
    SetItem(symboltbl, "R7\0", "7\0", 1, 1);
    SetItem(symboltbl, "R8\0", "8\0", 1, 1);
    SetItem(symboltbl, "R9\0", "9\0", 1, 1);
    SetItem(symboltbl, "R10\0", "10\0", 1, 1);
    SetItem(symboltbl, "R11\0", "11\0", 1, 1);
    SetItem(symboltbl, "R12\0", "12\0", 1, 1);
    SetItem(symboltbl, "R13\0", "13\0", 1, 1);
    SetItem(symboltbl, "R14\0", "14\0", 1, 1);
    SetItem(symboltbl, "R15\0", "15\0", 1, 1);

    SetItem(symboltbl, "SCREEN\0", "16384\0", 1, 1);
    SetItem(symboltbl, "KBD\0", "24576\0", 1, 1);

    SetItem(symboltbl, "SP\0", "0\0", 1, 1);
    SetItem(symboltbl, "LCL\0", "1\0", 1, 1);
    SetItem(symboltbl, "ARG\0", "2\0", 1, 1);
    SetItem(symboltbl, "THIS\0", "3\0", 1, 1);
    SetItem(symboltbl, "THAT\0", "4\0", 1, 1);

    return symboltbl;
}

HashMap* InitializeDestMap()
{
    HashMap* map = NewHashMap();

    SetItem(map, "", "000", 1, 1);
    SetItem(map, "M", "001", 1, 1);
    SetItem(map, "D", "010", 1, 1);
    SetItem(map, "MD", "011", 1, 1);
    SetItem(map, "A", "100", 1, 1);
    SetItem(map, "AM", "101", 1, 1);
    SetItem(map, "AD", "110", 1, 1);
    SetItem(map, "AMD", "111", 1, 1);

    return map;
}

HashMap* InitializeCompMap()
{
    HashMap* map = NewHashMap();

    SetItem(map, "0", "0101010", 1, 1);
    SetItem(map, "1", "0111111", 1, 1);
    SetItem(map, "-1", "0111010", 1, 1);
    SetItem(map, "D", "0001100", 1, 1);
    SetItem(map, "A", "0110000", 1, 1);
    SetItem(map, "M", "1110000", 1, 1);
    SetItem(map, "!D", "0001101", 1, 1);
    SetItem(map, "!A", "0110001", 1, 1);
    SetItem(map, "!M", "1110001", 1, 1);
    SetItem(map, "-D", "0001111", 1, 1);
    SetItem(map, "-A", "0110011", 1, 1);
    SetItem(map, "-M", "1110011", 1, 1);
    SetItem(map, "D+1", "0011111", 1, 1);
    SetItem(map, "1+D", "0011111", 1, 1);
    SetItem(map, "A+1", "0110111", 1, 1);
    SetItem(map, "M+1", "1110111", 1, 1);
    SetItem(map, "1+A", "0110111", 1, 1);
    SetItem(map, "1+M", "1110111", 1, 1);
    SetItem(map, "D-1", "0001110", 1, 1);
    SetItem(map, "A-1", "0110010", 1, 1);
    SetItem(map, "M-1", "1110010", 1, 1);
    SetItem(map, "D+A", "0000010", 1, 1);
    SetItem(map, "D+M", "1000010", 1, 1);
    SetItem(map, "A+D", "0000010", 1, 1);
    SetItem(map, "M+D", "1000010", 1, 1);
    SetItem(map, "D-A", "0010011", 1, 1);
    SetItem(map, "D-M", "1010011", 1, 1);
    SetItem(map, "A-D", "0000111", 1, 1);
    SetItem(map, "M-D", "1000111", 1, 1);
    SetItem(map, "D&A", "0000000", 1, 1);
    SetItem(map, "D&M", "1000000", 1, 1);
    SetItem(map, "D|A", "0010101", 1, 1);
    SetItem(map, "D|M", "1010101", 1, 1);

    return map;
}

HashMap* InitializeJumpMap()
{
    HashMap* map = NewHashMap();

    SetItem(map, "", "000", 1, 1);
    SetItem(map, "JGT", "001", 1, 1);
    SetItem(map, "JEQ", "010", 1, 1);
    SetItem(map, "JGE", "011", 1, 1);
    SetItem(map, "JLT", "100", 1, 1);
    SetItem(map, "JNE", "101", 1, 1);
    SetItem(map, "JLE", "110", 1, 1);
    SetItem(map, "JMP", "111", 1, 1);

    return map;
}