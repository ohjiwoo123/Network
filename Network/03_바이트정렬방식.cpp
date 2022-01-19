#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	WSADATA wsa;
	// �ʱ�ȭ 
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("������ ���� �ʱ�ȭ ����\n");
		return -1;
	}
	printf("������ ���� �ʱ�ȭ ����\n");
	printf("--------------------------\n");

	//-----------------------------------
	// 1. ȣ��Ʈ ����Ʈ (��Ʋ �����)
	unsigned short a = 0x1234; // 2byte
	unsigned long b = 0x12345678; // 4byte

	printf("1. 0x%x, %d\n", a, sizeof(a));	// %x = hexa 
	printf("2. 0x%x, %d\n", b, sizeof(b));
	printf("--------------------------\n");

	// 2. ȣ��Ʈ ����Ʈ�� ��Ʈ��ũ ����Ʈ�� ��ȯ�Ѵ�.
	unsigned short c = htons(a);
	unsigned long d = htonl(b);

	printf("3. 0x%x, %d\n", c, sizeof(c));	// %x = hexa 
	printf("4. 0x%x, %d\n", d, sizeof(d));
	printf("--------------------------\n");

	// 3. ��Ʈ��ũ ����Ʈ�� ȣ��Ʈ ����Ʈ�� ��ȯ�Ѵ�.
	unsigned short e = ntohs(c);
	unsigned long f = ntohl(d);

	printf("5. 0x%x, %d\n", e, sizeof(e));	// %x = hexa 
	printf("6. 0x%x, %d\n", f, sizeof(f));
	printf("--------------------------\n");
	
	//-----------------------------------
	// ����
	WSACleanup();
	return 0;
}