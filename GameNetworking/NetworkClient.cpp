#include "NetworkClient.h"


NetworkClient::NetworkClient(void) {
	Network::Network();
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
        //cerr << "Could not create socket : " <<  WSAGetLastError() << endl;
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}
}

NetworkClient::NetworkClient(string ip, unsigned short port) {
	Network::Network(ip, port);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
        //cerr << "Could not create socket : " <<  WSAGetLastError() << endl;
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}
}

NetworkClient::NetworkClient(unsigned short port) {
	Network::Network(port);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
        //cerr << "Could not create socket : " <<  WSAGetLastError() << endl;
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}
}

int NetworkClient::bindToServer(string ip, unsigned short port) {
	m_server = Network(ip, port);
	if(bind(m_sock ,(struct sockaddr *)&(m_server.m_sockaddr),
		sizeof(m_server.m_sockaddr)) == SOCKET_ERROR) {
			return WSAGetLastError();
	}
	return 0;
}

NetworkClient::~NetworkClient(void) {
	closesocket(m_sock);
    WSACleanup();
}
