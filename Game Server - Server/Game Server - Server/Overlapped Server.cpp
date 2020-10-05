//#include <iostream>
//#include <map>
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
//
//#pragma pack(1)
//typedef struct Player
//{
//	unsigned int width;
//	unsigned int height;
//	unsigned int num;
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
//};
//
//map<SOCKET, SOCKETINFO> clients;
//
//void CALLBACK recv_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags);
//void CALLBACK send_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags);
//
//void CALLBACK recv_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags)
//{
//	if (player.num == 1) {
//		player.width -= 50;
//		if (player.width < 0)
//			player.width = 0;
//	}
//
//	if (player.num == 2) {
//		player.width += 50;
//		if (player.width > 350)
//			player.width = 350;
//	}
//
//	if (player.num == 3) {
//		player.height += 50;
//		if (player.height > 350)
//			player.height = 350;
//	}
//	if (player.num == 4) {
//		player.height -= 50;
//		if (player.height < 0)
//			player.height = 0;
//	}
//
//	SOCKET c_socket = reinterpret_cast<int>(overlapped->hEvent);
//
//	if (dataBytes == 0) 
//	{
//		closesocket(clients[c_socket].socket);
//		clients.erase(c_socket);
//		return;
//	}
//
//	clients[c_socket].dataBuffer.len = dataBytes;
//
//	cout << "Send to client DataBuffer Len : " << clients[c_socket].dataBuffer.len << endl;
//	cout << "Send to client DataBuffer Buf : " << &clients[c_socket].dataBuffer.buf << endl;
//	
//	memset(&(clients[c_socket].overlapped), 0, sizeof(WSAOVERLAPPED));
//	clients[c_socket].overlapped.hEvent = (HANDLE)c_socket;
//
//	WSASend(c_socket, &(clients[c_socket].dataBuffer), 1, NULL, 0, &(clients[c_socket].overlapped), send_callback);
//	
//	cout << "Send to client DataBuffer Len : " << clients[c_socket].dataBuffer.len << endl;
//	cout << "Send to client DataBuffer Buf : " << &clients[c_socket].dataBuffer.buf << endl;
//
//}
//
//void CALLBACK send_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags)
//{
//
//	DWORD receiveBytes = 0;
//	
//	SOCKET c_socket = reinterpret_cast<int>(overlapped->hEvent);
//
//	if (dataBytes == 0) 
//	{
//		closesocket(clients[c_socket].socket);
//		clients.erase(c_socket);
//		return;
//	}
//
//	clients[c_socket].dataBuffer.len = BUF_SIZE;
//
//	cout << "From client DataBuffer Len : " << clients[c_socket].dataBuffer.len << endl;
//	cout << "From client DataBuffer Buf : " << &(clients[c_socket].dataBuffer.buf) << endl;
//
//
//	memset(&(clients[c_socket].overlapped), 0, sizeof(WSAOVERLAPPED));
//	clients[c_socket].overlapped.hEvent = (HANDLE)c_socket;
//	WSARecv(c_socket, &clients[c_socket].dataBuffer, 1, 0, &flags, &(clients[c_socket].overlapped), recv_callback);
//
//	cout << "From client DataBuffer Len : " << clients[c_socket].dataBuffer.len << endl;
//	cout << "From client DataBuffer Buf : " << &(clients[c_socket].dataBuffer.buf) << endl;
//
//
//}
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
//	
//	while (true) {
//		SOCKET c_socket = accept(s_socket, (struct sockaddr*)&client_a, &a_size); // Accept�� ������ Ŭ���̾�Ʈ ������ �ʿ�
//		if (SOCKET_ERROR == c_socket)
//		{
//			err_disp("WSAAccept", WSAGetLastError());
//		}
//		cout << "New client accepted." << endl;
//
//		clients[c_socket] = SOCKETINFO{};
//		clients[c_socket].socket = c_socket;
//		clients[c_socket].dataBuffer.len = sizeof(player);
//		clients[c_socket].dataBuffer.buf = (char*)&player;
//		memset(&clients[c_socket].overlapped, 0, sizeof(WSAOVERLAPPED));
//		clients[c_socket].overlapped.hEvent = (HANDLE)clients[c_socket].socket;
//
//		// ��ø ������ �����ϰ� �Ϸ�� ������ �Լ��� �Ѱ��ش�.
//		DWORD flags = 0;
//		WSARecv(clients[c_socket].socket, &clients[c_socket].dataBuffer, 1, NULL,
//			&flags, &(clients[c_socket].overlapped), recv_callback);
//
//	}
//		cout << "Client connection closed.\n";
//		closesocket(s_socket);
//		WSACleanup();
//}
//
