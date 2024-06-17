typedef struct Node {
    char* label;
    struct Node* next;
    int isStringLiteral;
} Node;

typedef struct List {
    Node* Head;
} List;

int AddItem(List* list, char* label, int isStringLiteral);

int Any(List* list, char* label);

char* GetItem(List* list, unsigned int index);

List* NewList();

void FreeList(List* list);