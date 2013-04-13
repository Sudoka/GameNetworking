#include "NetworkClient.h"

NetworkClient::NetworkClient(void):m_stateAvailable(false) {
	Network::Network();
	InitializeCriticalSection(&m_cs);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}
}

NetworkClient::NetworkClient(string ip, unsigned short port):m_stateAvailable(false) {
	Network::Network(ip, port);
	InitializeCriticalSection(&m_cs);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}
}

NetworkClient::NetworkClient(unsigned short port):m_stateAvailable(false) {
	Network::Network(port);
	InitializeCriticalSection(&m_cs);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}
}

inline int NetworkClient::bindToServer(string ip, unsigned short port) {

	m_server = Network(ip, port);

	//bind server port to socket
	if(bind(m_sock ,(struct sockaddr *)&(m_server.m_sockaddr),
		sizeof(m_server.m_sockaddr)) == SOCKET_ERROR) {
			return WSAGetLastError();
	}

	//start thread to recv data from server
	unsigned int threadID;
	m_hThread = (HANDLE)_beginthreadex( NULL, // security
                      0,             // stack size
                      NetworkClient::ThreadStaticEntryPoint,// entry-point-function
                      this,           // arg list holding the "this" pointer
                      0,		
                      &threadID );
	return 0;
}

void NetworkClient::sendToServer(Event e) {
	if(sendto(m_sock, e.c_str(), e.size() + 1, 0, (sockaddr *) &m_server, sizeof(m_server)) == SOCKET_ERROR) {
		throw runtime_error("sendto() failed with error code : " + WSAGetLastError());
	}
}

void NetworkClient::updateGameState() {
	char local_buf[MAX_PACKET_SIZE];
	while(1) {
		memset(local_buf,'\0', MAX_PACKET_SIZE);
		int recv_len;
		if ((recv_len = recv(m_sock, local_buf, MAX_PACKET_SIZE, 0) == SOCKET_ERROR)) {
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}	
		EnterCriticalSection(&m_cs);
		m_gameState.push_back(string(local_buf));
		LeaveCriticalSection(&m_cs);
	}
}


State_t NetworkClient::getGameState() {

	EnterCriticalSection(&m_cs);
	State_t rtn = m_gameState;
	m_gameState.clear();
	LeaveCriticalSection(&m_cs);

	return rtn;
}

NetworkClient::~NetworkClient(void) {
	CloseHandle(m_hThread);
	closesocket(m_sock);	
    WSACleanup();
}
