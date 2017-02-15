#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
#include <stdio.h>
#include <string.h>

#include "osapi/osapi.h"

/* UDP socket ����
    ���շ�: 9001
*/

/* �����ļ� */

// ��ʮ�����ƣ���buf�е����ְ��ֽڴ�ӡ��ʾ
void print_bytes(void* buf, int n)
{
	unsigned char* bytes = (unsigned char*) buf;
	for(int i=0; i<n; i++)
	{
		printf("%02X ", bytes[i]);
		if( (i+1)%16 == 0) printf("\n");
	}
}

int main()
{
	printf("���շ�: port=9001 ...\n");
	
	OS_SockAddr local("127.0.0.1", 9001);
	OS_UdpSocket sock;
	sock.Open(local, true);
	
	FILE* fp = fopen("copy.rar", "wb");
	unsigned char buf[1024 + 16];

	int count = 0;
	while(1)
	{
		OS_SockAddr peer; // �Է��ĵ�ַ
		int n = sock.RecvFrom(buf, sizeof(buf), peer);
		
		if(n <= 0)
		{
			break;
		}

		// Ӧ��
		sock.SendTo("OK", 2, peer);

		if(buf[0] == 0x01)
		{
			printf("���俪ʼ\n");
			continue;
		}
		else if(buf[0] == 0xFF) // ע�⣺buf����Ϊunsigned 
		{
			printf("�������\n");
			break;
		}
		else
		{
			fwrite(buf+16, 1, n-16, fp);//buf+16����������
			printf("Got: %d bytes \n", n);	
			//print_bytes(buf, 16);
			printf("Packets = %d !\n", ++count);
		}
	}

	fclose(fp);

	// �ر�socket
	sock.Close();
	return 0;
}

