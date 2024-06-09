#include <stdio.h>
#include <execinfo.h>


void getAndPrintStack(){
	void* callstack[128];
	int i, frames = backtrace(callstack, 128);
	char** strs = backtrace_symbols(callstack, frames);
	for (i = 0; i < frames; ++i) {
		printf("%s\n", strs[i]);
	}
}

const char kNewLine = '\n';
const char kStrEnd = '\0';
char *kEndStr = "exit";

// return 1 if the strings are equivalent
int isSameString(char *a, char *b){
	int bLength = sizeof(b);
	// loop through the size of a
	for(int i = 0; i < sizeof(a); i++){
		// check if we still in bounds of a
		if(i >= sizeof(b) - 1){
			return 0;
		}
		
		// check if the char of each is the same
		if(a[i] != b[i]){
			return 0;
		}
		
		if(a[i] == kStrEnd && b[i] == kStrEnd){
			return 1;
		}
	}
	return 0;
}

// returns the length of the string 
// (aka the index of \0) return -1 if not found and mal formed string
int strLength(char *str){
	printf("size of %s is %lu ..", str, sizeof(str));
	for(int i = 0; i < sizeof(str); i++){
		if(str[i] == kStrEnd){
			return i;
		}
	}
	printf("attempting to find length of incorrect string size\n");
	return -1;
}

// return the index of a character in a string 
// -1 if not found
int indexOf(char *str, char c){
	for(int i = 0;  i < strLength(str); i++){
		if(str[i] == c){
			return i;
		}
	}
	return -1;
}

// remove all instances of char from a string
char* removeCharFromStr(char *str, char removal){
	printf("size of line in remove char helper is %ld", sizeof(str));

	int newLineIndex = indexOf(str, removal);
	while(newLineIndex >= 0){
		// shift eveything after the newline character one line back
		int strLen = strLength(str);
		for(int itr = newLineIndex; itr <= strLen; itr++){
			char newChar = itr+1 >= sizeof(str) ? '\0' : str[itr + 1];
			str[itr] = newChar;
		}
		newLineIndex = indexOf(str, removal);
	}
	return str;
}

int main(){
	char line[256];
	int i;
	while(1 == 1){
		printf("Enter a key (or enter 'exit' to end):\n" );
		if(fgets(line, sizeof(line), stdin)) {
			printf("size of line after reading in is %ld", sizeof(line));
			char *filteredLine = removeCharFromStr(line, kNewLine);
			if(isSameString(filteredLine,kEndStr) == 1){
				printf("Goodbye!\n");
				return 0;
			}
		}
	}
}
