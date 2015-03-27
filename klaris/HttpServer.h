#pragma once
#include "stdafx.h"

class HttpServer : public SocketSelectServer
{
public:
	HttpServer();
	~HttpServer();
};

