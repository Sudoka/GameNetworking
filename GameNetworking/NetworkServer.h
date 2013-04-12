#pragma once
#include "network.h"
class NetworkServer :
	public Network
{
public:

	//creates a NetworkServer with default port and any ip address
	//Throws runtime_error exception if socket cannot be opened
	NetworkServer(void);

	//creates NetworkServer with ip and port number passed
	//note: ip should be in the form "127.0.0.1"
	//Throws runtime_error exception if socket cannot be opened
	NetworkServer(string ip, unsigned short port);

	//creates NetworkServer with any ip address and passed port
	//Throws runtime_error exception if socket cannot be opened
	NetworkServer(unsigned short port);

	virtual ~NetworkServer(void);
private:
	SOCKET m_sock;
	CRITICAL_SECTION m_cs;
};

