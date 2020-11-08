#include "pch.h"
#include "MyClient.h"

void DataBase::ShowDB() {
	int len;
	for (auto i : db) {
		cout << "|| ";
		len = 13;
		for (auto j : i) {
			cout << j << " || ";
			len += j.length();
		}
		cout << endl;
		for (int k = 0; k <= len; k++) {
			cout << "=";
		}
		cout << endl;
	}
}

MyClient::MyClient()
{
}


MyClient::~MyClient()
{
	WSACleanup();
}

void MyClient::ClientStart() {
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
		printf("Error at WSAStartup()\n");
	//----------------------
	// Create a SOCKET for connecting to server
	
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket() : %ld\n", WSAGetLastError());
		WSACleanup();
		return;
	}
	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port of the server to be connected to.
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &(clientService.sin_addr));
	/*inet_pton(AF_INET, "127.0.0.1", &(clientService.sin_addr))*/;
	clientService.sin_port = htons(27015);
	//----------------------
	// Connect to server.
	if (connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		printf("Failed to connect.\n");
		WSACleanup();
		return;
	}

	


}

void MyClient::GetDB()
{
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			bytesRecv = SOCKET_ERROR;
			while (bytesRecv == SOCKET_ERROR) {
				char recvbuf[64] = "";
				bytesRecv = recv(ConnectSocket, recvbuf, 64, 0);
				doshka.db[i][j] = string(recvbuf);
				if (bytesRecv == 0 || bytesRecv == WSAECONNRESET) {
					printf("Connection Closed.\n");
					break;
				}
			}
		}
	}
}

void MyClient::SendMess()
{
}

bool MyClient::Process()
{
	while (1) {
		string mess;
		getline(cin, mess);
		if (mess.length() > 64) {
			cout << "Short requestes - 64 symbols";
		}
		else if (((int)(mess[2]-'0'>3|| mess[2] - '0' <0))&&((int)(mess[0] - '0' > 9 || mess[0] - '0' < 0))){
			cout << "First - number of row, one space char, then - number of column";
		}
		else {
			strcpy_s(sendbuf, mess.c_str());
			bytesSent = send(ConnectSocket, sendbuf, strlen(sendbuf), 0);
			GetDB();
			system("cls");
			doshka.ShowDB();
		}
	}
	return false;
}

