#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void main()
{
        char *line = NULL;
        char *copy = NULL;
        char *word;
        char *temp;
        size_t size = 0;
        ssize_t ret;
        int i = 0;

        if ((ret = getline(&line, &size, stdin)) != -1){

            char *newline = strchr(line, '\n');
            if (newline) *newline = 0;

            strcpy(copy, line);
            
            char *command = strtok(copy, " ");
            while(word != NULL) {
                i++;
                word = strtok(NULL, " ");
            }

            char **arg = (char **)malloc(sizeof(char*) * (i+2));
            arg[i+1] = NULL;

            arg[0] = command;

            while (temp != NULL) {
                temp = strtok(NULL, " ");
                arg[i] = temp;
                i++;
            }

            if(!strcmp(command, "ls")) {
                execv("/bin/ls", arg);
            }
            else printf("Wrong command!");
        }
        else printf("Error!");
}
