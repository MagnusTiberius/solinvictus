#include "HttpHeader.h"


HttpHeader::HttpHeader()
{
}


HttpHeader::~HttpHeader()
{
}


void HttpHeader::Parse(char* content)
{
	char buf1[DATA_BUFSIZE];
	ZeroMemory(buf1, DATA_BUFSIZE);
	int buf1_ptr = 0;
	int len = strlen(content);
	i = 0;
	char c = content[i];
	while (c != '\0')
	{
		if (c == '\r')
		{
			c = content[++i];
			continue;
		}
		if (c == '\n')
		{
			if (strlen(buf1)==0)
			{
				// header parsing is complete.
				return;
			}

			if (m_ps == PSTATE_URL) // url detected
			{
				printf("method found: %s\n", buf1);
				ZeroMemory(m_httpVer, DATA_BUFSIZE);
				sprintf_s(m_httpVer, DATA_BUFSIZE, "%s", buf1);
				ZeroMemory(buf1, DATA_BUFSIZE);
				m_ps = PSTATE_HTTP_VER;
				c = content[++i];
				buf1_ptr = 0;
				continue;
			}
			
			if (m_ps == PSTATE_HOST_DETECTED) 
			{
				printf("host value: %s\n", buf1);
				ZeroMemory(m_host, DATA_BUFSIZE);
				sprintf_s(m_host, DATA_BUFSIZE, "%s", buf1);
				ZeroMemory(buf1, DATA_BUFSIZE);
				m_ps = PSTATE_HOST_VALUE;
				c = content[++i];
				buf1_ptr = 0;
				continue;
			}
			if (m_ps == PSTATE_CONNECTION_DETECTED)
			{
				printf("connection value: %s\n", buf1);
				ZeroMemory(m_connection, DATA_BUFSIZE);
				sprintf_s(m_connection, DATA_BUFSIZE, "%s", buf1);
				ZeroMemory(buf1, DATA_BUFSIZE);
				m_ps = PSTATE_CONNECTION_VALUE;
				c = content[++i];
				buf1_ptr = 0;
				continue;
			}

		}
		if (c == ' ')
		{
			if (strcmp(buf1, "GET") == 0) // method detected
			{
				printf("method found: %s\n", buf1);
				ZeroMemory(buf1, DATA_BUFSIZE);
				buf1_ptr = 0;
				m_method = HTTP_GET;
				m_ps = PSTATE_GET;
				c = content[++i];
				continue;
			}
			if (m_ps == PSTATE_GET) // url detected
			{
				printf("method found: %s\n", buf1);
				ZeroMemory(m_url, DATA_BUFSIZE);
				sprintf_s(m_url, DATA_BUFSIZE, "%s", buf1);
				ZeroMemory(buf1, DATA_BUFSIZE);
				m_ps = PSTATE_URL;
				c = content[++i];
				buf1_ptr = 0;
				continue;
			}
			c = content[++i];
			continue;
		}
		if (c == ':')
		{
			if (strcmp(buf1, "Host") == 0) // method detected
			{
				m_ps = PSTATE_HOST_DETECTED;
				printf("header element: %s\n", buf1);
				ZeroMemory(buf1, DATA_BUFSIZE);
				c = content[++i];
				buf1_ptr = 0;
				continue;
			}
			if (strcmp(buf1, "Connection") == 0) // method detected
			{
				m_ps = PSTATE_CONNECTION_DETECTED;
				printf("header element: %s\n", buf1);
				ZeroMemory(buf1, DATA_BUFSIZE);
				c = content[++i];
				buf1_ptr = 0;
				continue;
			}
		}

		buf1[buf1_ptr++] = c;

		i = i + 1;
		c = content[i];
	}
}

int HttpHeader::Method()
{
	return 0;
}

bool HttpHeader::Url(char *urlval)
{
	return true;
}


char* HttpHeader::GetUrl()
{
	return m_url;
}