#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


void error(const char* msg) // error prints
{
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[])
{
	/* code */

	int sockFd,newSockFd,portno,n;
	struct sockaddr_in serv_addr,client_addr; //socket address for server and client
	socklen_t client_len; //client socket length
	struct hostent* server; // host
	char buffer[256];

	if(argc < 2){
		fprintf(stderr,"please provide the port number\n");
		exit(1);
	}
	
	sockFd = socket(AF_INET,SOCK_STREAM,0); //create socket
	if(sockFd < 0)
		error("ERROR opening socket");

	bzero((char *)&serv_addr,sizeof(serv_addr));

	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	//bind socket
	if(bind(sockFd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
		error("Bind failed");

	//listen

	if(listen(sockFd,5) < 0)
		error("listen failed");

	client_len = sizeof(client_addr);


	//accept connection
	newSockFd = accept(sockFd,(struct sockaddr *)&client_addr,&client_len);

	if(newSockFd < 0)
		error("accept error");

	FILE* fp;
	int ch =0;
	fp = fopen("FT_Recv.txt","a");
	int words = 0;

	read(newSockFd,&words,sizeof(int));

	while(ch != words)
	{
		read(newSockFd,&buffer,255);
		fprintf(fp, "%s ", buffer);
		ch++;
	}
	printf("File recived and saved\n");

	close(newSockFd);
	close(sockFd);

	return 0;
}