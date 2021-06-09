#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

static int g_var = 0;

int main()
{
	int i, j, l_var = 0;
	pid_t n;

	n = fork();
	if( n < 0) /* fork() failed */
	{
		printf("Error fork create fail\n");
	}
	else if(n > 0) /* parent */
	{
		for( i = 0; i < 30; ++i)
		{
			++g_var;
			printf("g_var %d\n", g_var);
			++l_var;
			printf("l_var %d\n", l_var);
			sleep(1);
		}
	}
	else /* child */
	{
		for( j = 0; j < 30; ++j)
		{
			--g_var;
			printf("g_var %d\n", g_var);
			--l_var;
			printf("l_var %d\n", l_var);
			sleep(1);
		}
	}

	return 0;
}
