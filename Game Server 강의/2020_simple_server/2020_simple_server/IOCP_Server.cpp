#include <iostream>
#include <WS2tcpip.h>
#include"protocol.h"
using namespace std;
#pragma comment(lib, "Ws2_32.lib")
constexpr int MAX_BUFFER = 4096;

constexpr char OP_MODE_RECV = 0;
constexpr char OP_MODE_SEND = 1;
constexpr char OP_MODE_ACCEPT = 2;

constexpr int KEY_SERVER = 1000000;

struct OVER_EX {
	WSAOVERLAPPED wsa_over;
	char op_mode;						// send인지 recv인지
	WSABUF wsa_buf;
	unsigned char iocp_buf[MAX_BUFFER];
};

struct client_info {
	int id;
	char name[MAX_ID_LEN];
	short x, y;

	SOCKET m_sock;
	OVER_EX m_recv_over;
	unsigned char* m_packet_start;
	unsigned char* m_recv_start;
};

client_info g_clients[MAX_USER]; 
HANDLE h_iocp;

void CALLBACK recv_complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flags);

void CALLBACK send_complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flags)
{
	if (bytes > 0) 
		printf("TRACE - Send message : %s (%d bytes)\n", messageBuffer, bytes);
	else {
		closesocket(client_socket);
		return;
	}

	// 다시 Recv
	wsabuf.len = MAX_BUFFER;
	ZeroMemory(over, sizeof(*over));
	int ret = WSARecv(client_socket, &wsabuf, 1, NULL, &flags, over, recv_complete);

}

void CALLBACK recv_complete(DWORD err, DWORD bytes, LPWSAOVERLAPPED over, DWORD flags)
{
	if (bytes > 0) {
		messageBuffer[bytes] = 0;
		cout << "TRACE - Receive message : " << messageBuffer << "(" << bytes << " bytes)\n";
	}
	else {
		closesocket(client_socket);
		return;
	}

	// 이제부터 반사해줘야함
	
	wsabuf.len = bytes; // 받은 만큼만 보낸다. 안그러면 1024바이트가 다 가버린다.
	ZeroMemory(over, sizeof(*over)); // 초기화 과정 반드시 필요
	int ret = WSASend(client_socket, &wsabuf, 1, NULL, NULL, over, send_complete);
}


void process_recv(int id, DWORD iosize) 
{
	//패킷 재조립 필요, 패킷 사이즈를 알아야 함
	unsigned char p_size = g_clients[id].m_packet_start[0];
	unsigned char* next_recv_ptr = g_clients[id].m_recv_start + iosize;
	// 패킷을 만들 수 있으면 루프를 돌아라
	while (p_size <= next_recv_ptr - g_clients[id].m_packet_start) 
	{
		process_packet(id);
		g_clients[id].m_packet_start += p_size;
		if (g_clients[id].m_packet_start < next_recv_ptr)
			p_size = g_clients[id].m_packet_start[0];
		else
			break;
	}

	int left_data = next_recv_ptr - g_clients[id].m_packet_start;

	if ((MAX_BUFFER - (next_recv_ptr - g_clients[id].m_recv_over.iocp_buf) 
		< MIN_BUFF_SIZE))  	{
		memcpy(g_clients[id].m_recv_over.iocp_buf,
			g_clients[id].m_packet_start, left_data);
		g_clients[id].m_packet_start = g_clients[id].m_recv_over.iocp_buf;
		g_clients[id].m_recv_start = g_clients[id].m_packet_start + left_data;
	}
	DWORD recv_flag = 0;
	WSARecv(g_clients[id].m_sock, &g_clients[id].m_recv_over.wsa_buf,
		1, NULL, &recv_flag, &g_clients[id].m_recv_over.wsa_over, NULL);

}


int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	h_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);   // iocp 생성
	SOCKET listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	CreateIoCompletionPort(listenSocket, h_iocp, KEY_SERVER, 0);		   // iocp에 등록
	
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	::bind(listenSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
	listen(listenSocket, 5);
	SOCKADDR_IN client_addr;
	WSAOVERLAPPED overlapped;
	// 여기서 Accept 해야함 AcceptEx 사용할 것
	// AcceptEx()
	while (true) {
		DWORD io_size;
		ULONG_PTR key;
		WSAOVERLAPPED* lpover;  // 오버랩트 구조체 포인터 필요
		int ret = GetQueuedCompletionStatus(h_iocp, &io_size, &key, &lpover, INFINITE);
		
		OVER_EX* over_ex = reinterpret_cast<OVER_EX *>(lpover);
		switch(over_ex->op_mode) {
			case OP_MODE_ACCEPT:
				add_new_client(client_socket);
				break;
			case OP_MODE_RECV:
				process_recv(key, io_size);
				break;
			case OP_MODE_SEND:
				delete over_ex;
				break;
		}

	}
		closesocket(listenSocket);
		WSACleanup();
}
