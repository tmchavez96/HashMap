#include <stdio.h>
#include <stdlib.h>

#include "String.h"
#include "Command.h"
#include "Debug.h"


const char kNewLine = '\n';
const int kCommandListSize = 20;

// struct used more or less used as a global to pass data from CLI to handler.
struct HanlderData {
    struct Command** commands;
    struct String* lastInput;
} HanlderData;

struct HanlderData *mainHandlerData;

void clearScreen() {
    printf("\033[H\033[J");
}

// helper method to hanlder reading input from the OS level
struct String* getInput(char *prompt){
    char line[256];
    printf("%s\n", prompt);
    if(fgets(line, sizeof(line), stdin)) {
        struct String* lineObj = createString(line, (int)sizeof(line));
		lineObj = removeCharFromString(lineObj, kNewLine);
        clearScreen();
        return lineObj;
    } else {
        printf("unexpected error getting user input, aborting.\n");
	    exit(0);
    }
}

int getBooleanInput(char *prompt){
    char line[256];
    printf("%s\n", prompt);
    printf("(y/n) \n");
    
    if(fgets(line, sizeof(line), stdin)) {
        struct String* lineObj = createString(line, (int)sizeof(line));
		lineObj = removeCharFromString(lineObj, kNewLine);
        clearScreen();
        
        if(stringIsEqualToCharArray(lineObj, "y") == 1){
            return 1;
        } else if (stringIsEqualToCharArray(lineObj, "n") == 1) {
            return 0;
        } 
        return getBooleanInput(prompt);

    } else {
        printf("Unexpected error getting user input, aborting.\n");
	    exit(0);
        return -1;
    }

}

void handleScene(void* data){
    printf("making a scene!\n");
}

void handleExit(void* data){
    printf("Goodbye!\n");
	exit(0);
}

void handleHashMap(){
    if(getBooleanInput("Create an a new array?") == 1){
        printf("Ceating a new array!\n");
    } else {
        if(getBooleanInput("See another array?") == 1){
            printf("No array's in memory..\n");
        } else {
            printf("Loop Ending..\n");
        }
    }
}


void handleHelp(void *data){
    struct Command** commands = mainHandlerData->commands;
    for(int i = 0; i < kCommandListSize; i++){
        struct Command* curCommand = commands[i];
        if(curCommand != NULL){
            printf("\033[33mCommand: '%s' \033[0m\n", curCommand->commandName->body);
            printf("%s\n \n", curCommand->helpMessage->body);
        }
    }
}

struct Command** createCommandList()
{
    // unfortunatelty, we can't pass a nameless function in c. Define the hanler's here in main.
    struct Command *exitCommand = createCommand("exit", "type 'exit' to end the program.", handleExit);
    struct Command *sceneCommand = createCommand("make a scene", "make a new scene to start :) ", handleScene);
    struct Command *helpCommand = createCommand("help", "use 'help' to see the list of available commands", handleHelp);
    struct Command *arrayCommand = createCommand("hashmap", "hashmap CLI to create, edit, and view a hashmap data structure", handleHashMap);

    struct Command** commands = (struct Command **)malloc(sizeof(struct Command *) * kCommandListSize);
    commands[0] = exitCommand;
    commands[1] = sceneCommand;
    commands[2] = helpCommand;
    commands[3] = arrayCommand;
    return commands;
};

void mainUserLoop(){
    struct Command** commands = createCommandList();
    mainHandlerData = (struct HanlderData *)malloc(sizeof(struct HanlderData));
    mainHandlerData->commands = commands;

	while(1 == 1){
        struct String *filteredLine = getInput("Enter a key (or enter 'exit' to end):");
        mainHandlerData->lastInput = filteredLine;

        int foundCommand = 0;
        for(int i = 0; i < kCommandListSize; i++){
            struct Command* currentCommand = commands[i];
            if(currentCommand != NULL && stringsAreEqual(filteredLine, currentCommand->commandName) == 1 ){
                foundCommand = 1;
                currentCommand->action(commands);
                break;
            }
        }
        if(foundCommand == 0){
            printf("\033[36m'%s'\033[31m - Command not found\033[0m\n",filteredLine->body);
        }
	}
}

int main(){
    mainUserLoop();
}
