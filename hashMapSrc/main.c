#include <stdio.h>

#include "String.h"
#include "Debug.h"

const char kNewLine = '\n';
const char kStrEnd = '\0';
const char *kEndStr = "exit";
const char *kSceneStr = "make a scene";



struct String** createCommandList()
{
    struct String* exitPrompt = createString((char *)kEndStr, sizeOfChar((char *)kEndStr));
    struct String* scenePrompt = createString((char *)kSceneStr, sizeOfChar((char *)kSceneStr));

    struct String** commands = (struct String **)malloc(sizeof(struct String *) * 2);
    commands[0] = exitPrompt;
    commands[1] = scenePrompt;
    return commands;
};


int main(){
	char line[256];

    struct String** commands = createCommandList();
	while(1 == 1){
		printf("Enter a key (or enter 'exit' to end):\n" );
		if(fgets(line, sizeof(line), stdin)) {
            struct String* lineObj = createString(line, (int)sizeof(line));
            
			struct String* filteredLine = removeCharFromString(lineObj, kNewLine);
			if(stringsAreEqual(filteredLine,commands[0]) == 1){
				printf("Goodbye!\n");
				return 0;
			} else if(stringsAreEqual(filteredLine,commands[1]) == 1) {
                printf("making a scene!\n");
            } else {
                printf("unknown command\n");
            }
		}
	}
}
