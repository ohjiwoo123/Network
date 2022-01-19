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
	printf("--------------------------\n");

	//-----------------------------------
	// 1. 호스트 바이트 (리틀 엔디언)
	unsigned short a = 0x1234; // 2byte
	unsigned long b = 0x12345678; // 4byte

	printf("1. 0x%x, %d\n", a, sizeof(a));	// %x = hexa 
	printf("2. 0x%x, %d\n", b, sizeof(b));
	printf("--------------------------\n");

	// 2. 호스트 바이트를 네트워크 바이트로 변환한다.
	unsigned short c = htons(a);
	unsigned long d = htonl(b);

	printf("3. 0x%x, %d\n", c, sizeof(c));	// %x = hexa 
	printf("4. 0x%x, %d\n", d, sizeof(d));
	printf("--------------------------\n");

	// 3. 네트워크 바이트를 호스트 바이트로 변환한다.
	unsigned short e = ntohs(c);
	unsigned long f = ntohl(d);

	printf("5. 0x%x, %d\n", e, sizeof(e));	// %x = hexa 
	printf("6. 0x%x, %d\n", f, sizeof(f));
	printf("--------------------------\n");
	
	//-----------------------------------
	// 종료
	WSACleanup();
	return 0;
}