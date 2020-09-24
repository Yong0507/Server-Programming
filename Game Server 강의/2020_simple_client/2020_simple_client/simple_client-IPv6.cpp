//#include <iostream>
//#include <WS2tcpip.h>
//using namespace std;
//#pragma comment (lib,"WS2_32.LIB")
//constexpr int BUF_SIZE = 1024;
//constexpr short PORT = 3500;
//constexpr char SERVER_ADDR[] = "::1";
//
//int main()
//{
//	WSADATA WSAData;
//	WSAStartup(MAKEWORD(2, 0), &WSAData);
//	SOCKET s_socket = WSASocket(AF_INET6, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0); // ���� �����
//	SOCKADDR_IN6 server_a; // ���� �ּ� ����
//	memset(&server_a, 0, sizeof(server_a)); // ���� �ּ� �ʱ�ȭ �ݵ�� �ʿ�
//	// ���� �ּҿ� �� �ϳ��ϳ� �־� �����
//	server_a.sin6_family = AF_INET6;
//	server_a.sin6_port = htons(PORT);  // host to netwrok �ص���� ���缭
//	inet_pton(AF_INET6, SERVER_ADDR, &server_a.sin6_addr);
//
//	WSAConnect(s_socket, (sockaddr*)&server_a, sizeof(server_a), NULL, NULL, NULL, NULL);
//
//	while (true) {
//		char buff[BUF_SIZE + 1]; // ������ �Է� �ޱ� ���ؼ� ���۰� �ʿ�
//		cout << "Enter Message : ";
//		cin.getline(buff, BUF_SIZE); // ���ۿ� 1�� �Է�
//
//		WSABUF wsabuf;
//		wsabuf.buf = buff;
//		wsabuf.len = static_cast<ULONG>(strlen(buff) + 1); // ULONG���� Ÿ�� ĳ����
//		if (1 == wsabuf.len) break; // �����Ͱ� 1���� ������ ����������
//
//		DWORD num_sent; // ������ API�� int �� �ƴ� DWORD ���� ���� ���
//		WSASend(s_socket, &wsabuf, 1, &num_sent, 0, NULL, NULL);
//		cout << "Sent " << wsabuf.len << "Bytes [" << buff << " ]\n";
//
//		DWORD num_recv;
//		DWORD flag = 0;
//		wsabuf.len = BUF_SIZE; // ������ ũ�� �󸶳� �� �� �𸣹Ƿ� �ִ밪���� ����, �̷��� ���ϸ� �������� �� ���� �����͸� �����൵ ���� �� �� ����
//
//		WSARecv(s_socket, &wsabuf, 1, &num_recv, &flag, NULL, NULL);
//		cout << "Received " << num_recv << "Bytes [" << wsabuf.buf << " ]\n";
//	}
//	closesocket(s_socket);
//	WSACleanup();
//
//}