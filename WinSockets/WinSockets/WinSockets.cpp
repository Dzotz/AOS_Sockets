#include "pch.h"
//#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "MyServer.h"

using namespace std;



int main()
{	
	setlocale(LC_ALL, "");
	MyServer server;
	server.StartServer();
	server.SendDB();
	server.Process();
}
