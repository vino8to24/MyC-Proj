
#include <stdio.h>
#include "osapi/osapi.h"
#include "TcpConn.h"

int main()
{
	OS_TcpSocket serv_sock ;
	// (1): 占用端口号
	serv_sock.Open(OS_SockAddr(9555), true);

	// (2): 监听
	serv_sock.Listen();

	while(1)
	{
		OS_TcpSocket work_sock;
		if(serv_sock.Accept(&work_sock) < 0)
		{
			break;
		}

		// 新建一个线程，处理该client的请求
		TcpConn* conn = new TcpConn(work_sock);
		conn->Run();
	}


	return 0;
}


