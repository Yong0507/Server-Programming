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
//	SOCKET s_socket = WSASocket(AF_INET6, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0); // 소켓 만들기
//	SOCKADDR_IN6 server_a; // 서버 주소 선언
//	memset(&server_a, 0, sizeof(server_a)); // 서버 주소 초기화 반드시 필요
//	// 서버 주소에 값 하나하나 넣어 줘야함
//	server_a.sin6_family = AF_INET6;
//	server_a.sin6_port = htons(PORT);  // host to netwrok 앤디안을 맞춰서
//	inet_pton(AF_INET6, SERVER_ADDR, &server_a.sin6_addr);
//
//	WSAConnect(s_socket, (sockaddr*)&server_a, sizeof(server_a), NULL, NULL, NULL, NULL);
//
//	while (true) {
//		char buff[BUF_SIZE + 1]; // 데이터 입력 받기 위해서 버퍼가 필요
//		cout << "Enter Message : ";
//		cin.getline(buff, BUF_SIZE); // 버퍼에 1줄 입력
//
//		WSABUF wsabuf;
//		wsabuf.buf = buff;
//		wsabuf.len = static_cast<ULONG>(strlen(buff) + 1); // ULONG으로 타입 캐스팅
//		if (1 == wsabuf.len) break; // 데이터가 1개도 없으면 빠져나가라
//
//		DWORD num_sent; // 윈도우 API는 int 가 아닌 DWORD 같은 것을 사용
//		WSASend(s_socket, &wsabuf, 1, &num_sent, 0, NULL, NULL);
//		cout << "Sent " << wsabuf.len << "Bytes [" << buff << " ]\n";
//
//		DWORD num_recv;
//		DWORD flag = 0;
//		wsabuf.len = BUF_SIZE; // 버퍼의 크기 얼마나 올 지 모르므로 최대값으로 설정, 이렇게 안하면 서버에서 더 많은 데이터를 보내줘도 받을 수 가 없음
//
//		WSARecv(s_socket, &wsabuf, 1, &num_recv, &flag, NULL, NULL);
//		cout << "Received " << num_recv << "Bytes [" << wsabuf.buf << " ]\n";
//	}
//	closesocket(s_socket);
//	WSACleanup();
//
//}