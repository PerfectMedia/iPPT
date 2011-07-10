/*
 * LocalIpAddress.h
 *
 *  Created on: Jun 19, 2011
 *      Author: mordonez
 */

#ifndef LOCALIPADDRESS_H_
#define LOCALIPADDRESS_H_

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

class LocalIpAddress
{
public:
	LocalIpAddress();
	virtual ~LocalIpAddress();
	string getIp();
private:
	bool isInternal(string ip);
};

#endif /* LOCALIPADDRESS_H_ */
