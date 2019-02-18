#include "headers.h"
#include <sys/types.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>
#define PORT 7000
#define BACKLOG 10
//extern 
//extern int sendall(int s,char *buf,int len);
int pid;
int main (int argc , char **argv)
{

	int sockfd,newSockfd;
	struct sockaddr_in server;
	struct sockaddr_in client;
	socklen_t size;
	//FILE *fp;
	int fp;
	char buf[16384];
	int yes = 1;
	int len;
	int ret;
    /*establish a server connection*/
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket");
		exit(1);
	}
	/*get rid of the address already in use message*/
	fprintf(stdout,"The server is running\n");
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
	/*set the address for the connection*/
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;
	memset(&(server.sin_zero),'\0',8);

	/*bind the port number to the given address*/
	int bind_return = bind(sockfd,(struct sockaddr *)&server,sizeof(struct sockaddr));
	if (bind_return == -1)
	{
		perror("bind");
		exit(1);
	
	}
	/*listen for any incoming connections*/
	int listen_return = listen(sockfd,BACKLOG);
	if (listen_return == -1)
//	fprintf(stdout,"[+]listening\n");
	{
		perror("listen");
		exit(1);
	
	}
	/*loop forever*/
	for ( ; ;)
	{
		size = sizeof(struct sockaddr_in);
		/*accept a connection from the listening port*/
		newSockfd = accept(sockfd,(struct sockaddr *)&client,&size);
		if (newSockfd == -1)
		{
			perror("aceept");
			exit(1);
			//continue;
		}
		pid = fork();
		if (pid <0){
				perror("fork");
			}
		if (pid == 0){
			close(sockfd);
		char name[20];
		printf("enter the name of the file to copy\n");
		scanf(" %s",name);

		fp = open ( name,O_RDONLY);
		//ssize_t sendfile(int out_fd,int in_fd,off_t *offset,size_t count);
		ssize_t returned;
		//returned = sendfile(sockfd,fp,0,sizeof(buf));
		
		//while((
		int re;
	    while (( re=read(fp,buf,sizeof(buf)-1))>0){
			buf[re] =0x00;
	    	printf("%s\n",buf);
			}
	//		send_all(newSockfd,buf,sizeof(buf),0);
		 
		 len = sizeof(buf);
		//strncmp(name,"*.mp4");
		 ret=send(newSockfd,buf,sizeof(buf),0);
		//ret = write(newSockfd,buf,sizeof(buf));
		if (ret == len)
		{
		    sleep(2);
			printf(" %s\n",buf);
			printf("file copied successfully\n");
			exit(0);
		}
	}
		//fclose(fp);
//		free(buf);
 if (pid  > 0){ 

	close(newSockfd);
//		close(sockfd);
	}
}
//close(newSockfd);
//close(sockfd);
	return 0;
}
