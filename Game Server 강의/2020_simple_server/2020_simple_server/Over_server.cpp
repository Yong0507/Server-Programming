//#include <iostream>
//#include <WS2tcpip.h>
//using namespace std;
//#pragma comment(lib, "Ws2_32.lib")
//#define MAX_BUFFER        1024
//#define SERVER_PORT       3500
//
//char messageBuffer[MAX_BUFFER];
//SOCKET client_socket;
//WSABUF wsabuf;
//
//void CALLBACK recv_complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flags);
//
//void CALLBACK send_complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flags)
//{
//	if (bytes > 0) 
//		printf("TRACE - Send message : %s (%d bytes)\n", messageBuffer, bytes);
//	else {
//		closesocket(client_socket);
//		return;
//	}
//
//	// 다시 Recv
//	wsabuf.len = MAX_BUFFER;
//	ZeroMemory(over, sizeof(*over));
//	int ret = WSARecv(client_socket, &wsabuf, 1, NULL, &flags, over, recv_complete);
//
//}
//
//void CALLBACK recv_complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flags)
//{
//	if (bytes > 0) {
//		messageBuffer[bytes] = 0;
//		cout << "TRACE - Receive message : " << messageBuffer << "(" << bytes << " bytes)\n";
//	}
//	else {
//		closesocket(client_socket);
//		return;
//	}
//
//	// 이제부터 반사해줘야함
//	
//	wsabuf.len = bytes; // 받은 만큼만 보낸다. 안그러면 1024바이트가 다 가버린다.
//	ZeroMemory(over, sizeof(*over)); // 초기화 과정 반드시 필요
//	int ret = WSASend(client_socket, &wsabuf, 1, NULL, NULL, over, send_complete);
//}
//
//int main()
//{
//	WSADATA WSAData;
//	WSAStartup(MAKEWORD(2, 0), &WSAData);
//
//	// SOCKET listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 0);
//	SOCKET listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
//	
//	SOCKADDR_IN serverAddr;
//	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
//	serverAddr.sin_family = AF_INET;
//	serverAddr.sin_port = htons(SERVER_PORT);
//	serverAddr.sin_addr.s_addr = INADDR_ANY;
//	::bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
//	listen(listenSocket, 5);
//	SOCKADDR_IN client_addr;
//
//	// 아래는 while(true)문 바깥에 선언해야한다
//	WSAOVERLAPPED overlapped;
//
//	while (true) {
//		int addr_size = sizeof(client_addr);
//		client_socket = accept(listenSocket, (sockaddr*)&client_addr, &addr_size);
//		wsabuf.buf = messageBuffer;
//		wsabuf.len = MAX_BUFFER;
//		DWORD flags = 0; // 0으로 초기화
//		ZeroMemory(&overlapped, sizeof(overlapped));
//		int ret = WSARecv(client_socket, &wsabuf, 1, NULL, &flags,
//			&overlapped, recv_complete);
//	}
//		// Receive는 루프를 돌면서 하는것이 아니라 단 1번만 해야함
//		closesocket(listenSocket);
//		WSACleanup();
//}
