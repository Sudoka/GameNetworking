#include<iostream>
#include"NetworkServer.h"

using namespace std;

int main(){
	NetworkServer server;
	EventBuff_t eventBuff;
	for(;;){
		if (server.eventsAvailable()){
			eventBuff = server.getEvents();
			for(unsigned int i = 0; i < eventBuff.size(); i++) {
				cout << eventBuff[i] << endl;
			}
		}
	}

}