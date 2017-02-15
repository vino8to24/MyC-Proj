#ifndef _TCP_HELPER_H
#define _TCP_HELPER_H

#include "osapi/Socket.h"

class TcpHelper
{

public:
	// ����ָ�����ȵ��ֽ�����
	// count: ׼�����ն����ֽ�
	// timeout: ���Ϊ0����ʾ�����ȴ������򣬱�ʾ���ý��ճ�ʱ
	static int WaitBytes(OS_TcpSocket sock, 
		void* buf, 
		int count, 
		int timeout=0);

};




#endif


