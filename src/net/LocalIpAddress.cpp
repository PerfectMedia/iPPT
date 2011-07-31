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

string LocalIpAddress::getIpDataFromLine(string line,string ip_string_to_find)
{

	size_t find_ip = line.find(ip_string_to_find);
	string ip = "";


	if(find_ip!=string::npos)
	{
		line.erase(0,int(find_ip+ip_string_to_find.size()));

		size_t find_space = line.find("  ");

		if(find_space!=string::npos)
		{
			ip = line.substr(0,find_space);
		}
	}

	return ip;
}


vector<ip_info> LocalIpAddress::getAddresses()
{
	string LOCAL_IP;

	vector<ip_info> ips;

	FILE * fp = popen("ifconfig", "r");
	if (fp) {
			char *p=NULL;
			size_t n;
			while ((getline(&p, &n, fp) > 0) && p)
			{
				string line = string(p);

				string ip_address = getIpDataFromLine(line,"inet addr:");

				if(isInternal(ip_address))
				{
					string broadcast_address = getIpDataFromLine(line,"Bcast:");

					ip_info ip;
					ip.ip_address = ip_address;
					ip.broadcast_address = broadcast_address;

					ips.push_back(ip);
				}

			}
	}
	pclose(fp);

	return ips;
}


