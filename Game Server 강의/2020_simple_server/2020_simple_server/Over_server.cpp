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
//	// �ٽ� Recv
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
//	// �������� �ݻ��������
//	
//	wsabuf.len = bytes; // ���� ��ŭ�� ������. �ȱ׷��� 1024����Ʈ�� �� ��������.
//	ZeroMemory(over, sizeof(*over)); // �ʱ�ȭ ���� �ݵ�� �ʿ�
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
//	// �Ʒ��� while(true)�� �ٱ��� �����ؾ��Ѵ�
//	WSAOVERLAPPED overlapped;
//
//	while (true) {
//		int addr_size = sizeof(client_addr);
//		client_socket = accept(listenSocket, (sockaddr*)&client_addr, &addr_size);
//		wsabuf.buf = messageBuffer;
//		wsabuf.len = MAX_BUFFER;
//		DWORD flags = 0; // 0���� �ʱ�ȭ
//		ZeroMemory(&overlapped, sizeof(overlapped));
//		int ret = WSARecv(client_socket, &wsabuf, 1, NULL, &flags,
//			&overlapped, recv_complete);
//	}
//		// Receive�� ������ ���鼭 �ϴ°��� �ƴ϶� �� 1���� �ؾ���
//		closesocket(listenSocket);
//		WSACleanup();
//}
