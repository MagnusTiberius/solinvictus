#pragma once
#include <map>
#include <vector>

class HttpUrlRoute
{
public:
	HttpUrlRoute();
	~HttpUrlRoute();

	typedef std::pair<char*, void*> ROUTEURL;

	typedef std::vector<ROUTEURL> ROUTEMAP;
	typedef ROUTEMAP::iterator ROUTEMAPITERATOR;

	void AddRoute(char *url, void* lpFunc);
	void* GetRoute(char* url);
private:
	ROUTEMAP urlRoutes;
};

