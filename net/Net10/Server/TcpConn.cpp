#define _CRT_SECURE_NO_WARNINGS /* VS2013,2015��Ҫ��һ�� */
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
	// Ϊclient�ṩ����
	char buf[1024];

	// ���տͻ�������
	int n = m_WorkSock.Recv(buf, 1024);
	buf[n] = 0;
	printf("�ͻ�����: %s \n", buf);
	
	// Ӧ��ͻ�
	strcpy(buf, "yes, ok");
	n = strlen(buf);
	m_WorkSock.Send(buf, n);

	// �ر�socket
	m_WorkSock.Close();
	
	return 0;
}

