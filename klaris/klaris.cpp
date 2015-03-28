// klaris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HttpKlaris.h"


int _tmain(int argc, _TCHAR* argv[])
{

	HttpKlaris httpserver;

	httpserver.Init(8080);

	return 0;
}

