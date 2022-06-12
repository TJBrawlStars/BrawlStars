#pragma once
#include<WinSock2.h>
#include <WS2tcpip.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")

//使用端口
constexpr int kPORT = 7777;
//缓冲区大小
constexpr int kMAX = 100;

/**
* @brief 用于初始化和关闭网络库
*/
class Socket
{
public:
	//初始化网络库
	static bool init_Socket();

	//关闭网络库
	static bool close_Socket();

};

