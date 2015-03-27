#pragma once
#include "stdafx.h"
#include "HttpHeader.h"
#include "HttpServer.h"

class HttpKlaris : public HttpServer
{
public:
	HttpKlaris();
	~HttpKlaris();

	typedef void (HttpKlaris::*LP_MEM_FUNC3) ();
	void HttpKlaris::AddRoute(char *purl, LP_MEM_FUNC3 lpFunc);

	void EvaluateRoute(HttpHeader *httpHeader);

	void HandleTest();
	void HandleHome();

private:
	std::map <std::string, LP_MEM_FUNC3> m_routes;
};

