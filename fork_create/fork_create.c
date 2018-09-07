#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	/* code */

	int childpid;
	int childCount=0,parentCount=0;
	printf("Fork starting...\n");

	childpid = fork();

	if(childpid == 0)
	{
		printf("child process is created\n");
		while(childCount<10){
			printf("child = %d\n",childCount);
			sleep(1);
			childCount++;
		}
	}
	else
	{
		printf("parent process with pid %d\n",childpid);
		while(parentCount<10){
			printf("child = %d\n",parentCount);
			sleep(1);
			parentCount++;
		}
	}

	return 0;
}