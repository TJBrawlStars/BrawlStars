#pragma once
#include"cocos2d.h"
#include"Socket.h"

/**
* @brief 客户端（单例）
*/
class Client :public cocos2d::Ref
{
public:

	//第一次用要加ip地址
	static Client* getInstance(const std::string& ip = "");

	//关闭套接字
	void Close();

	//开始接收内容
	void Start();

	//获取最新数据
	virtual void update(std::vector<std::string>& data);

	//发送内容
	void sendData(const std::string&);

private:

	//接收内容
	void recvData();

	Client(const std::string& ip);

	//创建客户端socket
	static bool create(const std::string& ip);

private:

	//信息列表
	std::vector<std::string> _msg;

	static SOCKET _socket;

	static Client* _client;

	std::mutex _mutex;

};

