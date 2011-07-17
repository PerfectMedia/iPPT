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
// Description : Class to get local ip address
//============================================================================


#include "LocalIpAddress.hpp"



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
