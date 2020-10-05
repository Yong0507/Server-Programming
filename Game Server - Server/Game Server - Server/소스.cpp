//// ------------------------------9.27------------------------------------------
//// Ŭ���̾�Ʈ�� ���� ��� SOCKETINFO ����ü�� �̿��� Overlapped I/O Callback
//// ��ε�ĳ���� �۾��� �ϱ� ���� �ʱ� �۾���
//// vector�� �̿��� ������ ��� Ŭ���̾�Ʈ���� Send �ϵ��� �� ����
//
//#include <iostream>
//#include <vector>
//#include <map>
//#include <WS2tcpip.h>
//#include "protocol.h"
//#pragma comment (lib,"WS2_32.LIB")
//using namespace std;
//
//constexpr int MAX_BUFFER = 1024;
//constexpr short PORT = 3500;
//
//void err_disp(const char* msg)
//{
//	LPVOID lpMsgBuf;
//	FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, WSAGetLastError(),
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(LPTSTR)&lpMsgBuf, 0, NULL);
//	printf("[%s] %s", msg, (char*)lpMsgBuf);
//	printf("%d", WSAGetLastError());
//	LocalFree(lpMsgBuf);
//}
//
//#pragma pack(1)
//typedef struct Player
//{
//	unsigned int width;
//	unsigned int height;
//	unsigned int num;
//	int ID;
//} Player;
//#pragma pack()
//
//Player player;
//
//struct SOCKETINFO 
//{
//	WSAOVERLAPPED overlapped;
//	WSABUF dataBuffer;
//	SOCKET socket;
//	unsigned int x;
//	unsigned int y;
//	char messageBuffer[MAX_BUFFER];
//	char id;
//};
//
//map<int, SOCKETINFO* > clients;
//
//void CALLBACK recv_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags);
//void CALLBACK send_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags_);
//void ProcessPacket(void* buf);
//
//void ProcessPacket(void* buf) 
//{
//
//
//}
//
//void CALLBACK recv_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags)
//{
//	int id = reinterpret_cast<int>(overlapped->hEvent);
//
//	CS_MOVE_packet cs_move_packet{};
//	CS_Enter cs_packet_enter{};
//
//	SC_MOVE_packet sc_move_packet{};
//	SC_Enter sc_packet_enter{};
//	
//	SOCKETINFO socketInfo{};
//
//	// Ŭ���̾�Ʈ���� CS_ENTER �޾��� ����
//	// Ŭ���̾�Ʈ���� CS_MOVE_PACKET �޾��� ����
//	// SOCKETINFO[Ŭ���̾�ƮID] �� messageBuffe�� [1] == type�� Ȯ���Ѵ�
//	
//	switch (clients[id]->messageBuffer[1]) 
//	{
//		case CS_ENTER:
//		{
//			break;
//		}
//		case CS_MOVE:
//		{
//			cs_move_packet.dir = clients[id]->messageBuffer[2];
//			if (cs_move_packet.dir == KEY_DOWN) 
//			{
//				sc_move_packet.height += 50; 
//			}
//			else if (cs_move_packet.dir == KEY_UP) 
//			{ 
//				sc_move_packet.height -= 50; 
//			}
//			else if (cs_move_packet.dir == KEY_LEFT) 
//			{ 
//				sc_move_packet.width -= 50; 
//			}
//			else if (cs_move_packet.dir == KEY_RIGHT) 
//			{ 
//				sc_move_packet.width += 50; 
//			}
//
//			send(clients[id]->socket, (char*)&sc_move_packet, sizeof(sc_move_packet),0);
//			// � Ű�� ���ȳ� Ȯ���Ѵ�.
//			// if ( packet.dir == KEY_UP)
//			//		�ش� �������� X, Y ���� �����Ѵ�.
//			//		���� ���� ����ü�� ������Ʈ�� ��ǥ�� �����Ѵ�.
//			//		�������ִ� ��� Ŭ���̾�Ʈ�鿡�� sc_move_packet�� �����Ѵ�.
//			// else if ( ... == KEY_DOWN)
//			break;
//		}
//
//		default:
//		{
//			cout << "Unknown Packet Type Error!" << endl;
//			while (1);
//			break;
//		}
//
//	}
//
//	if (dataBytes == 0) 
//	{
//		closesocket(clients[id]->socket);
//		clients.erase(id);
//		return;
//	}
//
//	//clients[id]->messageBuffer[dataBytes] = 0;
//	//cout << "From client : " << clients[id]->messageBuffer << " (" << dataBytes << " ) bytes" << endl;
//	//clients[id]->dataBuffer.len = dataBytes;
//	//memset(&(clients[id]->overlapped), 0, sizeof(OVERLAPPED));
//	//clients[id]->overlapped.hEvent = (HANDLE)id;
//	//int ret = WSASend(clients[id]->socket, &(clients[id]->dataBuffer), 1, &dataBytes, 0, &(clients[id]->overlapped), send_callback);
//	//if (ret == SOCKET_ERROR) 
//	//{
//	//	if (WSAGetLastError() != WSA_IO_PENDING) {
//	//		err_disp("WSARecv()");
//	//	}
//	//}
//}
//
//void CALLBACK send_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags)
//{
//	//DWORD receiveBytes = 0;
//
//	//int id = reinterpret_cast<int>(overlapped->hEvent);
//
//	//if (dataBytes == 0) 
//	//{
//	//	closesocket(clients[id]->socket);
//	//	clients.erase(id);
//	//	return;
//	//}
//
//	//clients[id]->dataBuffer.len = MAX_BUFFER;
//
//	//cout << " Send : " << clients[id]->messageBuffer << " (" << dataBytes << "bytes" << endl;
//
//	//memset(&(clients[id]->overlapped), 0, sizeof(OVERLAPPED));
//	//clients[id]->overlapped.hEvent = (HANDLE)id;
//	//int ret = WSARecv(clients[id]->socket, &clients[id]->dataBuffer, 1, 0, &flags, &(clients[id]->overlapped), recv_callback);
//	//if (ret == SOCKET_ERROR)
//	//{
//	//	if (WSAGetLastError() != WSA_IO_PENDING) {
//	//		err_disp("WSARecv()");
//	//	}
//	//}
//}
//
//int main()
//{
//	int ret;
//	wcout.imbue(std::locale("korean"));
//
//	WSADATA WSAData;
//	WSAStartup(MAKEWORD(2, 0), &WSAData);
//	// 1. ���� ����
//	SOCKET s_socket = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED); // ���� �����
//
//	// �������� ��ü����
//	SOCKADDR_IN server_a; // ���� �ּ� ����
//	memset(&server_a, 0, sizeof(SOCKADDR_IN)); // ���� �ּ� �ʱ�ȭ �ݵ�� �ʿ�
//	server_a.sin_family = AF_INET;
//	server_a.sin_port = htons(PORT);  // host to netwrok �ص���� ���缭
//	server_a.sin_addr.s_addr = INADDR_ANY; // ��� �ּҸ� �ޱ� ����
//
//	// 2. ���ϼ���
//	ret = ::bind(s_socket, (struct sockaddr*)&server_a, sizeof(SOCKADDR_IN)); // ����,���� �ּ�,���� �ּ��� ũ��
//	if (ret == SOCKET_ERROR)
//	{
//		err_disp("acccept()");
//	}
//	// 3. ���Ŵ�⿭ ����
//	ret = listen(s_socket, SOMAXCONN);
//	if (ret == SOCKET_ERROR)
//	{
//		err_disp("acccept()");
//	}
//
//	SOCKADDR_IN client_a;
//	int addrLen = sizeof(client_a);
//	memset(&client_a, 0, addrLen);
//	int user_id{};
//	SOCKET c_socket{};
//	
//	while (true) {
//		
//		c_socket = accept(s_socket, (struct sockaddr*)&client_a, &addrLen); // Accept�� ������ Ŭ���̾�Ʈ ������ �ʿ�
//		if (c_socket == INVALID_SOCKET)
//		{
//			err_disp("acccept()");
//		}
//			cout << "New client accepted." << endl;
//
//		
//		SOCKETINFO* socketInfo = new SOCKETINFO;
//		socketInfo->id = user_id;
//		socketInfo->socket = c_socket;
//		socketInfo->dataBuffer.len = MAX_BUFFER;
//		socketInfo->dataBuffer.buf = socketInfo->messageBuffer;
//		memset(&socketInfo->overlapped, 0, sizeof(WSAOVERLAPPED));
//		socketInfo->overlapped.hEvent = (HANDLE)user_id;
//		clients[user_id] = socketInfo;
//
//		DWORD flags{};
//
//		ret = WSARecv(clients[user_id]->socket, &clients[user_id]->dataBuffer, 1, NULL,
//			&flags, &(clients[user_id]->overlapped), recv_callback);
//		if (ret == SOCKET_ERROR) 
//		{
//			if (WSAGetLastError() != WSA_IO_PENDING) {
//				err_disp("WSARecv()");
//				
//			}
//		}
//		user_id++;
//	}
//		cout << "Client connection closed.\n";
//		closesocket(s_socket);
//		WSACleanup();
//}
