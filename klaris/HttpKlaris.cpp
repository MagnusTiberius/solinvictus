#include "HttpKlaris.h"


HttpKlaris::HttpKlaris()
{
	AddRoute("/", &HttpKlaris::HandleHome);
	AddRoute("/test", &HttpKlaris::HandleTest);
}


HttpKlaris::~HttpKlaris()
{
}

void HttpKlaris::AddRoute(char *purl, LP_MEM_FUNC3 lpFunc)
{
	m_routes[purl] = lpFunc;
}

void HttpKlaris::EvaluateRoute(HttpHeader *httpHeader)
{
	LP_MEM_FUNC3 lpFunc = m_routes[std::string(httpHeader->GetUrl())];
	if (lpFunc != NULL)
		(this->*lpFunc)();
	else
		Handle404();
}

void HttpKlaris::HandleTest()
{
	const char* body = "<html><h1>This is a test page.</h1><br><hr></html>\n";
	int bodylen = strlen(body);
	char content[DATA_BUFSIZE];
	memset(m_SocketInfo->BufferOut, '\0', DATA_BUFSIZE);
	memset(content, '\0', DATA_BUFSIZE);
	sprintf_s(content, DATA_BUFSIZE, "HTTP/1.0 200 OK\nDate: Fri, 31 Dec 1999 23:59:59 GMT\nContent-Type: text/html\nContent-Length: %d\n\n%s", bodylen, body);
	sprintf_s(m_SocketInfo->BufferOut, DATA_BUFSIZE, "%s", content);
	m_SocketInfo->BytesSEND = strlen(m_SocketInfo->BufferOut);
}

void HttpKlaris::HandleHome()
{
	const char* body = "<html><h1>Klaris web server home page loaded.</h1><br><hr></html>\n";
	int bodylen = strlen(body);
	char content[DATA_BUFSIZE];
	memset(m_SocketInfo->BufferOut, '\0', DATA_BUFSIZE);
	memset(content, '\0', DATA_BUFSIZE);
	sprintf_s(content, DATA_BUFSIZE, "HTTP/1.0 200 OK\nDate: Fri, 31 Dec 1999 23:59:59 GMT\nContent-Type: text/html\nContent-Length: %d\n\n%s", bodylen, body);
	sprintf_s(m_SocketInfo->BufferOut, DATA_BUFSIZE, "%s", content);
	m_SocketInfo->BytesSEND = strlen(m_SocketInfo->BufferOut);
}
