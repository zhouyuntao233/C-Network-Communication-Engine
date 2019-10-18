// TCP server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<WinSock2.h>//winsock2必须放在windows上面，因为早期的window已经实现了winsock,会引起冲突
#include<windows.h>
using namespace std;
#pragma comment(lib,"ws2_32")//明确指出要用到的库
int main()
{
	WORD ver = MAKEWORD(2, 2);//版本号
	WSADATA data;//wsa数据指针
	WSAStartup(ver, &data);
	//建立套接字
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//AF_INET为网络版本号，SOCK_STREAM 网络为什么的类型,什么样一种协议的网络
	//绑定网络端口
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;//定义绑定地址的类型为ipv4
	_sin.sin_port = htons(4567);//主机to网络
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;//主机任意ip都可以访问的
	if (SOCKET_ERROR == bind(sock, (sockaddr*)&_sin, sizeof(_sin)))
		cout << "绑定失败" << endl;
	else
		cout << "绑定成功" << endl;
	//监听端口listen
	if (SOCKET_ERROR == listen(sock, 5))//最多5人连接
		cout << "监听失败" << endl;
	else
		cout << "监听成功" << endl;
	//等待接收accept
	sockaddr_in client = {};
	SOCKET csock = INVALID_SOCKET;
	int claddr = sizeof(sockaddr_in);
	char msgbuf[] = "hello i am server";
	while (true) {
		csock = accept(sock, (sockaddr*)&client, &claddr);//阻塞直到有客户端连接
		if (csock == INVALID_SOCKET)
			cout << "接收到无效客户端sock" << endl;
		cout << "新客户加入" << inet_ntoa(client.sin_addr) << endl;
		//向客户端发送数据
		csock = send(csock, msgbuf, strlen(msgbuf) + 1, 0);
		if (csock == SOCKET_ERROR)
			cout << "发送消息失败" << endl;
		else
			cout << "发送消息成功" << endl;
	}
	//关闭自身
	closesocket(sock);


	WSACleanup();
	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
