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
		printf("Ŭ���̾�Ʈ ���� ����\n");
		// Ŭ���̾�Ʈ ���� ���
		printf("Ŭ���̾�Ʈ ���� : %s:%d\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));

		// 5. send()/receive()
		int rev;
		rev = recv(ClientSocket, buf, sizeof(buf), 0);
		printf("�������� : %dbyte, %s\n", rev, buf);
		rev = send(ClientSocket, buf, strlen(buf) + 1, 0);
		printf("�۽����� : %dbyte, %s\n", rev, buf);
		
		// 6. closesocket()
		closesocket(ClientSocket);
	}
	//------------------------------------------
	// ����
	WSACleanup();
	return 0;
}