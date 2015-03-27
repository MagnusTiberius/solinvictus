// klaris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HttpServer.h"


int _tmain(int argc, _TCHAR* argv[])
{

	HttpServer httpserver;

	httpserver.Init(9090);

	return 0;
}

