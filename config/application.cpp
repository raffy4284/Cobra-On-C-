/* courtesy of http://www.linuxhowtos.org/C_C++/socket.htm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include "routes.h"
#include "utilities.h"
#include <vector>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int listen_sockfd, connect_sockfd, portno;
    socklen_t client_len;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
	pid_t child;
	

    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sockfd < 0) 
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(listen_sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0) 
            error("ERROR on binding");

	while(1){
	    listen(listen_sockfd,5);
     	client_len = sizeof(cli_addr);
	

	    connect_sockfd = accept(listen_sockfd,(struct sockaddr *) &cli_addr,&client_len);
		child = fork();

		//parent
		if(child > 0)
			close(connect_sockfd);
		
		//child-serve the request!
		else if ( child == 0){
			close(listen_sockfd);	
			bzero(buffer,256);
			n = read(connect_sockfd,buffer,255);
			if (n < 0) error("ERROR reading from socket");

			//PROTECT!
			//printf("child_ID: %d\n\nHere is the message: \n\n%s\n",getpid(),buffer);
			string request[2] = ParseRequest(buffer);

			//n = write(connect_sockfd,"<div style='background-color:red;float:right'>I got your message</div>",49);
			if (route.find(request) == route.end()){
				//spit out 404
			}
			else{
				route[request];
			}
			if (n < 0) error("ERROR writing to socket");
			close(connect_sockfd);
			//UNPROTECT!

				
			exit(EXIT_SUCCESS);
		}
		else	 
     	     error("ERROR on accept");
	}
	close(listen_sockfd); 
}
