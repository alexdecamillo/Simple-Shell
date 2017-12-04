#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "internalCommands.c"

int *PATH;

void runCommand(char *c[], int len);

int main(int argc, char *argv[]){

    int commandLength;
    fd = malloc(sizeof(int));
    char prompt[] = "Minix Console$ ";
    char *input = malloc(50), *token, *delim=" ", *buffer;

    // initialize the command pointers
    char **command = (char**)malloc(2*sizeof(char*));
    for(int i = 0; i < 2; i++)
        command[i] = (char *)malloc(50*sizeof(char *));

    // the main loop for the minix console
    while (1) {
        // prompt and get input
        printf("%s", prompt);
        fgets(input, 50, stdin);

        // use buffer string and reset commandLength
        buffer = strdup(input);
        commandLength = 0;

        // parse the input by ' ' into an array
        while ( (token = strsep(&buffer, delim)) != NULL ) {
            if (token[strlen(token)-1] == '\n')
                token[strlen(token)-1] = '\0';
            command[commandLength] = token;
            commandLength++;
        }

        runCommand(command, commandLength);
    }

}

// takes the command array and the length of the array and calls the
//  appropiate module from modules.c
void runCommand(char *c[], int len){
    // try to run in internal commands
    cd(c);
    // then try to run in path commands
    // else print error


}
