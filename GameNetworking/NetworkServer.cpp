#include "NetworkServer.h"


NetworkServer::NetworkServer(void) {
	Network::Network();
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
        //cerr << "Could not create socket : " <<  WSAGetLastError() << endl;
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}
}

NetworkServer::NetworkServer(string ip, unsigned short port) {
	Network::Network(ip, port);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
        //cerr << "Could not create socket : " <<  WSAGetLastError() << endl;
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}
}

NetworkServer::NetworkServer(unsigned short port) {
	Network::Network(port);
	if( (m_sock = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET )  {
        //cerr << "Could not create socket : " <<  WSAGetLastError() << endl;
		throw runtime_error("Could not create socket : " + WSAGetLastError());
	}
}

NetworkServer::~NetworkServer(void) {
	closesocket(m_sock);
    WSACleanup();
}
