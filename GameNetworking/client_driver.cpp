#include<iostream>
#include"NetworkClient.h"

using namespace std;


int main(){
	int a;
	try{
		cout << "Client:" << endl;
		NetworkClient client("127.0.0.1", DEFAULT_PORT + 1);		
		cout << "socket created" << endl;
		State_t state;
		client.bindToServer("127.0.0.1", 8888);
		while(1) {
			client.sendToServer(Entity());
			Sleep(500);
			state = client.getGameState();
			for(int i = 0; i < state.size(); i++) {
				//printEntity(state[i]);
				cout << state[i] << endl;
			}
			state.clear();
		}
	} catch (const std::exception &exc){
		cout << "exception occured!" << endl;
		cout << exc.what() << endl;
		cin >> a;
	}
	cin >> a;
	cout << a;
}