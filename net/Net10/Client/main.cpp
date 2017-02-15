#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include <string.h>

#include "osapi/osapi.h"

int main()
{
	// 打开Socket
	OS_TcpSocket client_sock;
	client_sock.Open();

	// 连接服务器
	OS_SockAddr serv_addr("127.0.0.1", 9555);
	if(	client_sock.Connect( serv_addr ) < 0)
	{
		printf("无法连接服务器!\n");
		return -1;
	}

	char buf[1024];

	// 发送请求
	strcpy(buf, "help me");
	int n = strlen(buf);
	client_sock.Send(buf, n);

	// 接受应答
	n = client_sock.Recv(buf, sizeof(buf));
	buf[n] = 0;
	printf("Got: %s \n", buf);

	// 关闭Socket
	client_sock.Close();
	return 0;
}