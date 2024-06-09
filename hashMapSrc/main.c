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

void handleScene(void* data){
    printf("making a scene!\n");
}

void handleExit(void* data){
    printf("Goodbye!\n");
	exit(0);
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

    struct Command** commands = (struct Command **)malloc(sizeof(struct Command *) * kCommandListSize);
    commands[0] = exitCommand;
    commands[1] = sceneCommand;
    commands[2] = helpCommand;
    return commands;
};

void mainUserLoop(){
    char line[256];
    struct Command** commands = createCommandList();
    mainHandlerData = (struct HanlderData *)malloc(sizeof(struct HanlderData));
    mainHandlerData->commands = commands;

	while(1 == 1){

		printf("Enter a key (or enter 'exit' to end):\n" );
		if(fgets(line, sizeof(line), stdin)) {
            clearScreen();
            struct String* lineObj = createString(line, (int)sizeof(line));
			struct String* filteredLine = removeCharFromString(lineObj, kNewLine);
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
}

int main(){
    mainUserLoop();
}
