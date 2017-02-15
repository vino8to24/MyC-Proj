#include <stdio.h>
#include <string.h>

#include "osapi/osapi.h"

// send file
int main() {
    printf("发送方: port=9000 ...\n");

    OS_UdpSocket sock;
    sock.Open();

    printf("press Enter to send ...");
    getchar();

    FILE* fp = fopen("123.rar", "rb");
    unsigned char buf[1024+16];

    OS_SockAddr peer("127.0.0.1", 9001);    // destination

    buf[0] = 0x01;
    sock.SendTo(buf, 16, peer);
    int count = 0;
    while(1) {
        int n = fread(buf+16, 1, 1024, fp);
        if(n <= 0) break;

        buf[0] = 0x02;
        sock.SendTo(buf, n+16, peer);

        sock.RecvFrom(buf, 16, peer);
        //OS_Thread::Msleep(50);
        printf("send data packet, count = %d!\n", ++count);
    }

    buf[0] = 0xFF;
    sock.SendTo(buf, 16, peer);

    printf("Transmission completed.\n");
    fclose(fp);
    sock.Close();
    return 0;
}
