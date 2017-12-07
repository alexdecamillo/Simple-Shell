#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/wait.h>
#include "internalCommands.c"

char *PATH;

void runCommand(char *c[], int len);

int main(int argc, char *argv[]){

    int commandLength;
    PATH = (char *)malloc(sizeof(char) * 100);
    //strcat(PATH, "test/with/stuff:blah/blah");
    char prompt[] = "Simple Shell$ ";
    char *input = malloc(50), *token, *delim=" ", *buffer;

    // initialize the command pointers
    char **command = (char**)malloc(2*sizeof(char*));
    for(int i = 0; i < 2; i++)
        command[i] = (char *)malloc(50*sizeof(char *));

    // the main loop for the shell
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
//  appropiate command
void runCommand(char *argv[], int argc){
    // check if command is an interal command first
    // otherwise, check if it is in the path

    if (checkInternalCommands(argv[0])) {
        if (!strcmp(argv[0], "quit")) {
            quit();
        } else if(!strcmp(argv[0], "cd")) {
            if (argc >= 2) {
                cd(argv[1]);
            } else {
                printf("You must specify a directory location\n");
            }
        } else if (!strcmp(argv[0], "path")) {
            if (argc == 1) {
                path(PATH, 0, NULL);
            } else if (argc == 3) {
                if (!strcmp(argv[1], "+")) {
                    path(PATH, 1, argv[2]);
                } else if(!strcmp(argv[1], "-")) {
                    path(PATH, 2, argv[2]);
                }
            } else {
                printf("%s%d%s\n", "path: ERROR: no command for 'path' takes ", argc, " arguments");
            }
        }
    } else {
        // check if command is in a path directory

        // fork
        pid_t pid = fork();

        // check child or parent
        if(pid < 0) {
            // error
            perror(argv[0]);
        } else if(pid == 0) {
            // child
            char *command = malloc(sizeof(char* ) * 20);

            // initialize the command pointers
            char *pathName = (char *)malloc(10*sizeof(char *));
            char *buffer = (char *)malloc(100*sizeof(char *));
            char *commandName = (char *)malloc(100*sizeof(char *));
            strcpy(buffer, PATH);
            strcpy(commandName, argv[0]);

            while ( (pathName = strsep(&buffer, ":")) != NULL ) {
                // construct argument
                strcpy(command, pathName);
                strcat(command, "/");
                strcat(command, commandName);
                argv[0] = command;
                argv[argc] = NULL;

                execve(argv[0], argv, NULL);
            }

            printf("Error: could not find command '%s' in the path\n", commandName);
            exit(0);
        } else {
            // parent
            int status;
            waitpid(pid, &status, 0);
        }
    }

}
