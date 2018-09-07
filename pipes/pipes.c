#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	/* code */

	pid_t pid;
	int pipes[2];
	int pipeRet;
	char buf[1024];

	if((pipeRet =  pipe(pipes))== -1)
	{
		perror("no pipe created:");
		exit(1);
	}


	pid =  fork();

	if(pid == 0)
		/*child process opeation*/
	{
		write(pipes[1],"child sending to parent",24);
	}
	else
		/*parent process*/
	{
		read(pipes[0],buf,30);
		printf("buff: %s\n",buf);

	}

	return 0;
}