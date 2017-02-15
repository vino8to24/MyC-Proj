#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015需要这一行 */
#include <stdio.h>
#include <string.h>

#include "TcpConn.h"

TcpConn::TcpConn(OS_TcpSocket work_sock)
{
	m_WorkSock = work_sock;
}

TcpConn::~TcpConn()
{

}

int TcpConn::Routine()
{
	// 为client提供服务
	char buf[1024];

	// 接收客户的请求
	int n = m_WorkSock.Recv(buf, 1024);
	buf[n] = 0;
	printf("客户请求: %s \n", buf);
	
	// 应答客户
	strcpy(buf, "yes, ok");
	n = strlen(buf);
	m_WorkSock.Send(buf, n);

	// 关闭socket
	m_WorkSock.Close();
	
	return 0;
}

