#include "pch.h"
#include "MyServer.h"


MyServer::MyServer()
{
}


MyServer::~MyServer()
{
	WSACleanup();
}

void MyServer::StartServer() {
	
	int iResult = WSAStartup(MAKEWORD(2, 2), &wData);
	if (iResult != NO_ERROR)
		printf("ы");

	//----------------------
	// Create a SOCKET for listening for
	// incoming connection requests
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET) {
		printf("ыы");
		WSACleanup();
		return;
	}
	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	sockaddr_in service = { 0 };
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = htonl(INADDR_ANY);
	service.sin_port = htons(27015);

	//----------------------
	// Bind the socket.
	if (bind(ListenSocket,
		(SOCKADDR*) &service,
		sizeof(service)) == SOCKET_ERROR) {
		printf("ыыыы");
		closesocket(ListenSocket);
		return;
	}
	//----------------------
// Listen for incoming connection requests
// on the created socket
	if (listen(ListenSocket, 1) == SOCKET_ERROR) //можливе лише одне підключення
		printf("..");

	// Create a SOCKET for accepting incoming requests.
	printf(" Waiting for client to connect...\n");
	//----------------------
	// Accept the connection.
	while (1) {
		AcceptSocket = SOCKET_ERROR;
		while (AcceptSocket == SOCKET_ERROR) {
			AcceptSocket = accept(ListenSocket, NULL, NULL);
		}
		printf("Client connected.\n");
		ListenSocket = AcceptSocket;
		break;
	}

	//WSACleanup();

		return;
}

void MyServer::SendDB()
{
	for (auto i : doshka.db) {
		for (string j : i) {
			strcpy_s(sendbuf,j.c_str());
			bytesSent = send(ListenSocket, sendbuf, strlen(sendbuf), 0);
		}
	}

}

void MyServer::Process()
{
	while (1) {
		bytesRecv = recv(ListenSocket, recvbuf, 64, 0);
		int i = (int)(recvbuf[0]-'0');
		int j = (int)(recvbuf[2]-'0');
		char tmp[64];
		copy(begin(recvbuf) + 3, end(recvbuf), begin(tmp));
		doshka.db[i][j] = string(tmp);
		SendDB();
	}
}

void DataBase::ShowDB()
{
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
