#ifndef HEADERS_H
#define	HEADERS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/*int sendall(int s,char *buf,int *len)
{
	int total = 0;
	int bytesleft = *len;
	int n;

	while ( total < *len){
	n = send(s,buf+total,bytesleft,0);
	if (n == -1)
	{
		break;
	}
	total += n;
	bytesleft -= n;
}
	*len = total;//return number sent
	return n ==-1? -1:0;

}
*/
//int
int send_all(int socket, const void *buffer, size_t length, int flags)
{
    ssize_t n;
    const char *p = buffer;
    while (length > 0)
    {
        n = send(socket, p, length, flags);
        if (n <= 0)
            return -1;
        p += n;
        length -= n;
    }
    return 0;
}
#endif
