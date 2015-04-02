#include "IocpHttpd.h"


IocpHttpd::IocpHttpd()
{
	dwThreadId = GetCurrentThreadId();
	AddRoute("/", IocpHttpd::HandleHome);
	AddRoute("/test", IocpHttpd::HandleTest);
	AddRoute("/init", IocpHttpd::HandleInit);
}


IocpHttpd::~IocpHttpd()
{
}

void IocpHttpd::EvalGet(HttpRequest *httpRequest, HttpResponse *httpResponse)
{
	printf("%d::IocpHttpd::EvalGet\n", dwThreadId);
}

void IocpHttpd::EvalPost(HttpRequest *httpRequest, HttpResponse *httpResponse)
{
	printf("%d::IocpHttpd::EvalPost\n", dwThreadId);
}

void IocpHttpd::HandleHome(HttpRequest *httpRequest, HttpResponse *httpResponse)
{
	DWORD dwThreadId = GetCurrentThreadId();
	printf("%d::IocpHttpd::HandleHome\n", dwThreadId);
	httpResponse->Write("<html><h1>Test Home</h1><hr></html>");
}

void IocpHttpd::HandleTest(HttpRequest *httpRequest, HttpResponse *httpResponse)
{
	DWORD dwThreadId = GetCurrentThreadId();
	printf("%d::IocpHttpd::HandleTest\n", dwThreadId);
	httpResponse->Write("<html><h1>Test Test</h1><hr></html>");
}

void IocpHttpd::HandleInit(HttpRequest *httpRequest, HttpResponse *httpResponse)
{
	DWORD dwThreadId = GetCurrentThreadId();
	printf("%d::IocpHttpd::HandleInit\n", dwThreadId);
	httpResponse->Write("<html><h1>Test Init</h1><hr></html>");
}
