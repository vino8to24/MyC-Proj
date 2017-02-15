
#include <stdio.h>
#include <string.h>

#include "TcpConn.h"
#include "Endian.h"
#include "TcpHelper.h"

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
	unsigned char buf[1024];
	int n ;

	// 接收客户的请求
	n = m_WorkSock.Recv(buf, 1023);
	//printf("客户请求: %s \n", buf);
	
	OS_Thread::Msleep(5000);


	// 应答客户
	m_WorkSock.Send("yes", 3);

	// 关闭socket
	m_WorkSock.Close();
	
	return 0;
}

