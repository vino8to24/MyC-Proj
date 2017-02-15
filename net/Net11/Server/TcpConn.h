
#ifndef _TCP_CONN_H
#define _TCP_CONN_H

#include "osapi/osapi.h"

/* TcpConn:
   ��һ���߳���ά��Client - WorkingSocket֮���ͨ������
*/

class TcpConn : public OS_Thread
{
public:
	TcpConn(OS_TcpSocket work_sock);
	~TcpConn();

private:
	virtual int Routine();

private:
	OS_TcpSocket m_WorkSock;

};




#endif

