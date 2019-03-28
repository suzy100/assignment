#include <stdio.h>
#include <unistd.h>
#include <string.h>

void main(int argc, char *argv[]){

        /* argv[] = {name of file executed, "ls", option/path...}

           To get argv in execv, make argv elements replace to advance index
         one by one.*/
        for (int i = 0; i<argc; i++){
                argv[i] = argv[i+1];
        }

        /* argv = {"ls", option/path...}

           Using strcmp, if there is "ls" in argv[0], execv().
           If not, it's error. */
        if (!strcmp(argv[0], "ls")) //if argv[0] and "ls" is identical,
        {
                execv("/bin/ls", argv); //get argv and execute file in "/bin/ls".
        }
        //if different
        else printf("Error! (Maybe wrong command)"); //wrong command or error occured when change argv.
        
        return;

}
