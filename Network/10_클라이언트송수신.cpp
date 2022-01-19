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

	//--------------------------------------------
	// 1. socket()
	SOCKET Socket;
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// SOCK_STREAM = TCP 
	if (Socket == INVALID_SOCKET)
	{
		return -1;
	}

	//2. connect()

	// 주소확인 cmd >> ipconfig 명령 (192.168.1.34)
	SOCKADDR_IN ServerAddr = { 0, };
	ServerAddr.sin_family = AF_INET;	// TCP/IP 통신을 하겠다.
	ServerAddr.sin_addr.s_addr = inet_addr("192.168.1.12");	// IP 주소를 알려준다
	ServerAddr.sin_port = htons(9000);	// 9000을 뒤집어서 내보낸다. (호스트가 네트워크 내보낼 때)

	int retval = connect(Socket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (retval == SOCKET_ERROR)
	{
		return -1;
	}
	printf("접속성공\n");
	while (1)
	{
		char buf[100];
		printf(">>");
		gets_s(buf, sizeof(buf));
		if (strcmp(buf, "exit") == 0)
		{
			break;
		}

		// 3. send
		int rev;
		rev = send(Socket, buf, strlen(buf) + 1, 0);
		if (rev == SOCKET_ERROR || rev == 0)
			break;
		printf("송신정보 : %dbyte, %s\n", rev, buf);

		// 4. recv
		rev = recv(Socket, buf, sizeof(buf), 0);
		if (rev == SOCKET_ERROR || rev == 0)
			break;
		printf("수신정보 : %dbyte, %s\n", rev, buf);

	}

	//--------------------------------------------
	// 종료
	closesocket(Socket);

	WSACleanup();
	return 0;
}