#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include <string.h>

#include "osapi/osapi.h"

/* �����ļ� */

int main()
{
	printf("���ͷ�: port=9000 ...\n");

	OS_UdpSocket sock;
	sock.Open();

	// �س��󣬿�ʼ����
	printf("press enter to send ...");
	getchar();

	FILE* fp = fopen("123.rar", "rb");
	unsigned char buf[1024 + 16];// unsigned char

	OS_SockAddr peer("127.0.0.1", 9001); // �Է���ַ

	// ָ���ʼ����
	buf[0] = 0x01;
	sock.SendTo(buf, 16, peer);

	int count = 0;
	while(1)
	{		
		int n = fread(buf + 16, 1, 1024, fp);
		if(n <= 0) break;

		// ���ݰ�
		buf[0] = 0x02;
		sock.SendTo(buf, n + 16, peer);	

		// ����Ӧ��
		sock.RecvFrom(buf, 16, peer);

		//OS_Thread::Msleep(50);
		printf("send data pcket , count=%d !\n", ++count);
	}

	// ָ���������
	buf[0] = 0xFF;
	sock.SendTo(buf, 16, peer);

	printf("�������,���س��ر�!\n");
	getchar();


	fclose(fp);
	// �ر�socket
	sock.Close();
	return 0;
}

