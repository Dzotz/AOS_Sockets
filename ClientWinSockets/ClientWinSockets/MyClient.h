#pragma once
#pragma comment(lib,"Ws2_32.lib")
#include<winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include<vector>
#include <string>
using namespace std;

struct DataBase {
	vector<vector<string>> db = { {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."}, {"...", "...", "..."} };
	void ShowDB();
};

class MyClient
{
public:
	MyClient();
	~MyClient();


	int bytesSent;
	int bytesRecv = SOCKET_ERROR;
	char sendbuf[64] = "Client: Sending data.";
	char recvbuf[64] = "";
	DataBase doshka;
	SOCKET ConnectSocket;


	void ClientStart();
	void GetDB();
	void SendMess();
	bool Process();
};

