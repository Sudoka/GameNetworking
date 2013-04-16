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
		State_t gameState;
		D3DXVECTOR3 m_pos(2,2,2);
		D3DXVECTOR3 m_dir(1,1,1);
		//gameState.push_back(Entity());
		Entity *test = new Entity(m_pos,m_dir);
		gameState.push_back(test);

		for(;;) {
			if (server.eventsAvailable()) {
				eventBuff = server.getEvents();
				for(unsigned int i = 0; i < eventBuff.size(); i++) {
					cout << *eventBuff[i] << endl;
				}
			}
			if(eventBuff.size() < 50 && !eventBuff.empty()) {
				gameState[0]->m_pos.z += .05;
				server.broadcastGameState(gameState);
			}
			if(!eventBuff.empty()) {
				eventBuff.clear();
			}
			Sleep(16);
		}
	} catch (exception &e) {
		cout << "exception occured!" << endl;
		cerr << e.what() << endl;
		system("pause");
	}

}