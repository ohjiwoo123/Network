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
	SOCKADDR_IN addr; 
	addr.sin_family = AF_INET;	// TCP/IP 통신을 하겠다.
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");	// IP 주소를 알려준다
	addr.sin_port = htons(9000);	// 9000을 뒤집어서 내보낸다. (호스트가 네트워크 내보낼 때)

	//--------------------------------------------
	// 종료
	WSACleanup();
	return 0;
}