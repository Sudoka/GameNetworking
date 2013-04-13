#pragma once
#include "network.h"
#include <vector>

typedef string Event;
typedef vector<Event> EventBuff_t;

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

	//returns true if there are new events available
	bool eventsAvailable() { return m_eventsAvailable; };

	//returns a vector of events received
	EventBuff_t getEvents();


	virtual ~NetworkServer(void);
private:

	SOCKET m_sock;
	EventBuff_t m_eventsBuffer;
	bool m_eventsAvailable;

	//thread stuff
	CRITICAL_SECTION m_cs;
	HANDLE m_hThread;
	void updateEventsBuffer();

	static unsigned __stdcall ThreadStaticEntryPoint(void * pThis) {
		NetworkServer * pthX = (NetworkServer*)pThis;
		pthX->updateEventsBuffer();	
		return 1;
	}

};

