
#include <stdio.h>
#include "osapi/osapi.h"
#include "TcpConn.h"

int main()
{
	OS_TcpSocket serv_sock ;
	// (1): ռ�ö˿ں�
	serv_sock.Open(OS_SockAddr(9555), true);

	// (2): ����
	serv_sock.Listen();

	while(1)
	{
		OS_TcpSocket work_sock;
		if(serv_sock.Accept(&work_sock) < 0)
		{
			break;
		}

		// �½�һ���̣߳������client������
		TcpConn* conn = new TcpConn(work_sock);
		conn->Run();
	}


	return 0;
}


