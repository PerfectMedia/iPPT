/*
 * LocalIpAddress.cpp
 *
 *  Created on: Jun 19, 2011
 *      Author: mordonez
 */

#include "LocalIpAddress.h"



LocalIpAddress::LocalIpAddress()
{
	// TODO Auto-generated constructor stub

}

LocalIpAddress::~LocalIpAddress()
{
	// TODO Auto-generated destructor stub
}

bool LocalIpAddress::isInternal(string ip)
{

	bool is_internal = false;

	char ip_1 [9] = "192.168.";
	char ip_2 [5] = "172.";
	char ip_3 [4] = "10.";

	char * ips[] = {ip_1,ip_2,ip_3};

	for (int j=0;j<3;j++)
	{

		if(ip.find(ips[j]) !=string::npos)
		{
			is_internal = true;
		}

	}

	return is_internal;

}

string LocalIpAddress::getIp()
{
	string LOCAL_IP;

	FILE * fp = popen("ifconfig", "r");
	if (fp) {
			char *p=NULL, *e; size_t n;
			while ((getline(&p, &n, fp) > 0) && p) {
			   if (p = strstr(p, "inet addr:")) {
					p+=10;
					if (e = strchr(p, ' ')) {
						 *e='\0';

						string ip = p;

						if(isInternal(ip))
						{
							LOCAL_IP = ip;
							break;
						}
					}
			   }
			}
	}
	pclose(fp);

	return LOCAL_IP;
}
