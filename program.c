/*===---- devChat is a IRC client program ----------------------------===
 *
 * Copyright (c) 2017 Santosh Kumar Shaw
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 */

#include <stdio.h>
#include <netdb.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

/*
	quit() takes a string as argument and print it along
	along with the error message. 
*/
void quit(const char *msg)
{
	perror(msg);
	exit(1);
}
/*
	exitMessage() 
*/
void exitMessage(void)
{
	printf("devChat has been closed\n\n");
}
//struct  hostent {
  //           char    *h_name;        /* official name of host */
    //         char    **h_aliases;    /* alias list */
      //       int     h_addrtype;     /* host address type */
        //     int     h_length;       /* length of address */
          //   char    **h_addr_list;  /* list of addresses from name server */
     //};
void print(struct hostent *t)
{
	printf("Official name is: %s\n", t->h_name);
    printf("    IP addresses: ");
    struct in_addr **addr_list = (struct in_addr **)t->h_addr_list;
    for(int i = 0; addr_list[i] != NULL; ++i)
 	{
        puts(inet_ntoa(*addr_list[i]));
    }
    printf("\n");

}
int main( int argc, char ** argv)
{
	// exitMessage will be called when the program terminates
	atexit(exitMessage);

	int port = 6667, sfd, cfd;
	char options, *usage = " irc -p [port]", *host = "94.125.182.252";
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
	struct hostent *hostip = gethostbyname("irc.freenode.net");
	if (hostip == NULL)
	{
		herror(host);
		quit("gethostbyname");
	}
	print(hostip);	
	struct sockaddr_in ser;
	socklen_t length;
	ser.sin_family = PF_INET;
	ser.sin_port = htons(port);
	ser.sin_addr.s_addr = inet_addr(host);
	if(connect(sfd,(struct sockaddr*)&ser, sizeof(ser)) == -1)
	{
		quit(NULL);
	}
	else
		printf("YAY we are connec to the server");
	char buffer[128];
	while(read(sfd,&buffer,128)!=-1)
	{
		puts(buffer);
	}
	close(sfd);
	return 0;
}
