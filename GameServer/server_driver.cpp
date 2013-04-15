#include<iostream>
#include"NetworkServer.h"

using namespace std;

int main(){
	try{
		NetworkServer server(8888);
		EventBuff_t eventBuff;
		for(;;){
			if (server.eventsAvailable()){
				eventBuff = server.getEvents();
				for(unsigned int i = 0; i < eventBuff.size(); i++) {
					cout << eventBuff[i] << endl;
				}
			}
		}
	} catch (exception &e){
		cerr << e.what() << endl;
	}

}