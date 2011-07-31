/*
 * Broadcaster.hpp
 *
 *  Created on: Jul 16, 2011
 *      Author: mordonez
 */

#ifndef BROADCASTER_HPP_
#define BROADCASTER_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>

using namespace std;

class Broadcaster
{
	public:
	void startBroadcast(string ip ,int port,string message);
};

#endif /* BROADCASTER_HPP_ */
