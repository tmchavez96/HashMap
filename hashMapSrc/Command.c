#include "Command.h"

struct Command *createCommand(
    char *commandName,
    char * helpMessage,
    void (*actionHanlder)(void* data)
){
    // struct String *newString = (struct String *)malloc(sizeof(struct String));
    struct Command *newCommand = (struct Command *)malloc(sizeof(struct Command));
    struct String* commandNameStr = createString(commandName, sizeOfChar(commandName));
    struct String* helpMessageStr = createString(helpMessage, sizeOfChar(helpMessage));

    newCommand->commandName = commandNameStr;
    newCommand->action = actionHanlder;
    newCommand->helpMessage = helpMessageStr;
    return newCommand;
}

void freeCommand(struct Command *command){
    if(command != NULL){
        if(command->commandName != NULL){
            freeString(command->commandName);
        }
        free(command);
    }
}