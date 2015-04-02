#pragma once
#include "SocketCompletionPortServer.h"


class IocpHttpd : public SocketCompletionPortServer
{
public:
	IocpHttpd();
	~IocpHttpd();

	void EvalGet(HttpRequest *httpRequest, HttpResponse *httpResponse);
	void EvalPost(HttpRequest *httpRequest, HttpResponse *httpResponse);

	static void HandleHome(HttpRequest *httpRequest, HttpResponse *httpResponse);
	static void HandleTest(HttpRequest *httpRequest, HttpResponse *httpResponse);
	static void HandleInit(HttpRequest *httpRequest, HttpResponse *httpResponse);

private:
	DWORD dwThreadId;

};

