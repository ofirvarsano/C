#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>

#define SERVER_PORT 1111

void ClientCreate()
{
    struct sockaddr_in sin;
    int port = SERVER_PORT;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int sent_bytes;
    int sin_len;
    char buffer[4096];
    int read_bytes;

    char* data_addr;
    int data_len;

    if (sock < 0)
    {
        printf("socket error");
        exit(0);
    }
    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;

    
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    /*
    sin.sin_addr.s_addr = inet_addr("192.168.0.227");
    */
    sin.sin_port = htons(SERVER_PORT);

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0)
    {

        printf("connect error");
        exit(0);

    }

    data_addr = "hello, world";
    data_len = 12;
    sent_bytes = send(sock, data_addr, data_len, 0);

    if (sent_bytes < 0)
    {
        printf("send error");
        exit(0);
    }
    /*
    sent_bytes = sendto(sock, "Hi Server", 10, 0,(struct sockaddr *) &sin, sizeof(sin));

    if (sent_bytes < 0) 
    {
        printf("send error");
        exit(0);
    }

    sin_len = sizeof(sin);
    read_bytes = recvfrom(sock, buffer, sizeof(buffer), 0,(struct sockaddr *) &sin, &sin_len);
    if (read_bytes < 0) 
    {
        printf("read error");
        exit(0);
    }
    printf("%s\n", buffer);
    */
    close(sock); 
}

int main()
{
	ClientCreate();

    return 0;
}