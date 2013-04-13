#include "NetworkServer.h"


NetworkServer::NetworkServer(void) : m_eventsAvailable(false) {
	Network::Network();
	InitializeCriticalSection(&m_cs);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}

	unsigned int threadID;
	m_hThread = (HANDLE)_beginthreadex( NULL, // security
                      0,             // stack size
                      NetworkServer::ThreadStaticEntryPoint,// entry-point-function
                      this,           // arg list holding the "this" pointer
                      0,		
                      &threadID );
}

NetworkServer::NetworkServer(string ip, unsigned short port) : m_eventsAvailable(false) {
	Network::Network(ip, port);
	InitializeCriticalSection(&m_cs);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}

	unsigned int threadID;
	m_hThread = (HANDLE)_beginthreadex( NULL, // security
                      0,             // stack size
                      NetworkServer::ThreadStaticEntryPoint,// entry-point-function
                      this,           // arg list holding the "this" pointer
                      0,		
                      &threadID );

}

NetworkServer::NetworkServer(unsigned short port) : m_eventsAvailable(false) {
	Network::Network(port);
	InitializeCriticalSection(&m_cs);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}

	unsigned int threadID;
	m_hThread = (HANDLE)_beginthreadex( NULL, // security
                      0,             // stack size
                      NetworkServer::ThreadStaticEntryPoint,// entry-point-function
                      this,           // arg list holding the "this" pointer
                      0,		
                      &threadID );
}

EventBuff_t NetworkServer::getEvents() {

	EnterCriticalSection(&m_cs);
	EventBuff_t rtn = m_eventsBuffer;
	m_eventsAvailable = false;
	m_eventsBuffer.clear();
	LeaveCriticalSection(&m_cs);

	return rtn;
}


void NetworkServer::updateEventsBuffer() {
	char local_buf[MAX_PACKET_SIZE];
	while(1) {
		memset(local_buf,'\0', MAX_PACKET_SIZE);
		int recv_len;
		if ((recv_len = recv(m_sock, local_buf, MAX_PACKET_SIZE, 0) == SOCKET_ERROR)) {
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		EnterCriticalSection(&m_cs);
		m_eventsBuffer.push_back(string(local_buf));
		m_eventsAvailable = true;
		LeaveCriticalSection(&m_cs);
	}
}

NetworkServer::~NetworkServer(void) {
	CloseHandle(m_hThread);
	closesocket(m_sock);
	WSACleanup();
}
