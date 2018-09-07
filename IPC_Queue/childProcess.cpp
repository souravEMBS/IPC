#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


int main(int argc, char const *argv[])
{
    /* code */
    pid_t pid;
    int a = 47, b= 11;
    int c =0;
    int myPipe[2];
    pipe(myPipe);
    char *const paramList[] = {"bin/ls","-l","/home/sourav/cis505_lecture",NULL};
    if((pid=fork()) == -1)
        perror("fork fail: ");
    else if (pid == 0){
        close(myPipe[0]);
        c = a+b;
        write(myPipe[1],&c,sizeof(c));
        fprintf(stdout,"entering child process\n");
        execv("/bin/ls",paramList);
        perror("execv error");
        //errorHandle(1);
    }
    else{
        int status;
        close(myPipe[1]);
        read(myPipe[0],&c,sizeof(c));
        printf("a = %d, b= %d, c= %d\n",a,b,c);
        wait(&status);
        printf("Child status = (%d)\n", status);
        exit(status);
    }

    printf("a = %d, b= %d, c= %d\n",a,b,c);
    return 0;
}
