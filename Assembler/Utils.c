#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "Utils.h"

char* PadLeft(char* s, char p, int len)
{
    char* retStr = malloc(sizeof(char) * len + 1);
    if (!retStr) return NULL;

    size_t n = strlen(s);

    if (n >= len) return s;

    for (size_t i = 0; i < len - n; i++)
    {
        retStr[i] = p;
    }

    for (size_t i = len - n; i < len; i++)
    {
        retStr[i] = s[i - (len - n)];
    }

    retStr[len] = '\0';

    return retStr;
}

int IsWhitespace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
    {
        return 1;
    }

    return -1;
}

int ContainsOnlyNumbers(char* s)
{
    char* c;

    for (c = s; *c != '\0'; c++)
    {
        if (!isdigit(*c)) return -1;
    }

    return 1;
}