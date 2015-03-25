#pragma once
// Link to ws2_32.lib
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#define PORT 5150
#define DATA_BUFSIZE 8192

class SocketEventSelectServer
{
public:
	SocketEventSelectServer();
	~SocketEventSelectServer();

	typedef struct _SOCKET_INFORMATION {
		CHAR Buffer[DATA_BUFSIZE];
		WSABUF DataBuf;
		SOCKET Socket;
		DWORD BytesSEND;
		DWORD BytesRECV;
	} SOCKET_INFORMATION, *LPSOCKET_INFORMATION;


	DWORD EventTotal = 0;
	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];
	LPSOCKET_INFORMATION SocketArray[WSA_MAXIMUM_WAIT_EVENTS];

	int Start();
	BOOL CreateSocketInformation(SOCKET s);
	void FreeSocketInformation(DWORD Event);
};

