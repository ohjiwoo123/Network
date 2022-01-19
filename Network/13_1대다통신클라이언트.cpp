#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")


DWORD WINAPI recvThread(LPVOID p)
{
	SOCKET Socket = (SOCKET)p;
	int rev;
	char buf[100];

	while (1)
	{
		// 4. recv
		rev = recv(Socket, buf, sizeof(buf), 0);
		if (rev == SOCKET_ERROR || rev == 0)
			break;
		else
			printf("�������� : %dbyte, %s\n", rev, buf);
	}
	closesocket(Socket);
	return 0;
}
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
	// 1. socket()
	SOCKET Socket;
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// SOCK_STREAM = TCP 
	if (Socket == INVALID_SOCKET)
	{
		return -1;
	}

	//2. connect()

	// �ּ�Ȯ�� cmd >> ipconfig ��� (192.168.1.34)
	SOCKADDR_IN ServerAddr = { 0, };
	ServerAddr.sin_family = AF_INET;	// TCP/IP ����� �ϰڴ�.
	ServerAddr.sin_addr.s_addr = inet_addr("192.168.1.34");	// IP �ּҸ� �˷��ش�
	ServerAddr.sin_port = htons(9000);	// 9000�� ����� ��������. (ȣ��Ʈ�� ��Ʈ��ũ ������ ��)

	int retval = connect(Socket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr));
	if (retval == SOCKET_ERROR)
	{
		return -1;
	}
	printf("���Ӽ���\n");

	while (1)
	{
		// ���� ������ ���� 
		CloseHandle(CreateThread(NULL, 0, recvThread, (LPVOID)Socket, 0, 0));
		char buf[100];
		printf(">>");
		gets_s(buf, sizeof(buf));
		if (strcmp(buf, "exit") == 0)
		{
			break;
		}

		int rev;
		rev = send(Socket, buf, strlen(buf) + 1, 0);
		if (rev == SOCKET_ERROR || rev == 0)
			break;
		printf("�۽����� : %dbyte, %s\n", rev, buf);
		

	}

	//--------------------------------------------
	// ����
	closesocket(Socket);

	WSACleanup();
	return 0;
}