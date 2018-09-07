#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <mqueue.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct msgbf {
    long mtype; //for message type
    char mtext[100]; //data being send
};

int main(int argc, char const *argv[])
{
    /* code */
    struct msgbf msg;
    int msgid;
    key_t key;

    /** Generate key **/
    if((key = ftok("messageQueueS.cpp",'b'))== -1)
    {
        perror("Key");
        exit(1);
    }

    /** generate message id **/
    if((msgid = msgget(key,0644 | IPC_CREAT)) == -1)
    {
        perror("msgid");
        exit(1);
    }


    printf("message id is %d\n", msgid);

    msg.mtype = 1;
    printf("Enter message here\n");

    /** read message and send message **/
    while(gets(msg.mtext),!feof(stdin)){
        if(msgsnd(msgid,&msg,sizeof(msg),0)==-1)
        {
            perror("msgsnd");
            exit(1);
        }
    }

    /** remove message **/
    if(msgctl(msgid,IPC_RMID,NULL)== -1)
    {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
