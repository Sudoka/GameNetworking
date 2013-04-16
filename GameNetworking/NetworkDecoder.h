#pragma once
#include"NetworkEncoded.h"
#include"../core/Entity.h"
#include<vector>

typedef Entity Event;

class NetworkDecoder
{
private:
	unsigned int m_size;
	const char *m_head;
	const char *m_curr_head;

public:
	NetworkDecoder(const char *head, unsigned int size) {
		char * tmp = new char[size];
		m_head = tmp;
		m_size = size;
		memcpy(tmp, head, size);
	};

	void decodeEntities(vector<Entity> &) {
		

	}
	void decodeEvents(vector<Event> &);
	virtual ~NetworkDecoder(void);
};

