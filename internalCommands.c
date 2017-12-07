char* commands[] = {"cd", "quit", "path"};

int checkInternalCommands(char* command) {
    for (int i = 0; i < (sizeof(commands)/sizeof(char*)); i++) {
        if (strcmp(commands[i], command) == 0) {
            return 1;
        }
    }
    return 0;
}

void cd(char* directory) {
    chdir(directory);
    // add error handling
}

void quit() {
    exit(1);
}

void path(char* path, int option, char* pathArg) {
    if (!option) {
        // write path to screen
        //write(1, path, strlen(path));
        printf("%s\n", path);
    } else if (option == 1) {
        if (strlen(path) != 0)
            strcat(path, ":");
        strcat(path, pathArg);
    } else if (option == 2) {
        // initialize the command pointers
        char *tempFullPath = (char *)malloc(100*sizeof(char *));
        char *pathName = (char *)malloc(10*sizeof(char *));
        char *buffer = (char *)malloc(100*sizeof(char *));
        strcpy(buffer, path);

        while ( (pathName = strsep(&buffer, ":")) != NULL ) {
            if (strcmp(pathName, pathArg)) {
                if (strlen(tempFullPath) != 0)
                    strcat(tempFullPath, ":");
                strcat(tempFullPath, pathName);
            } else {
                printf("%s%s\n", "removed: ", pathName);
            }
        }
        strcpy(path, tempFullPath);
    }
}
