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
			client.sendToServer("hello server");
			Sleep(8);
			state = client.getGameState();
			for(int i = 0; i < state.size(); i++) {
				cout << state[i] << endl;
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