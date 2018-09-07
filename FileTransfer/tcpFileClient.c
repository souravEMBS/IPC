#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>



void error(const char* msg) // error prints
{
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[])
{
	/* code */

	int socketFd,portno,n;
	struct sockaddr_in serv_addr; //socket address
	struct hostent* server; // host
	char buffer[256];

	if(argc < 3){
		fprintf(stderr,"usage %s host port",argv[0]);
		exit(0);
	}
	portno  = atoi(argv[2]);

	socketFd = socket(AF_INET, SOCK_STREAM,0); // create cocket
	if(socketFd == -1)
		error("socket open error: ");

	server = gethostbyname(argv[1]); // returns hostent for a given host name
	if(server == NULL)
	{
		fprintf(stderr,"no host present by name %s ",argv[1]);
		exit(0);
	}

	bzero((char *)&serv_addr,sizeof(serv_addr));//fill with zero
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(portno);

	if(connect(socketFd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)// connect to the socket
		error("connection error... ");


	// while(1)
	// {
	bzero(buffer,sizeof(buffer));
	
	FILE *f;
	int words = 0;
	char c;
	f = fopen("FT_Sample.txt","r");
	if(f ==  NULL)
		error("File cannot be read");
	while((c = getc(f)) != EOF)//check until end of file
	{
		fscanf(f,"%s",buffer);
		if(isspace(c) || c == '\t')//isspace checks for space
		words++;
	}

	write(socketFd,&words,sizeof(int));
	rewind(f);//file pointer to the start

	char ch;
	while (ch !=  EOF)
	{
		fscanf(f,"%s",buffer);
		write(socketFd,buffer,255);
		ch = fgetc(f);
	}

	printf("File successfully sent\n");
	close(socketFd);
	return 0;
}