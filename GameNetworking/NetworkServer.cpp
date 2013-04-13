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

void NetworkServer::broadcastGameState(const State_t &state) {
	map<Network,Network>::iterator start = m_connectedClients.begin();
	map<Network,Network>::iterator end = m_connectedClients.end();

	memset(m_packetData,'\0', MAX_PACKET_SIZE);
	for(unsigned int i = 0; i < state.size(); i++) {
		strcat_s(m_packetData, state[i].size()+1, state[i].c_str());
	}

	for(map<Network,Network>::iterator it = start; it != end; it++) {
		sendToClient(m_packetData, strlen(m_packetData)+1, it->second);
	}
}

void NetworkServer::sendToClient(char * const buff, int size, Network &client) {
	if(sendto(m_sock, buff, size, 0, (sockaddr *) &(client.getSockAddr()), sizeof(sockaddr_in)) == SOCKET_ERROR) {
		throw runtime_error("sendto() failed with error code : " + WSAGetLastError());
	}
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
	struct sockaddr_in recv_addr;
	int recv_size = sizeof(recv_addr);
	while(1) {
		memset(local_buf,'\0', MAX_PACKET_SIZE);
		int recv_len;
		if ((recv_len = recvfrom(m_sock, local_buf, MAX_PACKET_SIZE, 0, (sockaddr *) &recv_addr, &recv_size) == SOCKET_ERROR)) {
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		Network lookUpAddr(recv_addr);
		EnterCriticalSection(&m_cs);
		m_connectedClients[Network(recv_addr)] = lookUpAddr;
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
