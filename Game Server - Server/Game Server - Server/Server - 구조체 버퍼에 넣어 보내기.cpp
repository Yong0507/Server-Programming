//#include <iostream>
//#include <WS2tcpip.h>
//using namespace std;
//#pragma comment (lib,"WS2_32.LIB")
//constexpr int BUF_SIZE = 1024;
//constexpr short PORT = 3500;
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
//#pragma pack(1)
//typedef struct Player
//{
//	int width;
//	int height;
//	int test;
//} Player;
//#pragma pack()
//
//Player player;
//
//
//int main()
//{
//	// int len = sizeof(player);
//
//	wcout.imbue(std::locale("korean"));
//	WSADATA WSAData;
//	WSAStartup(MAKEWORD(2, 0), &WSAData);
//	SOCKET s_socket = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0); // ���� �����
//	SOCKADDR_IN server_a; // ���� �ּ� ����
//	memset(&server_a, 0, sizeof(server_a)); // ���� �ּ� �ʱ�ȭ �ݵ�� �ʿ�
//	// ���� �ּҿ� �� �ϳ��ϳ� �־� �����
//	server_a.sin_family = AF_INET;
//	server_a.sin_port = htons(PORT);  // host to netwrok �ص���� ���缭
//	server_a.sin_addr.s_addr = INADDR_ANY; // ��� �ּҸ� �ޱ� ����
//
//	::bind(s_socket, (sockaddr*)&server_a, sizeof(server_a)); // ����,���� �ּ�,���� �ּ��� ũ��
//	listen(s_socket, SOMAXCONN);
//
//
//	while (true) {
//
//		SOCKADDR_IN client_a;
//		INT a_size = sizeof(client_a);
//		// ���� ���� �غ��� ���� a_size = 0;
//		SOCKET c_socket = WSAAccept(s_socket, (sockaddr*)&client_a, &a_size, NULL, NULL); // Accept�� ������ Ŭ���̾�Ʈ ������ �ʿ�
//		if (SOCKET_ERROR == c_socket) {
//			err_disp("WSAAccept", WSAGetLastError());
//		}
//		cout << "New client accepted.\n";
//		
//		while (true) {
//
//			WSABUF wsabuf;
//			wsabuf.buf = (char*)&player;
//			wsabuf.len = sizeof(player);
//			
//			DWORD num_recv;
//			DWORD num_sent;
//			DWORD flag = 0;
//			
//			WSARecv(c_socket, &wsabuf, 1, &num_recv, &flag, NULL, NULL);
//			
//			if (player.test == 1) {
//				player.width -= 50;
//				if (player.width < 0)
//					player.width = 0;
//			}
//
//			if (player.test == 2) {
//				player.width += 50;
//				if (player.width > 350)
//					player.width = 350;
//			}
//
//			if (player.test == 3) {
//				player.height += 50;
//				if (player.height > 350)
//					player.height = 350;
//			}
//			if (player.test == 4) {
//				player.height -= 50;
//				if (player.height < 0)
//					player.height = 0;
//			}
//
//			wsabuf.len = num_recv;
//
//			WSASend(c_socket, &wsabuf, 1, &num_sent, 0, NULL, NULL);
//		}
//		cout << "Client connection closed.\n";
//	}
//	closesocket(s_socket);
//	WSACleanup();
//}