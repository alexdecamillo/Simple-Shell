char* commands[] = {"cd", "quit", "path"};

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
        write(1, path, len(path));
    } else if (option == 1) {
        if (len(path) != 0)
            strcat(path, ':');
        strcat(path, pathArg);
    } else if (option == 2) {
        // initialize the command pointers
        char *tempFullPath = (char *)malloc(5*sizeof(char *));
        char *pathName = (char *)malloc(5*sizeof(char *));

        while ( (pathName = strsep(&buffer, ':')) != NULL ) {
            if (strcmp(pathName, pathArg) == 0)
                // maybe output a message
            else
                strcat(tempFullPath, pathName);
        }
        path = tempFullPath;
    }
}
