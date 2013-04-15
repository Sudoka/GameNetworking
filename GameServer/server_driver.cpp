#include<iostream>
#include"NetworkServer.h"

using namespace std;

void printEntity(Entity const &e) {
	cout << e.getID() << " " << e.m_pos.x << " " << e.m_pos.y << " " << e.m_pos.z
		<< e.m_dir.x << " " << e.m_dir.y << " " << e.m_dir.z << endl;
	}

int main(){
	Entity e1;
	printEntity(e1);
	const char* s = e1.encode();
	Entity e2(e1.decode(s));
	printEntity(e2);
	int a;
	cin >> a;

	/*try{
		NetworkServer server(8888);
		EventBuff_t eventBuff;
		for(;;){
			if (server.eventsAvailable()){
				eventBuff = server.getEvents();
				for(unsigned int i = 0; i < eventBuff.size(); i++) {
					printEntity(eventBuff[i]);
				}
			}
			if(eventBuff.size() < 50) {
				server.broadcastGameState(eventBuff);
			}
			eventBuff.clear();
			Sleep(16);
		}
	} catch (exception &e){
		cerr << e.what() << endl;
	}
*/
	

}