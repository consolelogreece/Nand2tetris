#include <stdlib.h>
#include "HashMap.h"

HashMap* NewHashMap()
{
	HashMap *map = malloc(sizeof(HashMap) + (sizeof(KeyValuePair) * HASHSIZE));
	if (!map) return NULL;

	for (int i = 0; i < HASHSIZE; i++)
	{
		map->KVP[i].Keys = NewList();
		map->KVP[i].Values = NewList();
	}

	return map;
}

// Pinched from https://stackoverflow.com/questions/7666509/hash-function-for-string - thanks! :)
int GenerateHash(char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c;

	return hash % HASHSIZE;
}

int SetItem(HashMap *map, char* key, char* value, int isKeyStringLiteral, int isValueStringLiteral)
{
	int hash = GenerateHash(key);

	int location = Any(map->KVP[hash].Keys, key);

	// key not yet in hashmap, so add.
	if (location = -1)
	{
		AddItem(map->KVP[hash].Keys, key, isKeyStringLiteral);
		AddItem(map->KVP[hash].Values, value, isValueStringLiteral);

		return 1;
	}

	// item exists in hashmap so do nothing. normally you would override the existing value in this case,
	// but we'll never need to do this in this assembler.
	return -1;
}

char* GetValue(HashMap* map, char* key)
{
	int hash = GenerateHash(key);

	int location = Any(map->KVP[hash].Keys, key);

	if (location != -1)
	{
		return GetItem(map->KVP[hash].Values, location);
	}
	else
	{
		return NULL;
	}
}


void FreeHashMap(HashMap* map)
{

	for (int i = 0; i < HASHSIZE; i++)
	{
		FreeList(map->KVP[i].Keys);
		FreeList(map->KVP[i].Values);
	}

	free(map);	
}