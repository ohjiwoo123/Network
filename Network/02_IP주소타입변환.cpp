#define _WINSOCK_DEPRECATED_NO_WARNINGS
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
	

	//-------------------------------------
	// ���ڿ� �ּ� ��� 
	char ipaddr[] = "192.168.1.34";
	printf("1. IP ���ڿ� �ּ� : %s\n", ipaddr);

	// ���ڿ� �ּҸ� 4byte ������ ��ȯ
	int number = inet_addr(ipaddr);
	printf("2. IP ���ڿ� �ּ� : %d, %x\n", number,number);	// %x = 16����

	// 4byte ������ ���ڿ� �ּҷ� ��ȯ
	// : inet_ntoa(network-toascii)
	IN_ADDR in_addr;	// ����ü 
	in_addr.s_addr = number;
	char *p = inet_ntoa(in_addr);
	printf("3. IP ���� => ���ڿ� �ּ� = %s\n",p);
	
	//--------------------------------------
	// ����
	WSACleanup();
	return 0;
}