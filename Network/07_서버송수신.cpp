#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	WSADATA wsa;
	// 초기화 
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("윈도우 소켓 초기화 실패\n");
		return -1;
	}
	printf("윈도우 소켓 초기화 성공\n");
	//------------------------------------------
	//--- 리슨 소켓 생성
	// 1. socket()
	SOCKET ListenSocket;
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// SOCK_STREAM = TCP 
	if (ListenSocket == INVALID_SOCKET)
	{
		return -1;
	}
	//------------------------------------------
	// 2. bind()
	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = AF_INET;	// TCP/IP 통신을 하겠다.
	ServerAddr.sin_port = htons(9000);	// 9000을 뒤집어서 내보낸다. (호스트가 네트워크 내보낼 때)
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);	// IP 주소를 알려준다

	int retval = bind(ListenSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (retval == SOCKET_ERROR)
	{
		return -1;
	}

	//------------------------------------------
	// 3. listen()
	retval = listen(ListenSocket, SOMAXCONN); // 0x7fffffffffffffff
	if (retval == SOCKET_ERROR)
	{
		return -1;
	}
	printf("대기 소켓의 초기화 과정 완료\n");

	//--- 클라이언트 접속대기 (통신 소켓 생성)
	char buf[100];
	while (1)
	{
		// 4. accept()
		SOCKADDR_IN ClientAddr = { 0 };
		int ClientAddrSize = sizeof(ClientAddr);
		SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientAddr, &ClientAddrSize);

		if (ClientSocket == INVALID_SOCKET)
		{
			return -1;
		}
		printf("클라이언트 접속 성공\n");
		// 클라이언트 정보 출력
		printf("클라이언트 정보 : %s:%d\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));

		// 5. send()/receive()
		int rev;
		rev = recv(ClientSocket, buf, sizeof(buf), 0);
		printf("수신정보 : %dbyte, %s\n", rev, buf);
		rev = send(ClientSocket, buf, strlen(buf) + 1, 0);
		printf("송신정보 : %dbyte, %s\n", rev, buf);
		
		// 6. closesocket()
		closesocket(ClientSocket);
	}
	//------------------------------------------
	// 종료
	WSACleanup();
	return 0;
}