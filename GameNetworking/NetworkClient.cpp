#include "NetworkClient.h"

NetworkClient::NetworkClient(void):m_stateAvailable(false) {
	Network::Network();
	InitializeCriticalSection(&m_cs);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
        //cerr << "Could not create socket : " <<  WSAGetLastError() << endl;
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}
}

NetworkClient::NetworkClient(string ip, unsigned short port):m_stateAvailable(false) {
	Network::Network(ip, port);
	InitializeCriticalSection(&m_cs);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
        //cerr << "Could not create socket : " <<  WSAGetLastError() << endl;
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}
}

NetworkClient::NetworkClient(unsigned short port):m_stateAvailable(false) {
	Network::Network(port);
	InitializeCriticalSection(&m_cs);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
        //cerr << "Could not create socket : " <<  WSAGetLastError() << endl;
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

void NetworkClient::updateGameState() {
	char local_buf[MAX_PACKET_SIZE];
	while(1) {
		memset(local_buf,'\0', MAX_PACKET_SIZE);
		int recv_len;
		if ((recv_len = recv(m_sock, local_buf, MAX_PACKET_SIZE, 0) == SOCKET_ERROR) {
			printf("recvfrom() failed with error code : %d" , WSAGetLastError());
			cin >> a;
			exit(EXIT_FAILURE);
		}	
		EnterCriticalSection(&m_cs);
		m_gameState.push_back(string(local_buf));
		LeaveCriticalSection(&m_cs);
	}
}


vector<Entity> NetworkClient::getGameState() {

	EnterCriticalSection(&m_cs);
	vector<Entity> rtn = m_gameState;
	m_gameState.clear();
	LeaveCriticalSection(&m_cs);

	return rtn;
}

NetworkClient::~NetworkClient(void) {
	closesocket(m_sock);
	CloseHandle(m_hThread);
    WSACleanup();
}
