//============================================================================
// Name        : PPTSocket.cpp
// Author      : Marco Ordonez
// Version     :
// Copyright   : 
// Description : Power Point socket program to listen Iphone requests
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "net/LocalIpAddress.hpp"
#include "loffice/doccontrol/ppt/PPTController.hpp"



using namespace std;


#define BACKLOG 10


void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}


int main(int argc, char *argv[])
{


	PPTController * loffice_pptcontroller;

	loffice_pptcontroller->connect();
	loffice_pptcontroller->openDoc();
	loffice_pptcontroller->accessDoc();



	LocalIpAddress * ip_address;

	struct sockaddr_storage their_addr;
	struct addrinfo hints, *servinfo;
	int status;
	int sockfd, new_fd;
	struct sigaction sa;
	socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	cout << "Escuchando en  :  " << ip_address->getIp() << endl;

	if ((status = getaddrinfo(ip_address->getIp().c_str(), "9192", &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}

	sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

	int yes=1;
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)
	{
	    perror("setsockopt");
	    return 1;
	}



	if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		close(sockfd);
		perror("server: bind");
	}

	if (servinfo == NULL)
	{
		fprintf(stderr, "server: failed to bind\n");
		return 2;
	}

	freeaddrinfo(servinfo); // all done with this structure


	if (listen(sockfd, BACKLOG) == -1)
	{
		perror("listen");
		return 1;
	}


	sa.sa_handler = sigchld_handler; // reap all dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		return 1;
	}



	cout << sockfd << endl;
	 while(1)
	 {
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family,
			get_in_addr((struct sockaddr *)&their_addr),
			s, sizeof s);

		cout << "ok" << endl;
		printf("server: got connection from %s\n", s);

	}

	return 0;
}
