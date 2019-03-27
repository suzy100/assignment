#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


#define MAX_LINE 1024

int
main(void)
{
    char *buf[MAX_LINE];
    char *arg[MAX_LINE];
    int proc_stat;
    char *p;
    char *input[MAX_LINE];


    printf("prompt> ");

    while(1)
    {   
        int n_Fork = 0;
        int r_Process = 0;
        memset(buf, 0x00, MAX_LINE);
        memset(input, 0x00, MAX_LINE);
        memset(arg, 0x00, MAX_LINE);

        fgets(*buf, MAX_LINE-1, stdin);
        if(strcmp(*buf, "quit") == 0) break;
        
        buf[strlen(*buf)-1] = 0;
        
        p = strtok(*buf, ";");
        input[n_Fork] = p;

        while (p != NULL)
        {
            n_Fork++;
            p = strtok(NULL, ";");
            input[n_Fork] = p;
        }

        pid_t pid[n_Fork];


        while(r_Process < n_Fork)
        {
            p = strtok(input[r_Process], " ");
            p[strlen(p)-1] = '\0';
            arg[0] = p;
            int i = 0;
            while(p != NULL)
            {
                i++;
                arg[i] = input[r_Process];
            }

            pid[r_Process] = fork();

            if(pid[r_Process] == 0)
            {
                if(execvp(arg[0], arg) == -1)
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

