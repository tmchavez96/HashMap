#include <stdlib.h>

#include "String.h"


void printString(struct String *string, char *callsite){
    printf("Printing String from %s\n", callsite);
    printf("body = '%s'\n", string->body);
    printf("length = %d\n", string->length);
    printf("size = %d\n", string->size);
}

// assuming a string is trustworthy, find its end
int sizeOfChar(char *str){
    int i = 0;
    while(1 == 1){
        i++;
        if(str[i] == '\0'){
            return i+1;
        }
    }
    return i;
}

// static method to make the base struct
struct String* createBaseString(char *body, int size){
    struct String *newString = (struct String *)malloc(sizeof(struct String));
    // body is the only field that needs to be malloced
    newString->body = (char *)malloc(size * sizeof(char));
    // size is the same regardless of impl
    newString->size = size;
    return newString;
}

// create a string from text input
struct String* createStringFromFgets(char *body, int size){
    struct String *newString = createBaseString(body, size);
    
    int length = -1;
    for(int i = 0; i < size; i++){
        newString->body[i] = body[i];
        if(body[i] == '\0' || body[i] == 10){
            length = i;
            newString->body[i] = '\0';
        }
    }
    
    newString->length = length;
    return newString;
}

// create a string from static, or otherwise correctly null nerminated when expected string ends
struct String* createString(char *body, int size){
    struct String *newString = createBaseString(body, size);
    int length = -1;
    for(int i = 0; i < size; i++){
        newString->body[i] = body[i];
        if(body[i] == '\0'){
            length = i;
            break;
        }
    }
    if(length == -1){
        printString(newString, "error");
        printf("ERROR: created string with no termination\n");
        exit(0);
    }

    newString->length = length;
    return newString;
}

// body is the only allocated memory that needs to be free
void freeString(struct String* str){
    if(str != NULL){
        if(str->body != NULL){
            free(str->body);
        }
        free(str);
    }
}

// index of char
int indexOfChar(struct String *string, char charToFind) {
    int rv = -1;
    for(int i = 0; i < string->length; i++){
        if(string->body[i] == charToFind){
            rv = i;
            break;
        }
    }
    return rv;
}

int stringsAreEqual(struct String *a, struct String *b){
    //if the strings are not the same length, they cannot be equal
    if(a->length != b->length){
        return 0;
    }
    for(int i = 0; i <= a->length; i++){
        if(a->body[i] != b->body[i]){
            return 0;
        }
    }
    return 1;
}


struct String* removeCharFromString(struct String *string, char charToRemove) {
    int idx = indexOfChar(string, charToRemove);
    while(idx > -1){
        for(int itr = idx; itr <= string->length; itr++){
            char newChar = itr+1 >= string->size ? '\0' : string->body[itr + 1];
            string->body[itr] = newChar;
        }
        string->length--;

        idx = indexOfChar(string, charToRemove);
    }
    // return string with a modified body
    return string; 
}