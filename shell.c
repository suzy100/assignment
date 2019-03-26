#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


#define MAX_LINE 256

int
main(void)
{
    char *buf[MAX_LINE];
    char *argv[MAX_LINE];
    char command[32];
    int proc_stat;
    int n_Fork = 0;
    int r_Process = 0;
    char *p1;
    char *p2;


    printf("prompt> ");

    while(1)
    {
        memset(buf, 0, MAX_LINE);
        fgets(*buf, MAX_LINE-1, stdin);
        if(strcmp(*buf, "quit") == 0) break;
        
        buf[strlen(*buf)-1] = 0;

        p1 = strtok(*buf, ";");

        while (p1 != NULL)
        {
            n_Fork++;
            p1 = strtok(NULL, ";");
        }

        pid_t pid[n_Fork];


        while(r_Process < n_Fork)
        {
            p2 = strtok(*buf, ";");
            p1 = strtok(p2, " ");
            p2[strlen(p2)-1] = 0;
            if (p1 != NULL)
            {
                strcpy(command, p1);
                strcpy(*argv, p2);
            }

            pid[r_Process] = fork();

            if(pid[r_Process] == 0)
            {
                if(execvp(command, argv) == -1)
                {
                    printf("Failed to exec.\n");
                    exit(0);
                }
            }

            if(pid[r_Process] > 0)
            {
                wait(&proc_stat);
            }

            r_Process++;
        }
    }
    return 0;
}

