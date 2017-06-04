/*
	this is a IRC client program which connects to irc.freenode.net
*/
#include <stdio.h>
#include <netdb.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
void quit(const char* msg)
{
	perror(msg);
	exit(1);
}
int main( int argc, char ** argv)
{
	int port = 6667, sfd, cfd;
	char options, *usage = " irc -p [port]", *host = "irc.freenode.net";
	while ((options = getopt(argc,argv,"hp:"))!= -1)
		switch(options)
		{
			case 'h':	printf("%s", usage);
						break;
			case 'p':	port = atoi(optarg);
						break;
			default: quit(usage);
		}
	if (port < 0 || port > SHRT_MAX)
	{
		quit("invalid port number");	
	}
	if ( (sfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)	
	{
		quit("can't create socket ");
	}
	struct hostent *hostip = gethostbyname("host");
	if (hostip == NULL)
	{
		herror(host);
		quit("gethostbyname");
	}
	struct sockaddr_in ser;
	socklen_t length;
	ser.sin_family = PF_INET;
	ser.sin_port = htons(port);
//	ser.sin_addr.s_addr ;
	return 0;
}
