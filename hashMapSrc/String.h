#include <stdio.h>
#include <stdlib.h>

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


int indexOfChar(struct String *string, char charToFind);

int stringsAreEqual(struct String *a, struct String *b);

struct String* removeCharFromString(struct String *string, char charToRemove);

void printString(struct String *string, char *callsite);