#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashMap.h"
#include "Utils.h"

#define MAX_LABEL_LENGTH 50

typedef struct CInstruction {
    char *dest;
    char *comp;
    char *jump;
} CInstruction;

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

int DetermineLineType(char* line)
{
    char* c;

    for (c = line; *c != '\0'; c++)
    {
        if (IsWhitespace(*c) == 1) continue;
        else if (*c == '/') return 0; // comment/whitespace - line is a comment, no such thing as /**/ comments in hack...
        else if (*c == '(') return 1; // label
        else if (*c == '@') return 2; // A instruction
        else return 3; // Only possiblity left is C instruction.
    }

    // comment/whitespace
    return 0;
}

char* ProcessLabel(char* line)
{
    char* c;
    int symbolLine = -1;

    char* label = malloc(sizeof(char) * MAX_LABEL_LENGTH);
    if (!label) return NULL;

    int labelCharIndex = 0;

    for (c = line; *c != '\0'; c++)
    {
        if (symbolLine == 1)
        {
            if (*c == ')')
            {
                label[labelCharIndex] = '\0';
                return label;
            }

            label[labelCharIndex] = *c;
            labelCharIndex++;
        }
        else if (IsWhitespace(*c) == 1) continue;
        else if (*c == '(')
        {
            symbolLine = 1;
            continue;
        }
        // Non whitespace character before open bracket, thus cannot be a label.
        else return NULL;
    }

    // If we end up here, it's either not a label or the line wasn't terminated with \0.
    return NULL;
}

char* ParseAIntruction(char* line)
{
    char* c;
    int IsAInstruction = -1;

    char* symbol = malloc(sizeof(char) * MAX_LABEL_LENGTH + 1);
    if (!symbol) return NULL;

    int labelCharIndex = 0;

    for (c = line; *c != '\0'; c++)
    {
        if (IsAInstruction == 1)
        {
            // in hack assembly language, / has no other usage beside a comment, 
            // so if we see a / we know it's a comment, even though comments are //.
            if (IsWhitespace(*c) == 1 || *c == '/')
            {
                symbol[labelCharIndex] = '\0';
                return symbol;
            }

            symbol[labelCharIndex] = *c;
            labelCharIndex++;
        }
        else if (IsWhitespace(*c) == 1) continue;
        else if (*c == '@')
        {
            IsAInstruction = 1;
            continue;
        }
        else return NULL;
    }
    
    // Terminate wih \0 as,if there is no whitespace after the A instruction, the loop above ends without terminating it.
   if (IsAInstruction == 1) 
   {
       symbol[labelCharIndex] = '\0';
       return symbol;
   }

   return NULL;
}

char *ProcessAInstruction(HashMap* symboltbl, char* line, int *symbolCount)
{ 
    char* symbol = ParseAIntruction(line);

    if (symbol != NULL)
    {
        char instruction[16];
        char* symbolValue = GetValue(symboltbl, symbol);

        // variable not defined yet, so add to symbol table.
        if (symbolValue == NULL)
        {
            // must be a explicit jump to a line number.
            if (ContainsOnlyNumbers(symbol) == 1)
            {
                symbolValue = symbol;
            }
            else
            {
                char* symbolCountString = malloc(sizeof(char) * 17);
                if (!symbolCountString) return NULL;
                (*symbolCount)++;
                sprintf_s(symbolCountString, 17, "%d\0", *symbolCount);
                
                SetItem(symboltbl, symbol, symbolCountString, 0, 0);
                symbolValue = GetValue(symboltbl, symbol);
            }
        }

        int symbolIntVal = atoi(symbolValue);
        _itoa_s(symbolIntVal, instruction, 16, 2);
        return PadLeft(instruction, '0', 16);
    }

    return NULL;
}

CInstruction* ParseCInstruction(char* line)
{
    CInstruction *instruction = malloc(sizeof(CInstruction));
    if (!instruction) return NULL;

    char* dest = malloc(sizeof(char) * 4);
    char* comp = malloc(sizeof(char) * 4);
    char* jump = malloc(sizeof(char) * 4);

    if (!jump || !comp || !dest) return NULL;
    dest[0] = '\0'; comp[0] = '\0'; jump[0] = '\0';

    instruction->comp = comp;
    instruction->dest = dest;
    instruction->jump = jump;

    char* c;

    int compProcessed = 0;

    char buffer[4];
   
    int bufferIndex = 0;

    for (c = line;; c++)
    {
        if (IsWhitespace(*c) == 1) continue;
        // buffer must contain the destination;
        else if (*c == '=')
        {
            buffer[bufferIndex] = '\0';
            strcpy_s(dest, 4, buffer);
            bufferIndex = 0;
        }
        // buffer must be computation
        else if (*c == ';')
        {
            buffer[bufferIndex] = '\0';
            strcpy_s(comp, 4, buffer);
            bufferIndex = 0;
            compProcessed = 1;
        }
        else if (*c == '\0' || *c == '\\')
        {
            buffer[bufferIndex] = '\0';
            bufferIndex = 0;

            // reached end of line, if comp has been processed it must be a jump in the buffer, otherwise it's the comp.
            if (compProcessed == 0) strcpy_s(comp, 4, buffer);            
            else strcpy_s(jump, 4, buffer);
            
            break;
        }
        else {
            buffer[bufferIndex] = *c;
            bufferIndex++;
        }
    }

    return instruction;
}

char* ProcessCInstruction(char* line, HashMap *destMap, HashMap *compMap, HashMap *jumpMap)
{
    CInstruction* instruction = ParseCInstruction(line);

    char* dest = GetValue(destMap, instruction->dest);
    char* comp = GetValue(compMap, instruction->comp);
    char* jump = GetValue(jumpMap, instruction->jump);

    char *binary = malloc(sizeof(char) * 17);
    if (!binary) return NULL;

    sprintf_s(binary, 17, "111%s%s%s\0", comp, dest, jump);

    free(instruction->comp);
    free(instruction->dest);
    free(instruction->jump);
    free(instruction);

    return binary;
}

int HandleLineFirstPass(HashMap* symboltbl, char* line, int *linecount)
{
    int linetype = DetermineLineType(line);

    int retval = -1;

    // Label line type.
    if (linetype == 1)
    {
        char* label = ProcessLabel(line);

        if (label != NULL)
        {
            char* lineCountString = malloc(sizeof(char) * 15);
            if (!lineCountString) return -1;
            sprintf_s(lineCountString, 15, "%d\0", *linecount);

            SetItem(symboltbl, label, lineCountString, 0, 0);

            retval = 1;
        }
    }

    if (linetype != 0 && linetype != 1) (*linecount)++;

    return retval;
}

void HandleLineSecondPass(HashMap* symboltbl, char* line, int* lineCount, int* symbolCount, HashMap* destmap, HashMap* compmap, HashMap* jumpmap, FILE* out)
{
    int linetype = DetermineLineType(line);

    if (linetype == 2)
    {
        char* instruction = ProcessAInstruction(symboltbl, line, symbolCount);
        
        fprintf(out, "%s\n", instruction);
        
    }
    else if (linetype == 3)
    {
        char* instruction = ProcessCInstruction(line, destmap, compmap, jumpmap);

        fprintf(out, "%s\n", instruction);
    }

    if (linetype != 0 && linetype != 1) (*lineCount)++;
}

int main(int argc, char** argv) 
{
    if (argc != 3) {
        printf("Usage: %s <input_file_path> <output_file_path>\n", argv[0]);
        return 1;
    }

    const char* input_file_path = argv[1];
    const char* output_file_path = argv[2];

    HashMap* symboltbl = InitializeSymbolTable();
    HashMap* compmap = InitializeCompMap();
    HashMap* destmap = InitializeDestMap();
    HashMap* jumpmap = InitializeJumpMap();
    FILE* fptr;
    FILE* fptrout;
    fopen_s(&fptr, input_file_path, "r");
    fopen_s(&fptrout, output_file_path, "w");
    int* linecount = malloc(sizeof(int));
    int* symbolCount = malloc(sizeof(int));

    if (!symboltbl || !compmap || !destmap || !jumpmap || !fptr || !fptrout || !linecount || !symbolCount) return -1;

    char lineBuffer[1000];
    *linecount = 0;
    *symbolCount = 15;

    while (fgets(lineBuffer, 1000, fptr)) {
        HandleLineFirstPass(symboltbl, lineBuffer, linecount);
    }

    rewind(fptr);
    *linecount = 0;

    while (fgets(lineBuffer, 1000, fptr)) {
        HandleLineSecondPass(symboltbl, lineBuffer, linecount,symbolCount, destmap, compmap, jumpmap, fptrout);
    }

    fclose(fptr);
    fclose(fptrout);

    free(linecount);
    free(symbolCount);
    free(fptr);
    free(fptrout);
    FreeHashMap(symboltbl);
    FreeHashMap(compmap);
    FreeHashMap(destmap);
    FreeHashMap(jumpmap);

    return 0;
}