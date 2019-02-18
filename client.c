#include "headers.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main ( int argc ,char **argv)
{
	char buf[16384];
//	char *buf =	(char *)malloc(1024*sizeof(char));;
	int sockfd;
     int fd;

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(7000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(addr.sin_zero),'\0',8);

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd == -1)
	{
		perror("socket");
		exit(1);
	}
	int connetc_return = connect(sockfd,(struct sockaddr *)&addr,sizeof(struct sockaddr));
	if (connetc_return == -1)
	{
		perror("connect");
		exit(1);
	
	}
	char response[5];
//	printf("Do you want to receive the file(y/N)");
//	scanf(" %c",response);
//	if (response == "y" || response == "Y")
//	{
	char name[20];
	printf("how to sava the file\n");
	scanf(" %s",name);

	fd = open(name,O_WRONLY|O_CREAT,0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
while(1){	
	int recdata=recv(sockfd,&buf,sizeof(buf),0 );
	int len = sizeof(buf);
	if (recdata  == len )
		break;
	}
printf(" %s\n",buf);	
//	fdrintf(fd,"%s\n",buf);
		int ret =write(fd,buf,strlen(buf));		
		if (ret == -1){
			printf("an error occured\n");
	
	}
//	free(buf);
//
else{
		printf("file  copied\n");
}
	return 0;
}
