#pragma once
#include"Socket.h"
#include<vector>
#include<mutex>
#include<iostream>
#include<memory.h>

/**
* @brief 服务端（单例）
*/
class Server
{
public:

	static std::shared_ptr<Server>& getInstance(const std::string& ip = "");

	//关闭套接字
	void Close();

	//开始接收客户端
	void Start();

	//接收内容
	void recvData();

	//开启线程接收消息
	void Doit()
	{
		std::thread recvThread = std::thread(&Server::recvData, this);
		recvThread.detach();
	}

	//发送内容
	void sendData(const char*);


private:

	Server(const std::string& ip);

	//接受客户端
	void Accept();

	//创建服务端socket
	static bool create(const std::string& ip);

	//处理data函数
	void Do();

private:

	static SOCKET _socket;

	/*static Server* _server;*/

	static std::shared_ptr<Server> _server;

	char _data[kMAX];

	//客户端集合
	std::vector<SOCKET> _client;

};


