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
	

	//-------------------------------------
	// 문자열 주소 출력 
	char ipaddr[] = "192.168.1.34";
	printf("1. IP 문자열 주소 : %s\n", ipaddr);

	// 문자열 주소를 4byte 정수로 변환
	int number = inet_addr(ipaddr);
	printf("2. IP 문자열 주소 : %d, %x\n", number,number);	// %x = 16진수

	// 4byte 정수를 문자열 주소로 변환
	// : inet_ntoa(network-toascii)
	IN_ADDR in_addr;	// 구조체 
	in_addr.s_addr = number;
	char *p = inet_ntoa(in_addr);
	printf("3. IP 정수 => 문자열 주소 = %s\n",p);
	
	//--------------------------------------
	// 종료
	WSACleanup();
	return 0;
}