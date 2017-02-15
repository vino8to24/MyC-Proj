#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include <string.h>

#include "osapi/osapi.h"
#include "Endian.h"

int main()
{
	// 打开Socket
	OS_TcpSocket client_sock;
	client_sock.Open();

	if(0)
	{
		// 获取Sendbuf的大小 
		int bufsize = 0; // 8k
		socklen_t len = 4;
		int ret = getsockopt(client_sock.hSock,SOL_SOCKET,
			SO_SNDBUF,
			(char*)&bufsize,&len);
		if(ret < 0)
		{
			// 设置失败
			printf("failed to get option!\n");
		}
	}

	if(0)
	{
		// 设置SendBuf的大小
		int bufsize = 128*1024; // 128K
		int ret = setsockopt(client_sock.hSock,SOL_SOCKET,
			SO_SNDBUF,
			(const char*)&bufsize,sizeof(int));
		if(ret < 0)
		{
			// 设置失败
		}
	}

	// 连接服务器
	OS_SockAddr serv_addr("127.0.0.1", 9555);
	if(	client_sock.Connect( serv_addr ) < 0)
	{
		printf("无法连接服务器!\n");
		return -1;
	}

	char buf[1024];
	int n;
	// 发送请求
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

	// 接受应答
	n = client_sock.Recv(buf, sizeof(buf));
	buf[n] = 0;
	printf("Got: %s \n", buf);

	// 关闭Socket
	client_sock.Close();
	return 0;
}