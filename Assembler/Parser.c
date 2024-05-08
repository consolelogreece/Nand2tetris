#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "Parser.h"

#define MAX_LABEL_LENGTH 50

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

    // whitespace
    return 0;
}

char* ParseLabel(char* line)
{
    char* label = malloc(sizeof(char) * MAX_LABEL_LENGTH);
    if (!label) return NULL;

    char* c;
    int labelTextRead = -1;
    int labelCharIndex = 0;

    for (c = line; *c != '\0'; c++)
    {
        if (labelTextRead == 1)
        {
            if (*c == ')') break;

            label[labelCharIndex] = *c;
            labelCharIndex++;
        }
        else if (*c == '(') labelTextRead = 1;
    }

    label[labelCharIndex] = '\0';
    return label;
}

char* ParseAIntruction(char* line)
{
    char* symbol = malloc(sizeof(char) * MAX_LABEL_LENGTH + 1);
    if (!symbol) return NULL;

    char* c;
    int instructionTextReached = -1;
    int labelCharIndex = 0;

    for (c = line; *c != '\0'; c++)
    {
        if (instructionTextReached == 1)
        {
            // In hack assembly language, / has no other usage beside a comment.
            if (IsWhitespace(*c) == 1 || *c == '/') break;

            symbol[labelCharIndex] = *c;
            labelCharIndex++;
        }
        else if (*c == '@') instructionTextReached = 1;
    }

    symbol[labelCharIndex] = '\0';
    return symbol;
}

CInstruction* ParseCInstruction(char* line)
{
    CInstruction* instruction = malloc(sizeof(CInstruction));
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
    char buffer[4];
    int compProcessed = 0;
    int bufferIndex = 0;

    for (c = line;; c++)
    {
        if (IsWhitespace(*c) == 1) continue;
        // Buffer must contain the destination.
        else if (*c == '=')
        {
            buffer[bufferIndex] = '\0';
            strcpy_s(dest, 4, buffer);
            bufferIndex = 0;
        }
        // Buffer must contain the computation.
        else if (*c == ';')
        {
            buffer[bufferIndex] = '\0';
            strcpy_s(comp, 4, buffer);
            bufferIndex = 0;
            compProcessed = 1;
        }
        else if (*c == '\0' || *c == '/')
        {
            buffer[bufferIndex] = '\0';
            bufferIndex = 0;

            // Reached end of line, if comp has been processed it must be a jump in the buffer, otherwise it's the comp.
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