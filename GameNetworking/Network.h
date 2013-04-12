#pragma once
#include<WinSock2.h>
#include<string>
#define DEFAULT_PORT 5555
using namespace std;

class Network
{
public:
	Network(void);
	Network(string ip, unsigned short port);
	Network(unsigned short port);
	virtual ~Network(void);
private:
	struct sockaddr_in m_sockaddr;
};

