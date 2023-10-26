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

	clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
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
		char		sendBuffer[100] = "hello world";
		int			error;

		error = send(clientSocket, sendBuffer, std::size(sendBuffer), 0);
		if (error == SOCKET_ERROR)
		{
			std::cout << "send() is failed. " << "code : " << WSAGetLastError() << std::endl;
			return 0;
		}

		std::cout << "send : " << sendBuffer << std::endl;

		char		receiveBuffer[100];
		int			byte;

		byte = recv(clientSocket, receiveBuffer, std::size(receiveBuffer), 0);
		if (byte <= 0)
		{
			std::cout << "recv() is failed. " << "code : " << WSAGetLastError() << std::endl;
			return 0;
		}

		std::cout << "receive : " << receiveBuffer << std::endl;

		std::this_thread::sleep_for(1s);
	}


	// 4. Release 
	closesocket(clientSocket);
	WSACleanup();

	return 0;
}