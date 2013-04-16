#include<iostream>
#include"NetworkClient.h"

using namespace std;


int main(){
	try{
		cout << "Client:" << endl;
		NetworkClient client;		
		cout << "socket created" << endl;
		State_t state;
		client.bindToServer("127.0.0.1", 8888);
		Entity *e = new Entity();
		while(1) {
			client.sendToServer(e);
			Sleep(32);
			vector<Entity *> state = client.getGameState().getEntities();
			for(int i = 0; i < state.size(); i++) {
				cout << state[i] << endl;
			}
			state.clear();
		}
		delete e;
	} catch (const std::exception &exc){
		cout << "exception occured!" << endl;
		cout << exc.what() << endl;
		system("pause");
	}
	
}