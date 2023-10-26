#include <iostream>
#include <WinSock2.h>
#include <MSWSock.h>
#include <thread>
#include <WS2tcpip.h>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")

using namespace std::chrono;

int main()
{
	WSADATA					wsaData;
	SOCKET					listenSocket;
	SOCKADDR_IN				serverAddress;
	int						error;


	// 1. Create socket
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		std::cout << "WSAStartup() is failed. " << "code : " << WSAGetLastError() << std::endl;
		return 0;
	}

	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		std::cout << "socket() is failed. " << "code : " << WSAGetLastError() << std::endl;
		return 0;
	}

	// 2. Set server address.
	memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
	{
		serverAddress.sin_family = AF_INET;
		serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
		serverAddress.sin_port = htons(7777);
	}

	// 3. Bind server address
	error = bind(listenSocket, reinterpret_cast<const sockaddr*>(&serverAddress), sizeof(serverAddress));
	if (error == SOCKET_ERROR)
	{
		std::cout << "bind() is failed. " << "code : " << WSAGetLastError() << std::endl;
		return 0;
	}

	// 4. Listen
	// backlog = queue size
	error = listen(listenSocket, 10);
	if (error == SOCKET_ERROR)
	{
		std::cout << "listen() is failed. " << "code : " << WSAGetLastError() << std::endl;
	}

	// 5. Accept
	while(true)
	{
		SOCKADDR_IN			clientAddress;
		int					addressLen;
		SOCKET				clientSocket;

		addressLen = sizeof(clientAddress);
		clientSocket = accept(listenSocket, reinterpret_cast<sockaddr*>(&clientAddress), &addressLen);
		if (clientSocket == INVALID_SOCKET)
		{
			std::cout << "accept() is failed. " << "code : " << WSAGetLastError() << std::endl;
			return 0;
		}

		char clientIP[20];
		inet_ntop(AF_INET, &clientAddress.sin_addr, clientIP, sizeof(clientIP));
		std::cout << "client ip address : " << clientIP << std::endl;


		while(true)
		{
			char		receiveBuffer[100];
			int			byte;

			byte = recv(clientSocket, receiveBuffer, std::size(receiveBuffer), 0);
			if ( byte <= 0 )
			{
				std::cout << "recv() is failed. " << "code : " << WSAGetLastError() << std::endl;
				return 0;
			}

			std::cout << "receive : " << receiveBuffer << std::endl;

			char		sendBuffer[100] = "hello world";
			int			error;

			error = send(clientSocket, sendBuffer, std::size(sendBuffer), 0);
			if (error == SOCKET_ERROR)
			{
				std::cout << "send() is failed. " << "code : " << WSAGetLastError() << std::endl;
				return 0;
			}

			std::cout << "send : " << receiveBuffer << std::endl;

		}
	}



	// 6. Release 
	closesocket(listenSocket);
	WSACleanup();

	return 0;
}