#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include <string.h>

#include "osapi/osapi.h"

/* UDP socket 测试
    接收方: 9001
*/

/* 接收文件 */

// 按十六进制，将buf中的数字按字节打印显示
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
	printf("接收方: port=9001 ...\n");
	
	OS_SockAddr local("127.0.0.1", 9001);
	OS_UdpSocket sock;
	sock.Open(local, true);
	
	FILE* fp = fopen("copy.rar", "wb");
	unsigned char buf[1024 + 16];

	int count = 0;
	while(1)
	{
		OS_SockAddr peer; // 对方的地址
		int n = sock.RecvFrom(buf, sizeof(buf), peer);
		
		if(n <= 0)
		{
			break;
		}

		// 应答
		sock.SendTo("OK", 2, peer);

		if(buf[0] == 0x01)
		{
			printf("传输开始\n");
			continue;
		}
		else if(buf[0] == 0xFF) // 注意：buf必须为unsigned 
		{
			printf("传输结束\n");
			break;
		}
		else
		{
			fwrite(buf+16, 1, n-16, fp);//buf+16后面是数据
			printf("Got: %d bytes \n", n);	
			//print_bytes(buf, 16);
			printf("Packets = %d !\n", ++count);
		}
	}

	fclose(fp);

	// 关闭socket
	sock.Close();
	return 0;
}

