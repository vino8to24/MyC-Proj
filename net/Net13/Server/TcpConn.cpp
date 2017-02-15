
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
	// Ϊclient�ṩ����
	unsigned char buf[1024];
	int n ;

	// ���տͻ�������
	n = m_WorkSock.Recv(buf, 1023);
	//printf("�ͻ�����: %s \n", buf);
	
	OS_Thread::Msleep(5000);


	// Ӧ��ͻ�
	m_WorkSock.Send("yes", 3);

	// �ر�socket
	m_WorkSock.Close();
	
	return 0;
}

