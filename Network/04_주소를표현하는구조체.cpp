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

	//--------------------------------------------
	SOCKADDR_IN addr; 
	addr.sin_family = AF_INET;	// TCP/IP ����� �ϰڴ�.
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");	// IP �ּҸ� �˷��ش�
	addr.sin_port = htons(9000);	// 9000�� ����� ��������. (ȣ��Ʈ�� ��Ʈ��ũ ������ ��)

	//--------------------------------------------
	// ����
	WSACleanup();
	return 0;
}