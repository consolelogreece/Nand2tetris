#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HackTables.h"
#include "utils.h"
#include "Parser.h"

char *ProcessAInstruction(HashMap* symboltbl, char* line, int *symbolCount)
{ 
    char instruction[16];
    char* symbol = ParseAIntruction(line);
    char* symbolValue = GetValue(symboltbl, symbol);

    // Variable not defined yet, so add to symbol table.
    if (symbolValue == NULL)
    {
        // If contains only numbers, it must be a number, i.e. an explicit line number.
        if (ContainsOnlyNumbers(symbol) == 1) symbolValue = symbol;
        else
        {
            char* symbolCountString = malloc(sizeof(char) * 17);
            if (!symbolCountString) return NULL;
            sprintf_s(symbolCountString, 17, "%d\0", ++(*symbolCount));
                
            SetItem(symboltbl, symbol, symbolCountString, 0, 0);
            symbolValue = GetValue(symboltbl, symbol);
        }
    }

    int symbolIntVal = atoi(symbolValue);
    _itoa_s(symbolIntVal, instruction, 16, 2);
    return PadLeft(instruction, '0', 16);
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

void HandleLineFirstPass(HashMap* symboltbl, char* line, int *linecount)
{
    int linetype = DetermineLineType(line);

    // Label line type.
    if (linetype == 1)
    {
        char* label = ParseLabel(line);

        if (label != NULL)
        {
            char* lineCountString = malloc(sizeof(char) * 15);
            if (!lineCountString) return;
            sprintf_s(lineCountString, 15, "%d\0", *linecount);

            SetItem(symboltbl, label, lineCountString, 0, 0);
        }
    }

    if (linetype != 0 && linetype != 1) (*linecount)++;
}

void HandleLineSecondPass(HashMap* symboltbl, char* line, int* lineCount, int* symbolCount, HashMap* destmap, HashMap* compmap, HashMap* jumpmap, FILE* out)
{
    int linetype = DetermineLineType(line);
    
    if (linetype == 2)
    {
        char* instruction = ProcessAInstruction(symboltbl, line, symbolCount);
        fprintf(out, "%s\n", instruction);
        (*lineCount)++;
    }
    else if (linetype == 3)
    {
        char* instruction = ProcessCInstruction(line, destmap, compmap, jumpmap);
        fprintf(out, "%s\n", instruction);
        (*lineCount)++;
    }
}

int main(int argc, char** argv) 
{
    if (argc != 3) {
        printf("Usage: %s <input_file_path> <output_file_path>\n", argv[0]);
        return 1;
    }

    const char* input_file_path = argv[1];
    const char* output_file_path = argv[2];
    FILE* fptr;
    FILE* fptrout;
    fopen_s(&fptr, input_file_path, "r");
    fopen_s(&fptrout, output_file_path, "w");
    HashMap* symboltbl = InitializeSymbolTable();
    HashMap* compmap = InitializeCompMap();
    HashMap* destmap = InitializeDestMap();
    HashMap* jumpmap = InitializeJumpMap();
    int* linecount = malloc(sizeof(int));
    int* symbolCount = malloc(sizeof(int));

    if (!symboltbl || !compmap || !destmap || !jumpmap || !fptr || !fptrout || !linecount || !symbolCount) return -1;

    char lineBuffer[1000];
    *linecount = 0;
    *symbolCount = 15;

    while (fgets(lineBuffer, 1000, fptr)) HandleLineFirstPass(symboltbl, lineBuffer, linecount);

    rewind(fptr);
    *linecount = 0;

    while (fgets(lineBuffer, 1000, fptr)) HandleLineSecondPass(symboltbl, lineBuffer, linecount,symbolCount, destmap, compmap, jumpmap, fptrout);

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