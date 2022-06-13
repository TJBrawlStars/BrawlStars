#pragma warning(disable:4996)
#include "Server.h"

SOCKET Server::_socket = INVALID_SOCKET;
std::shared_ptr<Server> Server::_server = NULL;
static std::mutex _mutex;
using namespace std;

std::shared_ptr<Server>& Server::getInstance(const string& ip)
{
	if (_server == NULL)
	{
		if (ip != "")
		{
			std::shared_ptr<Server> p1(new Server(ip));
			_server = p1;
		}
	}
	return _server;
}

void Server::Close()
{
	if (_socket != INVALID_SOCKET || _server != NULL)
	{
		closesocket(_socket);
		_socket = INVALID_SOCKET;
		_server.reset();
		_server = NULL;
	}
}

void Server::Start()
{
	cout << "wait for accept" << endl;
	std::thread recvThread = std::thread(&Server::Accept, this);
	recvThread.detach();
}

void Server::recvData()
{
	while (_client.size() == 0);
	while (true)
	{
		for (auto item : _client)
		{
			int ret = recv(item, _data, kMAX, 0);
			if (ret <= 0)
				continue;
			Do();
		}
	}
}

void Server::sendData(const char*data)
{
	std::lock_guard<std::mutex>lock(_mutex);
	//给全部客户端发
	
	vector<SOCKET>::iterator it = _client.begin();
	while (it != _client.end())
	{
		auto client = *it;
		if (INVALID_SOCKET == send(client, data, kMAX, 0))//最后一个是flag写0即可
		{
			cerr << "send fail" << __LINE__ << endl;
			it = _client.erase(it);
			cerr << "delete socket" << __LINE__ << endl;
			if (it != _client.end())
				continue;
		}
		cout << "sent " << data << " suc\n";
		++it;
	}
}

void Server::Accept()
{
	while (true)
	{
		SOCKET client = accept(_socket, NULL, NULL);
		cout << "one accept suc\n";
		//限制锁的范围
		{
			std::lock_guard<std::mutex>lock(_mutex);
			if (client != INVALID_SOCKET)
				_client.push_back(client);
			else
				cerr << "accept fail" << __LINE__ << endl;
		}
		sendData("MSG 520 hello");
		Sleep(50);
	}
}

Server::Server(const std::string& ip)
{
	if (_socket == INVALID_SOCKET)
	{
		if (!create(ip))
			cerr << "create server fail" << __LINE__ << endl;
	}
}

bool Server::create(const std::string& ip)
{

	//1 创建一个空的socket
	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//AF_INET代表ipv4(协议族),SOCK_STREAM为流式套接字,IPPROTO_TCP TCP协议)
	if (INVALID_SOCKET == server)//无符号零取反，无符号int最大
	{
		cerr << "socket fail" << __LINE__ << endl;
		return false;
	}

	//2 给socket绑定ip和端口
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;//协议族
	addr.sin_port = htons(kPORT);//端口号(htons变为网络字节序,大端存储小端存储)
	addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());//ADDR_ANY;//绑定本地任意ip
	if (SOCKET_ERROR == bind(server, static_cast<struct sockaddr*>(static_cast<void*>(&addr)), sizeof(addr)))//直接static_cast不行啊，最后搞成这样了,之后再研究吧
	{
		cerr << "bind fail" << __LINE__ << endl;
		return false;
	}

	//3 开始监听
	listen(server, 10);//10随便写，好像就是个log

	_socket = server;
	return true;
}

void Server::Do()
{
	/*auto data = _data).asString();
	auto datatype = data.substr(0, data.find(':'));*/
	//data = data.substr(data.find(':') + 1);
	//if (datatype == "MEG")
	sendData(_data);
}

