// Hello socket.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int ret = connect(sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret)
		cout << "连接失败" << endl;
	else
		cout << "连接成功" << endl;
	//接收服务器发来的信息
	char revbuf[256];
	recv(sock, revbuf, 256, 0);
	cout << "接收到服务器的信息:" << revbuf << endl;
	//关闭
	closesocket(sock);



	WSACleanup();
	system("pause");
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
