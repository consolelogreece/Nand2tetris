#include "List.h"

#define HASHSIZE 1000

typedef struct KeyValuePair KeyValuePairs[HASHSIZE];

typedef struct KeyValuePair {
	List* Keys;
	List* Values;
} KeyValuePair;

typedef struct HashMap
{
	struct KeyValuePair KVP[HASHSIZE];
} HashMap;

HashMap* NewHashMap();

int SetItem(HashMap* map, char* key, char* value, int isKeyStringLiteral, int isValueStringLiteral);

char* GetValue(HashMap* map, char* key);

void FreeHashMap(HashMap* map);