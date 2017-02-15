#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include <string.h>

#include "osapi/osapi.h"

/* 发送文件 */

int main()
{
	printf("发送方: port=9000 ...\n");

	OS_UdpSocket sock;
	sock.Open();

	// 回车后，开始传送
	printf("press enter to send ...");
	getchar();

	FILE* fp = fopen("123.rar", "rb");
	unsigned char buf[1024 + 16];// unsigned char

	OS_SockAddr peer("127.0.0.1", 9001); // 对方地址

	// 指令：开始传送
	buf[0] = 0x01;
	sock.SendTo(buf, 16, peer);

	int count = 0;
	while(1)
	{		
		int n = fread(buf + 16, 1, 1024, fp);
		if(n <= 0) break;

		// 数据包
		buf[0] = 0x02;
		sock.SendTo(buf, n + 16, peer);	

		// 接收应答
		sock.RecvFrom(buf, 16, peer);

		//OS_Thread::Msleep(50);
		printf("send data pcket , count=%d !\n", ++count);
	}

	// 指令：结束传送
	buf[0] = 0xFF;
	sock.SendTo(buf, 16, peer);

	printf("发送完成,按回车关闭!\n");
	getchar();


	fclose(fp);
	// 关闭socket
	sock.Close();
	return 0;
}

