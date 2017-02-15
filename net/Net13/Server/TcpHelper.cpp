
#include "TcpHelper.h"

int TcpHelper::WaitBytes(OS_TcpSocket sock, 
						 void* buf, 
						 int count, 
						 int timeout)
{
	// ���ó�ʱ
	if(timeout > 0)
	{
		sock.SetOpt_RecvTimeout(timeout);
	}

	// ��������,ֱ������ָ�����ֽ���
	int bytes_got = 0;
	while(bytes_got < count)
	{
		int n = sock.Recv((char*)buf + bytes_got, count - bytes_got);
		if(n <= 0)
		{
			return bytes_got;
		}

		bytes_got += n;
	}

	return bytes_got;
}

