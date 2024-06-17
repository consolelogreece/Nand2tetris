typedef struct CInstruction {
    char* dest;
    char* comp;
    char* jump;
} CInstruction;

int DetermineLineType(char* line);

char* ParseLabel(char* line);

char* ParseAIntruction(char* line);

CInstruction* ParseCInstruction(char* line);