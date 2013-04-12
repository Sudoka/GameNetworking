#pragma once
#include "network.h"
class NetworkServer :
	public Network
{
public:
	NetworkServer(void);
	virtual ~NetworkServer(void);
};

