/*

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF

  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO

  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A

  PARTICULAR PURPOSE.

 

    This is "Sample Code" and is distributable subject to the terms of the end user license agreement.

*/
///////////////////////////////////////////////////////////////////////////////
//
// TIMESERVER.CPP
//
// Simple Server app that mimics the functionality of RFC 868
//

#include <stdio.h>
#include <winsock.h>
#include <time.h>

#define RFC_ADJUSTMENT  2208988800  // seconds from Jan 1, 1900 - Jan 1, 1970


static SOCKET InitListener(void)
{
	WSADATA wsaData;

	if(!WSAStartup(MAKEWORD(1, 1), &wsaData))
	{
		SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if(INVALID_SOCKET != sock)
		{
			struct sockaddr_in addr;

			// set up the structure to bind the socket to the Time Server port
			ZeroMemory(&addr, sizeof(addr));
			addr.sin_family = AF_INET;
			addr.sin_port = htons(IPPORT_TIMESERVER);
			addr.sin_addr.s_addr = htonl(INADDR_ANY);
			
			if(SOCKET_ERROR != bind(sock, (struct sockaddr *)&addr, sizeof(addr)))
			{
				// listen to the socket for connections
				if(SOCKET_ERROR != listen(sock, 10))
				{
					return sock;
				}

				printf("TIMESERVER: can't listen - error %d\n", WSAGetLastError());

			}
			else
			{
				printf("TIMESERVER: can't bind - error %d\n", WSAGetLastError());
			}

			closesocket(sock);
		}
		else
		{
			printf("TIMESERVER: can't open TCP socket - error %d\n", WSAGetLastError());
		}

		WSACleanup();
	}
	else
	{
		printf("TIMESERVER: can't init Winsock!\n");
	}

	return INVALID_SOCKET;
}


static void EndListener(SOCKET listener)
{
	// close the socket and cleanup Winsock
	closesocket(listener);
	WSACleanup();
}


int main(int argc, char *argv[])
{
	SOCKET server, client;

	// setup the Time Server
	server = InitListener();
	if(INVALID_SOCKET != server)
	{
		UINT connections;

		// loop forever
		for(connections = 0; ; connections++)
		{
			union
			{
				char buf[4];
				time_t t;
			} mytime;

			// wait for an incoming connection
			client = accept(server, NULL, NULL);
			if(INVALID_SOCKET == client)
			{
				printf("TIMESERVER: can't accept - error %d\n", WSAGetLastError());
				break;
			}

			printf("Got connection number %u\n", connections);

			// get time in seconds since 1970
			time(&mytime.t);

			// time server must report time in seconds since 1900
			mytime.t += RFC_ADJUSTMENT;

			// convert the bytes to network order and send them to the client
			mytime.t = htonl(mytime.t);
			send(client, mytime.buf, 4, 0);

			// close the client socket connection
			printf("Closing connection\n");
			closesocket(client);
		}

		EndListener(server);
	}

	return 0;
}

