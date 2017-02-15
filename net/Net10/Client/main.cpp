#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include <string.h>

#include "osapi/osapi.h"

int main()
{
	// ��Socket
	OS_TcpSocket client_sock;
	client_sock.Open();

	// ���ӷ�����
	OS_SockAddr serv_addr("127.0.0.1", 9555);
	if(	client_sock.Connect( serv_addr ) < 0)
	{
		printf("�޷����ӷ�����!\n");
		return -1;
	}

	char buf[1024];

	// ��������
	strcpy(buf, "help me");
	int n = strlen(buf);
	client_sock.Send(buf, n);

	// ����Ӧ��
	n = client_sock.Recv(buf, sizeof(buf));
	buf[n] = 0;
	printf("Got: %s \n", buf);

	// �ر�Socket
	client_sock.Close();
	return 0;
}