#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include <string.h>

#include "osapi/osapi.h"
#include "Endian.h"

int main()
{
	// ��Socket
	OS_TcpSocket client_sock;
	client_sock.Open();

	if(0)
	{
		// ��ȡSendbuf�Ĵ�С 
		int bufsize = 0; // 8k
		socklen_t len = 4;
		int ret = getsockopt(client_sock.hSock,SOL_SOCKET,
			SO_SNDBUF,
			(char*)&bufsize,&len);
		if(ret < 0)
		{
			// ����ʧ��
			printf("failed to get option!\n");
		}
	}

	if(0)
	{
		// ����SendBuf�Ĵ�С
		int bufsize = 128*1024; // 128K
		int ret = setsockopt(client_sock.hSock,SOL_SOCKET,
			SO_SNDBUF,
			(const char*)&bufsize,sizeof(int));
		if(ret < 0)
		{
			// ����ʧ��
		}
	}

	// ���ӷ�����
	OS_SockAddr serv_addr("127.0.0.1", 9555);
	if(	client_sock.Connect( serv_addr ) < 0)
	{
		printf("�޷����ӷ�����!\n");
		return -1;
	}

	char buf[1024];
	int n;
	// ��������
// 	strcpy(buf, "help me");
// 	int n = strlen(buf);
// 	client_sock.Send(buf, n);

//	client_sock.Send("hello", 5);
//	client_sock.Send("world", 5);

// 	unsigned char bytes[2];
// 	itob_16be(10, bytes);
// 	client_sock.Send(bytes, 2);
// 	client_sock.Send("helloworld", 10);
	
// 	for(int i=0; i<256; i++)
// 	{
// 		printf("send # %d ... \n", i+1);
// 		client_sock.Send(buf,1024);
// 		printf("OK\n");
// 	}

	// ����Ӧ��
	n = client_sock.Recv(buf, sizeof(buf));
	buf[n] = 0;
	printf("Got: %s \n", buf);

	// �ر�Socket
	client_sock.Close();
	return 0;
}