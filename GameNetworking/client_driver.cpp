#include<iostream>
#include"NetworkClient.h"

using namespace std;

int main(){
	int a;
	try{
		NetworkClient client(5556);
		cout << "socket created" << endl;
		State_t state;
		client.bindToServer("127.0.0.1", DEFAULT_PORT);
		while(1) {
			client.sendToServer("hello server");
			Sleep(10000);
		}
	} catch (const std::exception &exc){
		cout << "exception occured!" << endl;
		cout << exc.what() << endl;
		cin >> a;
	}
	cin >> a;
}