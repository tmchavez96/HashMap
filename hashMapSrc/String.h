#include <stdio.h>
#include <stdlib.h>

// this prevents compile issues when string is imported into multiple other implementations / headers.
// Otherwise, it will compile as being included multiple times.
#ifndef STRING_H
#define STRING_H

struct String {
	char *body;
	int size;
	int length;
    int isValid;
} String;


int sizeOfChar(char *str);

// the callsite needs to have 
struct String* createString(char *body, int size);

// unlike a normal string, we will need to assume this strings ends with lf
struct String* createStringFromFgets(char *body, int size);

// dealloc
void freeString(struct String* str);

int indexOfChar(struct String *string, char charToFind);

int stringsAreEqual(struct String *a, struct String *b);

int stringIsEqualToCharArray(struct String *s, char *c);

struct String* removeCharFromString(struct String *string, char charToRemove);

void printString(struct String *string, char *callsite);

#endif