#pragma once

#include "stdafx.h"
#include <vector>
#include <string>
#include <map>

class HttpServer : public SocketSelectServer
{
public:
	HttpServer();
	~HttpServer();
	
	typedef std::pair<char*, void*> pair_t;

	virtual void Request(LPSOCKET_INFORMATION pSocketInfo);
	typedef void (HttpServer::*FUNC) ();
	void AddRoute(char *url, FUNC lpFunc);

private:
	HttpHeader httpHeader;

	std::map <std::string, FUNC> m_routes;
	void HandleHome();
	void HandleTest();
	void EvaluateRoute(HttpHeader *httpHeader);
	void Handle404();

	LPSOCKET_INFORMATION m_SocketInfo;
};

