//#define WIN32_LEAN_AND_MEAN
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#include <iostream>
//#include <WS2tcpip.h>
//#include <Windows.h>
//#include <tchar.h>
//#include <stdlib.h>
//#include <time.h>
//#include <string.h>
//#include <conio.h>
//#include "protocol.h"
//using namespace std;
//
//#pragma comment (lib,"WS2_32.LIB")
//
//// #define WM_ASYNC WM_USER+1
//constexpr int BUF_SIZE = 1024;
//constexpr short PORT = 3500;
//constexpr char SERVER_ADDR[] = "127.0.0.1";
//
//int Window_Size_X = 500;
//int Window_Size_Y = 500;
//
//HINSTANCE g_hInst;
//LPCTSTR lpszClass = "Window Class Name";
//LPCTSTR lpszWindowName = "Game Server - 1";
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
//{
//	HWND hWnd;
//	MSG Message;
//	WNDCLASSEX WndClass;
//	g_hInst = hInstance;
//
//	WndClass.cbSize = sizeof(WndClass);
//	WndClass.style = CS_HREDRAW | CS_VREDRAW;
//	WndClass.lpfnWndProc = (WNDPROC)WndProc;
//	WndClass.cbClsExtra = 0;
//	WndClass.cbWndExtra = 0;
//	WndClass.hInstance = hInstance;
//	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
//	WndClass.lpszMenuName = NULL;
//	WndClass.lpszClassName = lpszClass;
//	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//
//	RegisterClassEx(&WndClass);
//
//	hWnd = CreateWindow
//
//	(lpszClass,
//		lpszWindowName,
//		(WS_OVERLAPPEDWINDOW),
//		0,
//		0,
//		Window_Size_X,
//		Window_Size_Y,
//		NULL,
//		(HMENU)NULL,
//		hInstance,
//		NULL);
//
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//
//
//	while (GetMessage(&Message, 0, 0, 0)) {
//		TranslateMessage(&Message);
//		DispatchMessage(&Message);
//	}
//	return Message.wParam;
//}
//
//struct SOCKETINFO {
//	WSAOVERLAPPED overlapped;
//	WSABUF dataBuffer;
//	SOCKET socket;
//	char messageBuffer[BUF_SIZE];
//	short id;
//};
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
//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//{
//	HDC hdc;
//	PAINTSTRUCT ps;
//	COLORREF text_color;
//	COLORREF bk_color;
//	HBRUSH hBrush, oldBrush;
//
//	static RECT Pan[8][8];
//
//	static Player player;
//
//	static WSADATA WSAData;
//	static SOCKET s_socket;
//	static SOCKADDR_IN server_a;
//
//	static DWORD flag;
//	static DWORD num_sent;
//	static DWORD num_recv;
//	static WSABUF wsabuf;
//
//	static int sendBytes;
//	static int receiveBytes;
//
//	static CS_MOVE_packet cs_move_packet{};
//	static SC_MOVE_packet sc_move_packet;
//	
//	static char messageBuffer[BUF_SIZE];
//	static int bufferLen;
//	static int i;
//	static int time = 0;
//
//switch (iMessage)
//	{
//	case WM_CREATE:
//	{
//		WSAStartup(MAKEWORD(2, 0), &WSAData);
//		// 1. 소켓 생성
//		s_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // 소켓 만들기
//
//		memset(&server_a, 0, sizeof(SOCKADDR_IN));
//
//		// 서버정보 객체설정
//		server_a.sin_family = AF_INET;
//		server_a.sin_port = htons(PORT);  // host to netwrok 앤디안을 맞춰서
//		inet_pton(AF_INET, SERVER_ADDR, &server_a.sin_addr);
//		
//		// 2. 연결 요청
//		int ret = connect(s_socket, (struct sockaddr*)&server_a, sizeof(server_a));
//		if (ret == SOCKET_ERROR) {
//			cout << "connect error. - " << WSAGetLastError() << endl;
//		}
//
//		//// 입장 했음을 서버에 알리기
//		//CS_Enter packet_enter{};
//		//packet_enter.size = sizeof(packet_enter);
//		//packet_enter.type = CS_ENTER;
//		//packet_enter.x = 0;
//		//packet_enter.y = 0;
//
//		//ret = send(s_socket, (char*)&packet_enter, sizeof(packet_enter), 0);
//		//if (ret == SOCKET_ERROR) {
//		//	while (1);
//		//}
//
//		break;
//	}
//
//	case WM_KEYDOWN:
//
//		switch (wParam)
//		{
//		case VK_UP:
//		{
//			cs_move_packet.type = CS_MOVE;
//			cs_move_packet.size = sizeof(cs_move_packet);
//			cs_move_packet.dir = KEY_UP;
//			send(s_socket, (char*)&cs_move_packet, sizeof(cs_move_packet), 0);			
//			break;
//		}
//		case VK_DOWN:
//			cs_move_packet.type = CS_MOVE;
//			cs_move_packet.size = sizeof(cs_move_packet);
//			cs_move_packet.dir = KEY_DOWN;
//			send(s_socket, (char*)&cs_move_packet, sizeof(cs_move_packet), 0);
//			break;
//		case VK_LEFT:
//			cs_move_packet.type = CS_MOVE;
//			cs_move_packet.size = sizeof(cs_move_packet);
//			cs_move_packet.dir = KEY_LEFT;
//			send(s_socket, (char*)&cs_move_packet, sizeof(cs_move_packet), 0);
//			break;
//		case VK_RIGHT:
//			cs_move_packet.type = CS_MOVE;
//			cs_move_packet.size = sizeof(cs_move_packet);
//			cs_move_packet.dir = KEY_RIGHT;
//			send(s_socket, (char*)&cs_move_packet, sizeof(cs_move_packet), 0);
//			break;
//		}
//
//		recv(s_socket, (char*)&sc_move_packet, sizeof(sc_move_packet), 0);
//		
//		InvalidateRect(hWnd, NULL, TRUE); // FALSE로 하면 이어짐  
//		break;
//	case WM_TIMER:
//		if (wParam == 1) {
//			recv(s_socket, (char*)&sc_move_packet, sizeof(sc_move_packet), 0);
//		}
//		break;
//	case WM_PAINT:
//	{
//		
//		// 캐릭터 배열에 받자.
//		//char buf[BUF_SIZE];
//		//recv(s_socket, buf, BUF_SIZE, 0); // 예외처리 하자.
//
//		// ProcessPacket() 작성할 것
//		// 내부에서 객체 위치 갱신 
//		// 함수 밖에서 갱신된 위치에 그려질 수 있도록 하자.
//		// 전역 변수로 클라이언츠 두고, enter, exit 할 때, 컨테이너에 삽입, 삭제하자.
//		// 서버로 부터 어떤 객체가 이동했는지, 입장했는지 packet.id로 알 수 있으니
//		// id - client 관리할 수 있을 것이다.
//
//
//		hdc = BeginPaint(hWnd, &ps);
//
//		for (int i = 0; i < 8; i++) {
//			for (int j = 0; j < 8; j++) {
//				Pan[i][j].left = 0 + i * 50;
//				Pan[i][j].right = 50 + i * 50;
//				Pan[i][j].top = 0 + j * 50;
//				Pan[i][j].bottom = 50 + j * 50;
//				if (i % 2 == 1 && j % 2 == 0) {
//					hBrush = CreateSolidBrush(RGB(0, 0, 0));
//					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
//
//					Rectangle(hdc, Pan[i][j].left, Pan[i][j].top, Pan[i][j].right, Pan[i][j].bottom);
//					SelectObject(hdc, oldBrush);
//					DeleteObject(hBrush);
//				}
//
//				else if (i % 2 == 0 && j % 2 == 1) {
//					hBrush = CreateSolidBrush(RGB(0, 0, 0));
//					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
//
//					Rectangle(hdc, Pan[i][j].left, Pan[i][j].top, Pan[i][j].right, Pan[i][j].bottom);
//					SelectObject(hdc, oldBrush);
//					DeleteObject(hBrush);
//				}
//
//				else {
//					Rectangle(hdc, Pan[i][j].left, Pan[i][j].top, Pan[i][j].right, Pan[i][j].bottom);
//				}
//			}
//		}
//
//		hBrush = CreateSolidBrush(RGB(255, 0, 0));
//		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
//
//		
//		Ellipse(hdc, sc_move_packet.width+0, sc_move_packet.height+0, sc_move_packet.width + 50, sc_move_packet.height + 50);
//		SelectObject(hdc, oldBrush);
//		DeleteObject(hBrush);
//
//
//		EndPaint(hWnd, &ps);
//		break;
//
//	}
//	case WM_DESTROY:
//		closesocket(s_socket);
//		WSACleanup();
//		KillTimer(hWnd, 1);
//		PostQuitMessage(0);
//		break;
//	}
//	
//	return DefWindowProc(hWnd, iMessage, wParam, lParam);
//}