#include<iostream>
#include"NetworkClient.h"

using namespace std;

int main(){
	int a;
	try{
		NetworkClient client("127.0.0.1", DEFAULT_PORT + 1);
		cout << "socket created" << endl;
		State_t state;
		client.bindToServer("127.0.0.1", 8888);
		while(1) {
			client.sendToServer(Entity());
			Sleep(1000);
			state = client.getGameState();
			for(int i = 0; i < state.size(); i++) {
				cout << state[i].getID() << " " << state[i].m_pos << " " << state[i].m_dir << endl;
			}
		}
	} catch (const std::exception &exc){
		cout << "exception occured!" << endl;
		cout << exc.what() << endl;
		cin >> a;
	}
	cin >> a;
	cout << a;
}