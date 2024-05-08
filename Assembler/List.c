#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

Node* GetLastNode(List* list)
{
    Node* node = list->Head;

    while (node->next != NULL)
    {
        node = node->next;
    }

    return node;
}

int AddItem(List* list, char* label, int isStringLiteral)
{
    Node *node = malloc(sizeof(Node));
    if (!node) return -1;
    node->label = label;
    node->next = NULL;
    node->isStringLiteral = isStringLiteral;

    if (list->Head == NULL) list->Head = node;
    else
    {
        Node* lastNode = GetLastNode(list);

        lastNode->next = node;
    }

    return 1;
}

char* GetItem(List *list, unsigned int index)
{
    Node *node = list->Head;

    for (unsigned int i = 0; i < index; i++)
    {
        if (node->next == NULL) return NULL;

        node = node->next;
    }

    return node->label;
}

int Any(List* list, char* label)
{
    Node* node = list->Head;

    int i = 0;

    while (node != NULL) {
        if (strcmp(node->label, label) == 0) return i;

        node = node->next;

        i++;
    }

    return -1;
}

List* NewList()
{
    List *list = malloc(sizeof(List));
    if (!list) return NULL;
    list->Head = NULL;
    return list;
}

void FreeList(List* list)
{
    Node* node = list->Head;

    int i = 0;

    while (node != NULL) {
        Node* oldNode = node;

        node = node->next;
        if (oldNode->isStringLiteral == 0 && oldNode->label != NULL)
        {
            free(oldNode->label);
        }
        free(oldNode);
    }

    free(list);
}