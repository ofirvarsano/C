#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define PRMTSIZ 255
#define MAXARGS 63

int main(void)
{
	int i;
    while(1)
    {
        char input[PRMTSIZ + 1] = { 0x0 };
        char *ptr = input;
        char *args[MAXARGS + 1] = { NULL };
		
		printf("%s prompt: ", getuid() == 0 ? "#" : "$");
        fgets(input, PRMTSIZ, stdin);

        for (i = 0; i < sizeof(args) && *ptr; ptr++)
        {
            if (*ptr == ' ')
            {
            	continue;
            }
            if (*ptr == '\n')
            {
            	break;
            }
            for (args[i++] = ptr; *ptr && *ptr != ' ' && *ptr != '\n'; ptr++);
            *ptr = '\0';
        }

        if (fork() == 0)
        {
        	exit(execvp(args[0], args));
        }
        wait(NULL);
    }
}



