#include "pch.h"
#include "MyClient.h"

int main()
{
	MyClient client;
	client.ClientStart();	
	client.GetDB();
	client.doshka.ShowDB();
	client.Process();
}
