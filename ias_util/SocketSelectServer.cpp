#include "SocketSelectServer.h"


SocketSelectServer::SocketSelectServer()
{
}


SocketSelectServer::~SocketSelectServer()
{
}

int SocketSelectServer::Init(u_short portnum)
{
	SOCKET ListenSocket;
	SOCKET AcceptSocket;
	SOCKADDR_IN InternetAddr;
	WSADATA wsaData;
	INT Ret;
	FD_SET WriteSet;
	FD_SET ReadSet;
	DWORD i;
	DWORD Total;
	ULONG NonBlock;
	DWORD Flags;
	DWORD SendBytes;
	DWORD RecvBytes;

	if ((Ret = WSAStartup(0x0202, &wsaData)) != 0)
	{
		printf("WSAStartup() failed with error %d\n", Ret);
		WSACleanup();
		return 1;
	}
	else
		printf("WSAStartup() is fine!\n");

	// Prepare a socket to listen for connections
	if ((ListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		printf("WSASocket() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("WSASocket() is OK!\n");

	InternetAddr.sin_family = AF_INET;
	InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (portnum > 1024) {
		InternetAddr.sin_port = htons(portnum);
	}
	else {
		InternetAddr.sin_port = htons(PORT);
	}

	if (bind(ListenSocket, (PSOCKADDR)&InternetAddr, sizeof(InternetAddr)) == SOCKET_ERROR)
	{
		printf("bind() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("bind() is OK!\n");

	if (listen(ListenSocket, 5))
	{
		printf("listen() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("listen() is OK!\n");

	// Change the socket mode on the listening socket from blocking to
	// non-block so the application will not block waiting for requests
	NonBlock = 1;
	if (ioctlsocket(ListenSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
	{
		printf("ioctlsocket() failed with error %d\n", WSAGetLastError());
		return 1;
	}
	else
		printf("ioctlsocket() is OK!\n");

	while (TRUE)
	{
		// Prepare the Read and Write socket sets for network I/O notification
		FD_ZERO(&ReadSet);
		FD_ZERO(&WriteSet);

		// Always look for connection attempts
		FD_SET(ListenSocket, &ReadSet);

		// Set Read and Write notification for each socket based on the
		// current state the buffer.  If there is data remaining in the
		// buffer then set the Write set otherwise the Read set

		for (i = 0; i < TotalSockets; i++)
			if (SocketArray[i]->BytesSEND > 0) 
			{
				FD_SET(SocketArray[i]->Socket, &WriteSet);
			}
			else 
			{
				FD_SET(SocketArray[i]->Socket, &ReadSet);
			}
		/*
		for (i = 0; i < TotalSockets; i++)
		{
			if (SocketArray[i]->BytesRECV > 0)
			{
				FD_SET(SocketArray[i]->Socket, &ReadSet);
			}
			if (SocketArray[i]->BytesSEND > 0)
			{
				FD_SET(SocketArray[i]->Socket, &WriteSet);
			}
		}
		*/

		if ((Total = select(0, &ReadSet, &WriteSet, NULL, NULL)) == SOCKET_ERROR)
		{
			printf("select() returned with error %d\n", WSAGetLastError());
			return 1;
		}
		else
			printf("select() is OK!\n");

		// Check for arriving connections on the listening socket.
		if (FD_ISSET(ListenSocket, &ReadSet))
		{
			Total--;
			if ((AcceptSocket = accept(ListenSocket, NULL, NULL)) != INVALID_SOCKET)
			{
				// Set the accepted socket to non-blocking mode so the server will
				// not get caught in a blocked condition on WSASends
				NonBlock = 1;
				if (ioctlsocket(AcceptSocket, FIONBIO, &NonBlock) == SOCKET_ERROR)
				{
					printf("ioctlsocket(FIONBIO) failed with error %d\n", WSAGetLastError());
					return 1;
				}
				else
					printf("ioctlsocket(FIONBIO) is OK!\n");

				if (CreateSocketInformation(AcceptSocket) == FALSE)
				{
					printf("CreateSocketInformation(AcceptSocket) failed!\n");
					return 1;
				}
				else
					printf("CreateSocketInformation() is OK!\n");

			}
			else
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					printf("accept() failed with error %d\n", WSAGetLastError());
					return 1;
				}
				else
					printf("accept() is fine!\n");
			}
		}

		// Check each socket for Read and Write notification until the number
		// of sockets in Total is satisfied
		for (i = 0; Total > 0 && i < TotalSockets; i++)
		{
			LPSOCKET_INFORMATION SocketInfo = SocketArray[i];

			// If the ReadSet is marked for this socket then this means data
			// is available to be read on the socket
			if (FD_ISSET(SocketInfo->Socket, &ReadSet))
			{
				Total--;

				SocketInfo->DataBuf.buf = SocketInfo->Buffer;
				SocketInfo->DataBuf.len = DATA_BUFSIZE;

				Flags = 0;
				if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes, &Flags, NULL, NULL) == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						printf("WSARecv() failed with error %d\n", WSAGetLastError());
						FreeSocketInformation(i);
					}
					else
						printf("WSARecv() is OK!\n");
					continue;
				}
				else
				{
					SocketInfo->BytesRECV = RecvBytes;

					// If zero bytes are received, this indicates the peer closed the connection.
					if (RecvBytes == 0)
					{
						FreeSocketInformation(i);
						continue;
					}
					else
					{
						Request(SocketInfo);
					}
				}
			}

			// If the WriteSet is marked on this socket then this means the internal
			// data buffers are available for more data
			if (FD_ISSET(SocketInfo->Socket, &WriteSet))
			{
				Total--;

				//SocketInfo->DataBufOut.buf = SocketInfo->BufferOut + SocketInfo->BytesSEND;
				//SocketInfo->DataBufOut.len = SocketInfo->BytesRECV - SocketInfo->BytesSEND;
				SocketInfo->DataBufOut.buf = SocketInfo->BufferOut;
				SocketInfo->DataBufOut.len = strlen(SocketInfo->BufferOut);

				if (WSASend(SocketInfo->Socket, &(SocketInfo->DataBufOut), 1, &SendBytes, 0, NULL, NULL) == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						printf("WSASend() failed with error %d\n", WSAGetLastError());
						FreeSocketInformation(i);
					}
					else
						printf("WSASend() is OK!\n");

					continue;
				}
				else
				{
					printf("Sent:OK\n%s\n", SocketInfo->BufferOut);
					SocketInfo->BytesSEND -= SendBytes;

					//if (SocketInfo->BytesSEND == SocketInfo->BytesRECV)
					//{
					//	SocketInfo->BytesSEND = 0;
					//	SocketInfo->BytesRECV = 0;
					//}
				}
			}
		}
	}
}

void SocketSelectServer::Request(LPSOCKET_INFORMATION pSocketInfo)
{
	//printf("Recv:\n%s\n", pSocketInfo->DataBuf.buf);

	//pSocketInfo->BufferOut;

	//memset(pSocketInfo->BufferOut, '\0', DATA_BUFSIZE);
	//const char* body = "<html><h1>KLARIS WEB SERVER IS UP</h1><br><hr></html>\n";
	//int bodylen = strlen(body);


	//char content[DATA_BUFSIZE];
	//memset(content, '\0', DATA_BUFSIZE);
	//sprintf_s(content, DATA_BUFSIZE, "HTTP/1.0 200 OK\nDate: Fri, 31 Dec 1999 23:59:59 GMT\nContent-Type: text/html\nContent-Length: %d\n\n%s", bodylen, body);

	//sprintf_s(pSocketInfo->BufferOut, DATA_BUFSIZE, "%s", content);
	//pSocketInfo->BytesSEND = strlen(pSocketInfo->BufferOut);

}




BOOL SocketSelectServer::CreateSocketInformation(SOCKET s)
{
	LPSOCKET_INFORMATION SI;

	printf("Accepted socket number %d\n", s);

	if ((SI = (LPSOCKET_INFORMATION)GlobalAlloc(GPTR, sizeof(SOCKET_INFORMATION))) == NULL)
	{
		printf("GlobalAlloc() failed with error %d\n", GetLastError());
		return FALSE;
	}
	else
		printf("GlobalAlloc() for SOCKET_INFORMATION is OK!\n");

	// Prepare SocketInfo structure for use
	SI->Socket = s;
	SI->BytesSEND = 0;
	SI->BytesRECV = 0;

	SocketArray[TotalSockets] = SI;


	{
		LPCONNECTED_ENTITY_INFORMATION EI;
		if ((EI = (LPCONNECTED_ENTITY_INFORMATION)GlobalAlloc(GPTR, sizeof(CONNECTED_ENTITY_INFORMATION))) == NULL)
		{
			printf("GlobalAlloc() failed with error %d\n", GetLastError());
			return FALSE;
		}
		else
			printf("GlobalAlloc() for CONNECTED_ENTITY_INFORMATION is OK!\n");
		//
		ConnectedEntityArray[TotalSockets] = EI;
	}

	TotalSockets++;

	return(TRUE);
}

void SocketSelectServer::FreeSocketInformation(DWORD Index)
{
	LPCONNECTED_ENTITY_INFORMATION EI = ConnectedEntityArray[Index];
	GlobalFree(EI);

	LPSOCKET_INFORMATION SI = SocketArray[Index];
	DWORD i;

	closesocket(SI->Socket);
	printf("Closing socket number %d\n", SI->Socket);
	GlobalFree(SI);

	// Squash the socket array
	for (i = Index; i < TotalSockets; i++)
	{
		SocketArray[i] = SocketArray[i + 1];
		ConnectedEntityArray[i] = ConnectedEntityArray[i + 1];
	}

	TotalSockets--;
}
