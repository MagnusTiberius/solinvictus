#pragma once
class HttpRequest
{
public:
	HttpRequest();
	~HttpRequest();

	void Parse(char *content);

};

