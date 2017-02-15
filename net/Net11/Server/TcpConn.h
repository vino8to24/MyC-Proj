
#ifndef _TCP_CONN_H
#define _TCP_CONN_H

#include "osapi/osapi.h"

/* TcpConn:
   用一个线程来维护Client - WorkingSocket之间的通话连接
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

