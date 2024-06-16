#include <stdlib.h>

#include "HashMap.h"

const int kInitialMapLength = 20;

// creates an empty map
struct Hashmap* createHashMap(char *name){
    struct Hashmap *newHashmap = (struct Hashmap *)malloc(sizeof(struct Hashmap));
    struct String *mapName = createString(name, sizeOfChar(name));
    struct KeyValue **map = (struct KeyValue**)malloc(sizeof(struct KeyValue *) * kInitialMapLength);

    newHashmap->map = map;
    newHashmap->mapLegnth = kInitialMapLength;
    newHashmap->name = name;
    return newHashmap;
}


void printMap(struct Hashmap *map){
    printf("Map name %d\n", map->name);
    // find non-null key values?
}