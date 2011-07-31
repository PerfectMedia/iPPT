/*
 * Server.cpp
 *
 *  Created on: Jul 30, 2011
 *      Author: mordonez
 */

#include "Server.hpp"

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

Server::Server()
{
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
}

int Server::listenOn(string ip,string port)
{
	cout << "ok1" << endl;
	if ((status = getaddrinfo(ip.c_str(), port.c_str(), &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}

	sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

	cout << "ok2" << endl;
	int yes=1;
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)
	{
		perror("setsockopt");
		return 1;
	}



	cout << "ok3" << endl;
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


	cout << "ok4" << endl;
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


	cout << "ok5" << endl;
	 while(1)
	 {
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family,
			get_in_addr((struct sockaddr *)&their_addr),s, sizeof s);

		printf("server: got connection from %s\n", s);


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
				//loffice_pptcontroller->moveToNext();
			}
			if (command.compare("prev") == 0 )
			{
				cout << "ejecuta prev command : " << endl;
				//loffice_pptcontroller->moveToPrev();
			}
			if (command.compare("fullscreen") == 0 )
			{
				cout << "ejecuta fullscreen command : " << endl;
				//loffice_pptcontroller->toggleFullScreen();
			}
		}


	}

	cout << "ok6" << endl;
}
