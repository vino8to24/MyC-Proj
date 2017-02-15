#include <stdio.h>
#include <string.h>

#include "osapi/osapi.h"

int main() {
    printf("接收方: port=9001 ...\n");

    OS_SockAddr local("127.0.0.1", 9001);
    OS_UdpSocket sock;
    sock.Open(local, true);

    FILE* fp = fopen("copy.rar", "wb");
    unsigned char buf[1024+16];

    int count = 0;
    while(1) {
        OS_SockAddr peer;
        int n = sock.RecvFrom(buf, sizeof(buf), peer);
        if(n <= 0) break;

        // respones
        sock.SendTo("OK", 2, peer);

        if(buf[0] == 0x01) {
            printf("传输开始...\n");
            continue;
        }
        else if(buf[0] == 0xFF) {
            printf("传输结束.\n");
            break;
        }
        else {
            fwrite(buf+16, 1, n-16, fp);
            std::string ip_addr = peer.GetIp_str();
            int port = peer.GetPort();
            printf("From %s, port=%d ", ip_addr.c_str(), port);
            printf("receive: %d bytes\n", n);
            printf("packets = %d\n", ++count);
        }
    }
    fclose(fp);
    sock.Close();
    return 0;
}
