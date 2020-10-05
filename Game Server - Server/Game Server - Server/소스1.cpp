//#include <iostream>
//#include <map>
//#include <WS2tcpip.h>
//#include "protocol.h"
//using namespace std;
//#pragma comment (lib,"WS2_32.LIB")
//constexpr int BUF_SIZE = 1024;
//constexpr short PORT = 3500;
//constexpr int MAX_PLAYERS = 10;
//
//void err_disp(const char* msg, int err_no)
//{
//	WCHAR* h_mess;
//	FormatMessage(
//		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, err_no,
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(LPTSTR)&h_mess, 0, NULL);
//	cout << msg;
//	wcout << L"  ���� => " << h_mess << endl;
//	while (true);
//	LocalFree(h_mess);
//}
//
//
//#pragma pack(1)
//typedef struct Player
//{
//	unsigned int x;
//	unsigned int y;
//	int num;
//} Player;
//#pragma pack()
//
//struct SOCKETINFO 
//{
//	WSAOVERLAPPED overlapped;
//	WSABUF dataBuffer;
//	SOCKET socket;
//	char messageBuffer[BUF_SIZE];
//
//	int id;
//};
//
//struct RecvPacket {
//	int x;
//	int y;
//	char id;
//	char dir;
//};
//
//map<int, SOCKETINFO> clients;
//Player* players[MAX_PLAYERS];
//
//void CALLBACK recv_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags);
////void CALLBACK send_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags);
//
//void ProcessPacket(void* buf) 
//{
//	
//}
//
//void SendMovePacket(int id, int x, int y) 
//{
//	SC_MOVE_packet sc_move_packet{};
//
//	sc_move_packet.id = id;
//	sc_move_packet.width = x;
//	sc_move_packet.height = y;
//	
//}
//
//
//void CALLBACK recv_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags)
//{
//	int id = reinterpret_cast<int>(overlapped->hEvent);
//
//	CS_MOVE_packet cs_move_packet;
//	SC_MOVE_packet sc_move_packet{};
//
//	memcpy(&cs_move_packet, clients[id].messageBuffer, sizeof(CS_MOVE_packet));
//
//	cout << cs_move_packet.id << endl;
//	clients[id].id = cs_move_packet.id;
//	cout << clients[id].id << endl;
//
//	if (dataBytes == 0) 
//	{
//		closesocket(clients[id].socket);
//		clients.erase(SOCKET(id));
//		return;
//	}
//
//	switch (clients[id].messageBuffer[1])
//	{
//	case CS_MOVE:
//	{
//		if (cs_move_packet.dir == KEY_DOWN)
//		{
//			sc_move_packet.height -= 50;
//			send(clients[id].socket, (char*)&sc_move_packet, sizeof(sc_move_packet), 0);
//			cout << "��" << endl;
//		}
//		// ������ �������� UP
//		else if (cs_move_packet.dir == KEY_UP)
//		{
//			sc_move_packet.height += 50;
//			send(clients[id].socket, (char*)&sc_move_packet, sizeof(sc_move_packet), 0);
//			cout << "�Ʒ�" << endl;
//		}
//		else if (cs_move_packet.dir == KEY_LEFT)
//		{
//			sc_move_packet.width -= 50;
//			send(clients[id].socket, (char*)&sc_move_packet, sizeof(sc_move_packet), 0);
//			cout << "LEFT" << endl;
//		}
//		else if (cs_move_packet.dir == KEY_RIGHT)
//		{
//			sc_move_packet.width += 50;
//			send(clients[id].socket, (char*)&sc_move_packet, sizeof(sc_move_packet), 0);
//			cout << "RIGHT" << endl;
//		}
//
//		else
//		{
//			cout << "Error" << endl;
//		}
//		// � Ű�� ���ȳ� Ȯ���Ѵ�.
//		// if ( packet.dir == KEY_UP)
//		//		�ش� �������� X, Y ���� �����Ѵ�.
//		//		���� ���� ����ü�� ������Ʈ�� ��ǥ�� �����Ѵ�.
//		//		�������ִ� ��� Ŭ���̾�Ʈ�鿡�� sc_move_packet�� �����Ѵ�.
//		// else if ( ... == KEY_DOWN)
//	default:
//	{
//		cout << "Unknown Packet Type Error!" << endl;
//		break;
//	}
//	}
//	}
//}
//
//void CALLBACK send_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags)
//{
//}
//
//
//
//int main()
//{
//	wcout.imbue(std::locale("korean"));
//
//	WSADATA WSAData;
//	WSAStartup(MAKEWORD(2, 0), &WSAData);
//	// 1.���ϻ���
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
//	::bind(s_socket, (struct sockaddr*)&server_a, sizeof(SOCKADDR_IN)); // ����,���� �ּ�,���� �ּ��� ũ��
//	// 3. ���Ŵ�⿭ ����
//	listen(s_socket, SOMAXCONN);
//	SOCKADDR_IN client_a;
//	INT a_size = sizeof(client_a);
//	memset(&client_a, 0, a_size);
//	int user_id{};
//
//	// �������� Ŭ���̾�Ʈ
//	while (true) {
//
//		SOCKET c_socket = accept(s_socket, (struct sockaddr*)&client_a, &a_size); // Accept�� ������ Ŭ���̾�Ʈ ������ �ʿ�
//
//		if (SOCKET_ERROR == c_socket)
//		{
//			err_disp("WSAAccept", WSAGetLastError());
//		}
//		cout << "New client accepted." << endl;
//
//		clients[user_id] = SOCKETINFO{};
//		memset(&clients[user_id], 0, sizeof(struct SOCKETINFO));
//
//		clients[user_id].id = user_id;
//		clients[user_id].socket = c_socket;
////		clients[user_id].dataBuffer.len = sizeof(players[user_id]);
////		clients[user_id].dataBuffer.buf = (char*)&players[user_id];
//		clients[user_id].dataBuffer.len = BUF_SIZE;
//		clients[user_id].dataBuffer.buf = clients[user_id].messageBuffer;
//
//		memset(&clients[user_id].overlapped, 0, sizeof(WSAOVERLAPPED));
//		clients[user_id].overlapped.hEvent = (HANDLE)user_id;
//		
//		// ��ø ������ �����ϰ� �Ϸ�� ������ �Լ��� �Ѱ��ش�.
//		DWORD flags = 0;
//
//		WSARecv(clients[user_id].socket, &clients[user_id].dataBuffer, 1, NULL,
//			&flags, &(clients[user_id].overlapped), recv_callback);
//
//		user_id++;
//	}
//		cout << "Client connection closed.\n";
//		closesocket(s_socket);
//		WSACleanup();
//}
