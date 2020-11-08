#pragma once
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <vector>
#include<string>
using namespace std;

struct DataBase {
	vector<vector<string>> db = { {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."} };
	void ShowDB();
};

class MyServer
{
public:
	MyServer();
	~MyServer();
	void StartServer();
	void SendDB();
	void Process();
	unsigned short port;
	DataBase doshka;
	int bytesSent;
	int bytesRecv = SOCKET_ERROR;
	char sendbuf[64] = "Client: Sending data.";
	char recvbuf[64] = "";
private: 
	SOCKET this_s;
	SOCKET AcceptSocket;
	SOCKET ListenSocket;

	WSAData wData;
};

