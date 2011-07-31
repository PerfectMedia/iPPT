/*
 * Server.hpp
 *
 *  Created on: Jul 30, 2011
 *      Author: mordonez
 */

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <string>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
using namespace std;

#define BACKLOG 10
#define MAXDATASIZE 100

class Server
{
public :
	int listenOn(string ip,string port);
	Server();

private:
	struct sockaddr_storage their_addr;
	struct addrinfo hints, *servinfo;
	int status;
	int sockfd, new_fd;
	struct sigaction sa;
	socklen_t sin_size;
	char s[INET6_ADDRSTRLEN];
	int numbytes;
	char buf[MAXDATASIZE];

};

#endif /* SERVER_HPP_ */
