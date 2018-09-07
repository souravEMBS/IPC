#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define SHSIZE 100

int main(int argc, char const *argv[])
{
	/* code */
	int shrMemId;
	key_t key;
	char *shm;
	char *s;

	key = 9876;

	if((shrMemId = shmget(key, SHSIZE, 0666)) == -1)
	{
		perror("shmget:");
		exit(1);
	}

	shm = shmat(shrMemId,NULL,0);
	if(shm == (char*)-1)
	{
		perror("shmat:");
		exit(1);
	}

	memcpy(shm,"Hello shared memory", 20);

	s = shm;
	s += 19;

	s += 0;

	while(*shm != '*') // keep looping until client writes *
		sleep(1);
	
	return 0;
}