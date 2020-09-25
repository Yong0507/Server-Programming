#include <iostream>
#include <map>
#include <WS2tcpip.h>
using namespace std;
#pragma comment (lib,"WS2_32.LIB")
constexpr int BUF_SIZE = 1024;
constexpr short PORT = 3500;

void CALLBACK callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags);

void err_disp(const char* msg, int err_no)
{
	WCHAR* h_mess;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&h_mess, 0, NULL);
	cout << msg;
	wcout << L"  ���� => " << h_mess << endl;
	while (true);
	LocalFree(h_mess);
}


#pragma pack(1)
typedef struct Player
{
	unsigned int width;
	unsigned int height;
	unsigned int num;
} Player;
#pragma pack()

Player player;

struct SOCKETINFO
{
	WSAOVERLAPPED overlapped;
	WSABUF dataBuffer;
	SOCKET socket;
	int receiveBytes;
	int sendBytes;
	Player test;
};

map<SOCKET, SOCKETINFO> clients;

void CALLBACK callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD flags)
{
	struct SOCKETINFO* socketInfo;
	socketInfo = (struct SOCKETINFO*)overlapped;
	memset(&(socketInfo->overlapped), 0x00, sizeof(WSAOVERLAPPED));

	DWORD sendBytes = 0;
	DWORD receiveBytes = 0;

	if (socketInfo->test.num == 1) {
		player.width -= 50;
		if (player.width < 0)
			player.width = 0;
	}

	if (socketInfo->test.num == 2) {
		player.width += 50;
		if (player.width > 350)
			player.width = 350;
	}

	if (socketInfo->test.num == 3) {
		player.height += 50;
		if (player.height > 350)
			player.height = 350;
	}
	if (socketInfo->test.num == 4) {
		player.height -= 50;
		if (player.height < 0)
			player.height = 0;
	}


	if (dataBytes == 0) 
	{
		closesocket(socketInfo->socket);
		free(socketInfo);
		return;
	}

	if (socketInfo->receiveBytes == 0) 
	{
		// WSARecv(���� ��⿡ ����)�� �ݹ��� ���
		socketInfo->receiveBytes = dataBytes;
		socketInfo->sendBytes = 0;
		socketInfo->dataBuffer.buf = (char*)&player;
		socketInfo->dataBuffer.len = socketInfo->receiveBytes;
		
		cout << "Send " << dataBytes << " Bytes" << endl;

		if (WSASend(socketInfo->socket, &(socketInfo->dataBuffer), 1, &sendBytes, 0,
			&(socketInfo->overlapped), callback) == SOCKET_ERROR)
		{
			cout << "Error - Fail WSASend " << endl;
		}
	}

	else 
	{
		// WSASend(���信 ����)�� �ݹ��� ���
		socketInfo->sendBytes += dataBytes;
		socketInfo->receiveBytes = 0;
		socketInfo->dataBuffer.len = BUF_SIZE;
		socketInfo->dataBuffer.buf = (char*)&player;
	
		cout << "Send " << dataBytes << " Bytes" << endl;

		if (WSARecv(socketInfo->socket, &socketInfo->dataBuffer, 1, &receiveBytes, &flags,
			&(socketInfo->overlapped), callback) == ERROR) 
		{
			cout << "Error - Fail WSARecv " << endl;
		}

	}
}

int main()
{
	wcout.imbue(std::locale("korean"));

	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	// 1.���ϻ���
	SOCKET s_socket = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED); // ���� �����

	// �������� ��ü����
	SOCKADDR_IN server_a; // ���� �ּ� ����
	memset(&server_a, 0, sizeof(SOCKADDR_IN)); // ���� �ּ� �ʱ�ȭ �ݵ�� �ʿ�
	server_a.sin_family = AF_INET;
	server_a.sin_port = htons(PORT);  // host to netwrok �ص���� ���缭
	server_a.sin_addr.s_addr = INADDR_ANY; // ��� �ּҸ� �ޱ� ����

	// 2. ���ϼ���
	::bind(s_socket, (struct sockaddr*)&server_a, sizeof(SOCKADDR_IN)); // ����,���� �ּ�,���� �ּ��� ũ��
	// 3. ���Ŵ�⿭ ����
	listen(s_socket, SOMAXCONN);
	SOCKADDR_IN client_a;
	INT a_size = sizeof(client_a);
	memset(&client_a, 0, a_size);

	while (true) {
		SOCKET c_socket = accept(s_socket, (struct sockaddr*)&client_a, &a_size); // Accept�� ������ Ŭ���̾�Ʈ ������ �ʿ�
		if (c_socket == INVALID_SOCKET)
		{
			err_disp("WSAAccept", WSAGetLastError());
		}
		cout << "New client accepted." << endl;

		clients[c_socket] = SOCKETINFO{};
		clients[c_socket].socket = c_socket;
		clients[c_socket].dataBuffer.len = BUF_SIZE;
		clients[c_socket].dataBuffer.buf = (char*)&player;

		memset(&clients[c_socket].overlapped, 0, sizeof(WSAOVERLAPPED));
		clients[c_socket].overlapped.hEvent = (HANDLE)clients[c_socket].socket;

		// ��ø ������ �����ϰ� �Ϸ�� ������ �Լ��� �Ѱ��ش�.
		DWORD flags;
		DWORD receiveBytes;
		WSARecv(clients[c_socket].socket, &clients[c_socket].dataBuffer, 1, &receiveBytes,
			&flags, &(clients[c_socket].overlapped), callback);

	}
	cout << "Client connection closed.\n";
	closesocket(s_socket);
	WSACleanup();
}

