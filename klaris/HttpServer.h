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
	
	typedef void (HttpServer::*LP_MEM_FUNC) ();

	virtual void Request(LPSOCKET_INFORMATION pSocketInfo);
	void AddRoute(char *url, LP_MEM_FUNC lpFunc);

private:
	std::map <std::string, LP_MEM_FUNC> m_routes;
	LPSOCKET_INFORMATION m_SocketInfo;
	HttpHeader httpHeader;

	void HandleHome();
	void HandleTest();
	void EvaluateRoute(HttpHeader *httpHeader);
	void Handle404();
};

