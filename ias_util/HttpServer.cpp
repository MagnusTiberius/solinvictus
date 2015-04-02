#include "HttpServer.h"

HttpServer::~HttpServer() {}

HttpServer::HttpServer()
{
}

void HttpServer::EvaluateRoute(HttpHeader *httpHeader)
{
	LP_MEM_FUNC lpFunc = m_routes[std::string(httpHeader->GetUrl())];
	if (lpFunc != NULL) 
		(this->*lpFunc)();
	else
		Handle404();
}



void HttpServer::Handle404()
{
	const char* body = "<html><h1>KLARIS DID NOT FIND IT</h1><br><hr></html>\n";
	int bodylen = strlen(body);
	char content[DATA_BUFSIZE];

	memset(m_SocketInfo->BufferOut, '\0', DATA_BUFSIZE);
	memset(content, '\0', DATA_BUFSIZE);
	sprintf_s(content, DATA_BUFSIZE, "HTTP/1.0 404 OK\nDate: Fri, 31 Dec 1999 23:59:59 GMT\nContent-Type: text/html\nContent-Length: %d\n\n%s", bodylen, body);
	sprintf_s(m_SocketInfo->BufferOut, DATA_BUFSIZE, "%s", content);
	m_SocketInfo->BytesSEND = strlen(m_SocketInfo->BufferOut);
}

void HttpServer::AddRoute(char *purl, LP_MEM_FUNC lpFunc)
{
	m_routes[purl] = lpFunc;
}


void HttpServer::Request(LPSOCKET_INFORMATION pSocketInfo)
{
	fprintf(stderr, "Recv:\n%s\n", pSocketInfo->DataBuf.buf);
	server << pSocketInfo->DataBuf.buf;
	std::string msgout;
	server >> msgout;
	sprintf_s(m_SocketInfo->BufferOut, DATA_BUFSIZE, "%s", msgout.c_str());
	m_SocketInfo->BytesSEND = strlen(m_SocketInfo->BufferOut);

	//m_SocketInfo = pSocketInfo;
	//httpHeader.Parse(pSocketInfo->DataBuf.buf);
	//EvaluateRoute(&httpHeader);
}