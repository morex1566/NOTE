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
	SOCKET					serverSocket;
	SOCKADDR_IN				serverAddress;
	int						error;


	// 1. Create socket
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		std::cout << "WSAStartup() is failed. " << "code : " << WSAGetLastError() << std::endl;
		return 0;
	}

	serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (serverSocket == INVALID_SOCKET)
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
	error = bind(serverSocket, reinterpret_cast<const sockaddr*>(&serverAddress), sizeof(serverAddress));
	if (error == SOCKET_ERROR)
	{
		std::cout << "bind() is failed. " << "code : " << WSAGetLastError() << std::endl;
		return 0;
	}

	// 5. Accept
	while (true)
	{
		SOCKADDR_IN			clientAddress;
		int					addressLenght = sizeof(clientAddress);
		int					byte;
		char				recevieBuffer[100];

		memset(&clientAddress, 0, sizeof(clientAddress));

		byte = recvfrom(serverSocket, recevieBuffer, sizeof(recevieBuffer), 0, reinterpret_cast<sockaddr*>(&clientAddress), &addressLenght);
		if (byte <= 0)
		{
			std::cout << "recvfrom() is failed. " << "code : " << WSAGetLastError() << std::endl;
			return 0;
		}
		
		std::cout << "receive : " << recevieBuffer << std::endl;

		sendto(serverSocket, recevieBuffer, sizeof(recevieBuffer), 0, reinterpret_cast<sockaddr*>(&clientAddress), addressLenght);
		if (error == SOCKET_ERROR)
		{
			std::cout << "sendto() is failed. " << "code : " << WSAGetLastError() << std::endl;
			return 0;
		}

		std::cout << "send : " << recevieBuffer << std::endl;
	}



	// 6. Release 
	closesocket(serverSocket);
	WSACleanup();

	return 0;
}