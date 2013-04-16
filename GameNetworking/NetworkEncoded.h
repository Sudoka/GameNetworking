#pragma once
#include"Network.h"
//#include"../core/Entity.h"
class NetworkEncoded
{
private:
	const char *m_head;
	const unsigned int m_size;
	/*const char * getHead() {
		return m_head;
	}*/
	
public:
	NetworkEncoded(const char *, unsigned int size);
	unsigned int getSize() { return m_size; }
	const char* getHead() { return m_head; }
	friend class NetworkDecoder;
	virtual ~NetworkEncoded(void);
};

