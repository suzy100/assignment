#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


#define MAX_LINE 1024

int my_shell(char* buf);

int
main(int argc, char** argv)
{
    char buf[MAX_LINE];

    // batch mode
    if (argc == 2)
    {
        FILE* fp = fopen(argv[1], "rt");
        if (fp == NULL)
        {
            printf("Error : Can't open the file.\n");
            return 1;
        }

        while (feof(fp) == 0)
        {
            fgets(buf, MAX_LINE, fp);
            if(buf[strlen(buf)-1] == '\n')
                buf[strlen(buf)-1] = '\0';
            printf("%s\n", buf);
            if(strcmp(buf, "quit") == 0) return 0;
        
            my_shell(buf);
        }

        fclose(fp);
    }
    
 
    // interactive mode
    else if (argc == 1)
    {
    	while(1)
    	{           
            printf("prompt> ");

            // get input
            fgets(buf, MAX_LINE, stdin);
            buf[strlen(buf)-1] = '\0';
            if(strcmp(buf, "quit") == 0) return 0;
	        if(feof(stdin)){
                break;
            }
 	    my_shell(buf);
    	}
    }

    else
    {
        printf("Error : Input is wrong.\n");
        return 1;
    }
    return 0;
}

int
my_shell(char *buf)
{
	int n_Fork = 0;
	pid_t pid;
	pid_t pids[MAX_LINE];
	
    // quit
    if(strcmp(buf, "quit") == 0) return 0;
        
    // slice each command by ';'
    char *p = strtok(buf, ";");
    
    if (p == NULL)
    {
        printf("Error : wrong command.\n");
        return 1;
    }
        
    // command's'
    else
    {   
        // slice more
        while (p != NULL)
        {
            // fork here
            pids[n_Fork] = pid = fork();
            if (pid == 0) break;
            n_Fork++;
            p = strtok(NULL, ";");
        }
    }

    // child process
    if (pid == 0)
    {
        // parsing commands
        char *p2 = strtok(p, " ");
        char *arg[MAX_LINE];
        arg[0] = p2;

        int i = 0;
        while(p2 != NULL)
        {
            i++;
            p2 = strtok(NULL, " ");
            arg[i] = p2;
        }
            
        // exec!
        if(execvp(arg[0], arg) == -1)
        {
            printf("Error : exec failed. Maybe wrong command...\n");
            exit(0);
        }
    }

    // parent process
    else if(pid > 0)
    {
        int proc_stat;
        // wait for all children
        for(int i=0; i<n_Fork; i++)
        {
            waitpid(pids[i], &proc_stat, 0);
        }
    }

    return 0;
}
