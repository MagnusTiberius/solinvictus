#pragma once

#include <vector>
#include <string>
#include <map>
#include "SocketSelectServer.h"
#include "HttpHeader.h"

#include "stdafx.h"


class HttpServer : public SocketSelectServer
{
public:
	HttpServer();
	~HttpServer();
	
	typedef void (HttpServer::*LP_MEM_FUNC) ();

	virtual void AddRoute(char *url, LP_MEM_FUNC lpFunc);

	virtual void Request(LPSOCKET_INFORMATION pSocketInfo);
	virtual void Handle404();
	virtual void EvaluateRoute(HttpHeader *httpHeader);

protected:
	LPSOCKET_INFORMATION m_SocketInfo;
	HttpHeader httpHeader;

private:

	std::map <std::string, LP_MEM_FUNC> m_routes;
	void HandleHome();
	void HandleTest();
};

