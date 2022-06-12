#include"Server.h"
using namespace std;

int main()
{
	string ip;
	cout << "请输入服务端ip" << endl;
	cin >> ip;
	Socket::init_Socket();
	Server::getInstance(ip)->Start();
	Server::getInstance()->Doit();
	//Server::getInstance()->recvData();
	//std::thread recvThread = std::thread(Server::getInstance()->recvData());
	//recvThread.detach();
	cout << "若要服务器发送信息，请按照格式发送，若要退出，请输入ESC\n";
	while (true)
	{
		char a[kMAX];
		cin.getline(a, kMAX, '\n');
		
		if (a[0] == 'E' && a[1] == 'S' && a[2] == 'C')
			break;
		Server::getInstance()->sendData(a);
	}

	Server::getInstance()->Close();
	std::cout << "Server close\n";
	Socket::close_Socket();
}