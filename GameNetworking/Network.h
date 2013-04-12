#pragma once
#include<WinSock2.h>
#include<string>
#include<iostream>
#include<process.h>
#include"Sendable.h"

#pragma comment(lib,"ws2_32.lib")

#define WIN32_LEAN_AND_MEAN
#define DEFAULT_PORT 5555
#define MAX_PACKET_SIZE 65507
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

