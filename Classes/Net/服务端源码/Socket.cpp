#include "Socket.h"

bool Socket::init_Socket()
{
	WSAData wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata))//windows socket ansyc(windows异步套接字),这第一个参数WORD类型好像就是指定版本的
	{
		std::cerr << "WSAStartup\n";
		return false;
	}
	return true;
}

bool Socket::close_Socket()
{
	if (0 != WSACleanup())
	{
		std::cerr << "WSACleanup\n";
		return false;
	}
	return true;
}
