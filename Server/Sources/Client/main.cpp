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
	SOCKET					clientSocket;
	SOCKADDR_IN				serverAddress;
	int						error;


	// 1. Create socket
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		std::cout << "WSAStartup() is failed. " << "code : " << WSAGetLastError() << std::endl;
		return 0;
	}

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		std::cout << "socket() is failed. " << "code : " << WSAGetLastError() << std::endl;
		return 0;
	}

	// 2. Set server address.
	memset(&serverAddress, 0, sizeof(SOCKADDR_IN));
	{
		serverAddress.sin_family = AF_INET;
		inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
		serverAddress.sin_port = htons(7777);
	}

	// 3. Connect to server.
	error = connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress));
	if (error == SOCKET_ERROR)
	{
		std::cout << "connect() is failed. " << "code : " << WSAGetLastError() << std::endl;
		return 0;
	}

	std::cout << "Server is connected." << std::endl;


	while (true)
	{
		std::this_thread::sleep_for(1s);
	}


	// 4. Release 
	closesocket(clientSocket);
	WSACleanup();

	return 0;
}