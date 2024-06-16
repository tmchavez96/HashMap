#include <stdio.h>
#include <stdlib.h>
#include "String.h"

// this prevents compile issues when string is imported into multiple other implementations / headers.
// Otherwise, it will compile as being included multiple times.
#ifndef HASHMAP_H
#define HASMAP_H

struct KeyValue {
	struct String *string;
	struct String *value;
} KeyValue;


struct Hashmap {
	struct String *name;
	struct KeyValue **map;
	// length of the array
	int mapLegnth;
} Hashmap;

// creates an empty map
struct Hashmap* createHashMap(char *name);

void printMap(struct Hashmap *map);

#endif;