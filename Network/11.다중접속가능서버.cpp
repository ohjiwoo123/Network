#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")


DWORD WINAPI WorkThread(LPVOID p)
{
	SOCKET ClientSocket = (SOCKET)p;
	char buf[100];
	while (1) // �� ���� ������ �����ϱ� ���� ���� ����
	{
		// 5. send()/receive()
		int rev;
		rev = recv(ClientSocket, buf, sizeof(buf), 0);
		if (rev == SOCKET_ERROR)
		{
			printf("���Ͽ� ���� �߻�\n");
			break;
		}
		else if (rev == 0)
		{
			printf("������ closesocket() ȣ��\n");
			break;
		}
		else
		{
			printf("�������� : %dbyte, %s\n", rev, buf);
			rev = send(ClientSocket, buf, strlen(buf) + 1, 0);
			if (rev == SOCKET_ERROR || rev == 0)
			{
				break;
			}
			printf("�۽����� : %dbyte, %s\n", rev, buf);
		}
	}
	// 6. closesocket()
	closesocket(ClientSocket);
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
	//------------------------------------------
	//--- ���� ���� ����
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
	ServerAddr.sin_family = AF_INET;	// TCP/IP ����� �ϰڴ�.
	ServerAddr.sin_port = htons(9000);	// 9000�� ����� ��������. (ȣ��Ʈ�� ��Ʈ��ũ ������ ��)
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);	// IP �ּҸ� �˷��ش�

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
	printf("��� ������ �ʱ�ȭ ���� �Ϸ�\n");

	//--- Ŭ���̾�Ʈ ���Ӵ�� (��� ���� ����)

	while (1)	// �ټ��� ���� ���� ���ѷ��� 
	{
		// 4. accept()
		SOCKADDR_IN ClientAddr = { 0 };
		int ClientAddrSize = sizeof(ClientAddr);
		SOCKET ClientSocket = accept(ListenSocket, (SOCKADDR*)&ClientAddr, &ClientAddrSize);

		if (ClientSocket == INVALID_SOCKET)
		{
			return -1;
		}
		printf("Ŭ���̾�Ʈ ���� ����\n");
		// Ŭ���̾�Ʈ ���� ���
		printf("Ŭ���̾�Ʈ ���� : %s:%d\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));

		// �ϳ��� Ŭ���̾�Ʈ�� ���� ���� ������ ���� 
		CloseHandle(CreateThread(NULL, 0, WorkThread, (LPVOID)ClientSocket, NULL, NULL));

	}
	//------------------------------------------
	// ����
	WSACleanup();
	return 0;
}