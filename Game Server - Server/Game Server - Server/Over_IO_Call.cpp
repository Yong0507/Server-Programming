#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <map>
#include <list>
using namespace std;
#include <WS2tcpip.h> 
#pragma comment(lib, "Ws2_32.lib") 
#define MAX_BUFFER 1024
#define SERVER_PORT 3500 

// ü���� �̵� Ű��
#define KEY_LEFT	'4'
#define KEY_RIGHT	'6'
#define KEY_UP		'8'
#define KEY_DOWN	'2'
#define KEY_NULL	'0'


struct SOCKETINFO
{
	WSAOVERLAPPED overlapped;
	WSABUF dataBuffer;
	SOCKET socket;
	char messageBuffer[MAX_BUFFER];
};

struct PLAYER_INFO	// ü������ ��ǥ
{
	int pos_x;
	int pos_y;
	int id;
	bool connect;
};

struct KEY		// ü������ �̵�Ű���� �޾ƿ� ����ü
{
	char cKey;
	int id;
};

map <SOCKET, SOCKETINFO> clients;  // ���� �����̳� ��
PLAYER_INFO Arr_PlayersInfo[10];
list<int> idxList;

int idx = 0;


void KeyMessage(const char* key, PLAYER_INFO& p_info);	// Ű���� ���� ��ǥ�̵�
void CALLBACK recv_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD lnFlags);
void CALLBACK send_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD lnFlags);


int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
	SOCKET listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED); //wsaflag�� �ݵ�� �־���Ѵ�.
	SOCKADDR_IN serverAddr;
	memset(&serverAddr, 0, sizeof(SOCKADDR_IN));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	::bind(listenSocket, (struct sockaddr*)&serverAddr, sizeof(SOCKADDR_IN));
	listen(listenSocket, 5);
	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(SOCKADDR_IN);
	memset(&clientAddr, 0, addrLen);
	SOCKET clientSocket;
	DWORD flags;

	for (int i = 0; i < 10; ++i)
	{
		idxList.push_back(i);
	}

	while (true)
	{
		clientSocket = accept(listenSocket, (struct sockaddr*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			printf("err  \n");
			break;
		}
		else
		{
			printf("success  \n");
		}

		if (clients.size() < 10)
		{
			clients[clientSocket] = SOCKETINFO{};
			memset(&clients[clientSocket], 0, sizeof(struct SOCKETINFO));
			clients[clientSocket].socket = clientSocket;

			idx = idxList.front();
			idxList.pop_front();

			Arr_PlayersInfo[idx] = PLAYER_INFO{ 0, 0, idx, true };
			Arr_PlayersInfo[idx].id = idx;
			clients[clientSocket].dataBuffer.len = sizeof(PLAYER_INFO);  // �÷��̾��ü�� ������
			clients[clientSocket].dataBuffer.buf = (char*)&Arr_PlayersInfo[idx];
			flags = 0;
			clients[clientSocket].overlapped.hEvent = (HANDLE)clients[clientSocket].socket;
			WSASend(clients[clientSocket].socket, &clients[clientSocket].dataBuffer, 1, NULL,
				0, &(clients[clientSocket].overlapped), send_callback);// ��� �� �����Ͱ� ���� recv_callback���� �޽����� ó���Ѵ�.
		}
	}

	closesocket(listenSocket);
	WSACleanup();
}


void KeyMessage(const char* key, PLAYER_INFO& PlayerInfo)
{
	if (KEY_RIGHT == *key)
	{
		PlayerInfo.pos_x += 50;
		if (350 < PlayerInfo.pos_x)
		{
			PlayerInfo.pos_x -= 50;
		}
	}
	if (KEY_LEFT == *key)
	{
		PlayerInfo.pos_x -= 50;
		if (0 > PlayerInfo.pos_x)
		{
			PlayerInfo.pos_x += 50;
		}
	}
	if (KEY_UP == *key)
	{
		PlayerInfo.pos_y -= 50;
		if (0 > PlayerInfo.pos_y)
		{
			PlayerInfo.pos_y += 50;
		}
	}
	if (KEY_DOWN == *key)
	{
		PlayerInfo.pos_y += 50;
		if (350 < PlayerInfo.pos_y)
		{
			PlayerInfo.pos_y -= 50;
		}
	}
}

void CALLBACK recv_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD lnFlags)
{

	SOCKET client_s = reinterpret_cast<int>(overlapped->hEvent);

	KEY keyInfo{};
	memcpy(&keyInfo, clients[client_s].messageBuffer, sizeof(KEY)); // ���� Ű ����ü ������ ����

	if (dataBytes == 0)
	{
		closesocket(clients[client_s].socket);
		clients.erase(client_s);
		Arr_PlayersInfo[keyInfo.id] = PLAYER_INFO{};
		idxList.push_front(keyInfo.id);
		return;
	}		
	// Ŭ���̾�Ʈ�� closesocket�� ���� ��� 

	clients[client_s].messageBuffer[dataBytes] = 0;

	KeyMessage(&keyInfo.cKey, Arr_PlayersInfo[keyInfo.id]); // Ű �Է¿� ���� �÷��̾��ü ��ǥ �̵�

	cout << "From client : " << clients[client_s].messageBuffer << " (" << dataBytes << ") bytes)\n";

	clients[client_s].dataBuffer.len = sizeof(Arr_PlayersInfo); // ���ۻ�����
	clients[client_s].dataBuffer.buf = (char*)&Arr_PlayersInfo; // ������ ����


	memset(&(clients[client_s].overlapped), 0x00, sizeof(WSAOVERLAPPED));
	clients[client_s].overlapped.hEvent = (HANDLE)client_s;
	WSASend(client_s, &(clients[client_s].dataBuffer), 1, &dataBytes, 0,
		&(clients[client_s].overlapped), send_callback);
}

void CALLBACK send_callback(DWORD Error, DWORD dataBytes, LPWSAOVERLAPPED overlapped, DWORD lnFlags)
{
	DWORD receiveBytes = 0;
	DWORD flags = 0;
	SOCKET client_s = reinterpret_cast<int>(overlapped->hEvent);
	if (dataBytes == 0)
	{
		closesocket(clients[client_s].socket);
		clients.erase(client_s); return;
	}		// Ŭ���̾�Ʈ�� closesocket�� ���� ���

	clients[client_s].dataBuffer.len = MAX_BUFFER;
	clients[client_s].dataBuffer.buf = clients[client_s].messageBuffer;
	cout << "Sent : " << clients[client_s].messageBuffer << " (" << dataBytes << " bytes)\n";
	memset(&(clients[client_s].overlapped), 0x00, sizeof(WSAOVERLAPPED));
	clients[client_s].overlapped.hEvent = (HANDLE)client_s;
	WSARecv(client_s, &clients[client_s].dataBuffer, 1, 0, &flags,
		&(clients[client_s].overlapped), recv_callback);
}