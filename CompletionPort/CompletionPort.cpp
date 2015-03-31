// CompletionPort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SocketCompletionPortServer.h"



int _tmain(int argc, _TCHAR* argv[])
{

	SocketCompletionPortServer server;
	server.Start();

	return 0;
}

