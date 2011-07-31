/*
 * Broadcaster.cpp
 *
 *  Created on: Jul 16, 2011
 *      Author: mordonez
 */

#include "Broadcaster.hpp"

void Broadcaster::startBroadcast(string ip ,int port,string message)
{
	printf("ok");
	int sockfd;
	struct sockaddr_in their_addr; // connector's address information
	struct hostent *he;
	int numbytes;
	int broadcast = 1;
	//char broadcast = '1'; // if that doesn't work, try this

	if ((he=gethostbyname(ip.c_str())) == NULL) {  // get the host info
		perror("gethostbyname");
		exit(1);
	}


	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	// this call is what allows broadcast packets to be sent:
	if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
		sizeof broadcast) == -1) {
		perror("setsockopt (SO_BROADCAST)");
		exit(1);
	}

	their_addr.sin_family = AF_INET;     // host byte order
	their_addr.sin_port = htons(port); // short, network byte order
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);

	if ((numbytes=sendto(sockfd,message.c_str(), strlen(message.c_str()), 0,
			 (struct sockaddr *)&their_addr, sizeof their_addr)) == -1) {
		perror("sendto");
		exit(1);
	}

	printf("sent %d bytes to %s\n", numbytes,
		inet_ntoa(their_addr.sin_addr));

	close(sockfd);
}
