#include<iostream>
#include"NetworkServer.h"

using namespace std;

void printEntity(Entity const &e) {
	cout << e.getID() << " " << e.m_pos.x << " " << e.m_pos.y << " " << e.m_pos.z
		<< e.m_dir.x << " " << e.m_dir.y << " " << e.m_dir.z << endl;
	}

int main(){
	try{
		cout << "Server:" << endl;
		NetworkServer server(8888);
		cout << "socket created:" << endl;
		EventBuff_t eventBuff;
		for(;;){
			if (server.eventsAvailable()){
				eventBuff = server.getEvents();
				for(unsigned int i = 0; i < eventBuff.size(); i++) {
					cout << eventBuff[i] << endl;
				}
			}
			if(eventBuff.size() < 50 && eventBuff.size() != 0) {
				server.broadcastGameState(eventBuff);
			}
			eventBuff.clear();
			Sleep(16);
		}
	} catch (exception &e){
		cout << "exception occured!" << endl;
		cerr << e.what() << endl;
		system("pause");
	}

}