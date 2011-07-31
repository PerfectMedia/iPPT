/*Copyright (c) 2011 PerfectMedia SAC

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/
//============================================================================
// Name        : iPPT.cpp
// Author      : Marco Ordonez
// Version     : 1.0
// Copyright   : PerfectMedia SAC 2011
// Description : Power Point socket program to listen Iphone requests
//============================================================================

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string.h>

#include "net/LocalIpAddress.hpp"
#include "net/Server.hpp"
#include "net/Broadcaster.hpp"

#include "loffice/doccontrol/ppt/PPTController.hpp"


using namespace std;


#define PORT_TO_BROADCAST 9192
/*#define BACKLOG 10
#define MAXDATASIZE 100
#define PORT_TO_BROADCAST 9192

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
}*/

int main(int argc, char *argv[])
{
	LocalIpAddress * ip_address = new LocalIpAddress();
	vector<ip_info> ips = ip_address->getAddresses();

	//Broadcaster * broadcaster = new Broadcaster();



	for (unsigned int i = 0 ;i<ips.size();i++)
	{
		struct ip_info ip_data = ips.at(i);
		//cout << "Broadcasting a la ip : " << ip_data.broadcast_address << " en el puerto :" << PORT_TO_BROADCAST << endl;

		//cout << ip_data.broadcast_address << endl;


		//broadcaster->startBroadcast(ip_data.broadcast_address,PORT_TO_BROADCAST,ip_data.ip_address);


	}
	Server * server = new Server();
	server->listenOn("192.168.1.34","9192");



	cout << "ok  final "<< endl;

	return 0;


	system("soffice -invisible \"-accept=socket,host=localhost,port=8100;urp;StarOffice.ServiceManager\"");

	cout << "Se esta iniciando el servidor Office..." << endl;

	sleep(3);

	PPTController * loffice_pptcontroller;

	loffice_pptcontroller->connect();
	loffice_pptcontroller->openDoc();
	loffice_pptcontroller->accessDoc();



	//LocalIpAddress * ip_address;

	/*struct sockaddr_storage their_addr;
	struct addrinfo hints, *servinfo;
	int status;
	int sockfd, new_fd;
	struct sigaction sa;
	socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];
    int numbytes;
	char buf[MAXDATASIZE];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	cout << "Escuchando conexiones en :  " << endl;
	//cout << "Ip: " << ip_address->getInternalIp() << endl;
	cout << "Puerto : 9192" << endl;

	if ((status = getaddrinfo("192.168.1.36", "9192", &hints, &servinfo)) != 0)
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

		printf("server: got connection from %s\n", s);

		cout << "ok " << endl;

		while ((numbytes = recv(new_fd, buf, MAXDATASIZE-1, 0)) > -1)
		{
			//perror("recv");
			//exit(1);
			buf[numbytes] = '\0';

			printf("client: received '%s'\n",buf);

			string command = string(buf);

			if (command.compare("next") == 0 )
			{
				cout << "ejecuta next command : " << endl;
				loffice_pptcontroller->moveToNext();
			}
			if (command.compare("prev") == 0 )
			{
				cout << "ejecuta prev command : " << endl;
				loffice_pptcontroller->moveToPrev();
			}
			if (command.compare("fullscreen") == 0 )
			{
				cout << "ejecuta fullscreen command : " << endl;
				loffice_pptcontroller->toggleFullScreen();
			}
		}


	}*/

	return 0;
}
