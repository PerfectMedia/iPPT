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
// Description : Header file of LocalAddress.cpp
//============================================================================

#ifndef LOCALIPADDRESS_H_
#define LOCALIPADDRESS_H_

#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

struct ip_info
{
	string ip_address;
	string broadcast_address;
};


class LocalIpAddress
{
public:
	LocalIpAddress();
	virtual ~LocalIpAddress();
	vector<ip_info> getAddresses();
private:
	string getIpDataFromLine(string line,string ip_string_to_find);
	bool isInternal(string ip);
};

#endif /* LOCALIPADDRESS_H_ */
