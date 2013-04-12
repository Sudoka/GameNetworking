#pragma once
#include "network.h"
#include <exception>
class NetworkClient :
	public Network
{
public:
	NetworkClient(void);
	NetworkClient(string ip, unsigned short port);
	NetworkClient(unsigned short port);
	int bindToServer(string ip, unsigned short port);
	virtual ~NetworkClient(void);

private:
	SOCKET m_sock;
	Network m_server;
	
};

