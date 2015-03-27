#include "HttpServer.h"


HttpServer::HttpServer()
{
	AddRoute("/", &HttpServer::HandleHome);
	AddRoute("/test", &HttpServer::HandleTest);
}


HttpServer::~HttpServer()
{
}

void HttpServer::HandleTest()
{
	printf("Handle Home\n");

	memset(m_SocketInfo->BufferOut, '\0', DATA_BUFSIZE);
	const char* body = "<html><h1>This is a test page.</h1><br><hr></html>\n";
	int bodylen = strlen(body);


	char content[DATA_BUFSIZE];
	memset(content, '\0', DATA_BUFSIZE);
	sprintf_s(content, DATA_BUFSIZE, "HTTP/1.0 200 OK\nDate: Fri, 31 Dec 1999 23:59:59 GMT\nContent-Type: text/html\nContent-Length: %d\n\n%s", bodylen, body);

	sprintf_s(m_SocketInfo->BufferOut, DATA_BUFSIZE, "%s", content);
	m_SocketInfo->BytesSEND = strlen(m_SocketInfo->BufferOut);

}

void HttpServer::HandleHome() 
{
	printf("Handle Home\n");

	memset(m_SocketInfo->BufferOut, '\0', DATA_BUFSIZE);
	const char* body = "<html><h1>Klaris web server home page loaded.</h1><br><hr></html>\n";
	int bodylen = strlen(body);


	char content[DATA_BUFSIZE];
	memset(content, '\0', DATA_BUFSIZE);
	sprintf_s(content, DATA_BUFSIZE, "HTTP/1.0 200 OK\nDate: Fri, 31 Dec 1999 23:59:59 GMT\nContent-Type: text/html\nContent-Length: %d\n\n%s", bodylen, body);

	sprintf_s(m_SocketInfo->BufferOut, DATA_BUFSIZE, "%s", content);
	m_SocketInfo->BytesSEND = strlen(m_SocketInfo->BufferOut);

}

void HttpServer::Handle404()
{
	memset(m_SocketInfo->BufferOut, '\0', DATA_BUFSIZE);
	const char* body = "<html><h1>KLARIS DID NOT FIND IT</h1><br><hr></html>\n";
	int bodylen = strlen(body);


	char content[DATA_BUFSIZE];
	memset(content, '\0', DATA_BUFSIZE);
	sprintf_s(content, DATA_BUFSIZE, "HTTP/1.0 404 OK\nDate: Fri, 31 Dec 1999 23:59:59 GMT\nContent-Type: text/html\nContent-Length: %d\n\n%s", bodylen, body);

	sprintf_s(m_SocketInfo->BufferOut, DATA_BUFSIZE, "%s", content);
	m_SocketInfo->BytesSEND = strlen(m_SocketInfo->BufferOut);

}

void HttpServer::EvaluateRoute(HttpHeader *httpHeader)
{
	//auto x = httpHeader->GetUrl();
	std::string nm(httpHeader->GetUrl());
	FUNC lpFunc = m_routes[nm];
	if (lpFunc != NULL) 
	{
		(this->*lpFunc)();
	}
	else
	{
		Handle404();
	}
}

void HttpServer::AddRoute(char *purl, FUNC lpFunc)
{
	//pair_t p(purl, lpFunc);
	//m_routes.push_back(p);
	m_routes[purl] = lpFunc;
}

void HttpServer::Request(LPSOCKET_INFORMATION pSocketInfo)
{
	printf("Recv:\n%s\n", pSocketInfo->DataBuf.buf);
	m_SocketInfo = pSocketInfo;

	httpHeader.Parse(pSocketInfo->DataBuf.buf);
	EvaluateRoute(&httpHeader);
	//pSocketInfo->BufferOut;

}