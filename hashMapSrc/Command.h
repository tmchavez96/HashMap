#include <stdio.h>
#include <stdlib.h>
#include "String.h"

#ifndef COMMAND_H
#define COMMAND_H

struct Command {
	struct String *commandName;
    struct String *helpMessage;
    void (*action)(void* data);
} Command;

// init
struct Command *createCommand(char * commandName,char * helpMessage, void (*actionHanlder)(void* data) );

// free
void freeCommand(struct Command *command);


#endif