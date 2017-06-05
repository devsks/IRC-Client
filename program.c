/*
	this is a IRC client program which connects to irc.freenode.net
*/
/*	HEADERS	*/
#include <stdio.h>
#include <netdb.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

// Handler for errors
void quit(const char* msg)
{
	perror(msg);
	exit(1);
}

//struct  hostent {
  //           char    *h_name;        /* official name of host */
    //         char    **h_aliases;    /* alias list */
      //       int     h_addrtype;     /* host address type */
        //     int     h_length;       /* length of address */
          //   char    **h_addr_list;  /* list of addresses from name server */
     //};
void print(struct hostent t)
{
	printf("Name of host");
	puts(t.h_name);
	puts("alias list");
	int i = 0;
	while(t.h_aliases[i])
	{
		puts(t.h_aliases[i]);
		++i;
	}
	printf("Address type %i, host_length %i\n", t.h_addrtype,t.h_length);
	i = 0;
	printf("List of address from name server : ");
	while(t.h_addr_list[i])
	{
		puts(t.h_addr_list[i]);
		++i;
	}

}
int main( int argc, char ** argv)
{
	int port = 6667, sfd, cfd;
	char options, *usage = " irc -p [port]", *host = "162.246.59.191";
	// Intercept command-line options`
	while ((options = getopt(argc,argv,"hp:"))!= -1)
		switch(options)
		{
			case 'h':	printf("%s", usage);
						return 0;
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
	struct hostent *hostip = gethZostbyname(host);
	if (hostip == NULL)
	{
		herror(host);
		quit("gethostbyname");
	}
	print(*hostip);	
	struct sockaddr_in ser;
	socklen_t length;
	ser.sin_family = PF_INET;
	ser.sin_port = htons(port);
	//ser.sin_addr.s_addr = inetaddr ;
	return 0;
}
