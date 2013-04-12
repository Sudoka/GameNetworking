#pragma once
#include<WinSock2.h>
#include<string>
#include<iostream>
#include"Sendable.h"

#pragma comment(lib,"ws2_32.lib")
#define DEFAULT_PORT 5555
using namespace std;

class Network
{
public:
	Network(void);
	Network(string ip, unsigned short port);
	Network(unsigned short port);
	virtual ~Network(void);

protected:
	struct sockaddr_in& getSockAddr();
	struct sockaddr_in m_sockaddr;
	friend class NetworkClient;
};

