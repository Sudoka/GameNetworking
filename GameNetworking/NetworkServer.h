#pragma once
#include "network.h"
class NetworkServer :
	public Network
{
public:
	NetworkServer(void);
	NetworkServer(string ip, unsigned short port);
	NetworkServer(unsigned short port);
	virtual ~NetworkServer(void);
private:
	SOCKET m_sock;
};

