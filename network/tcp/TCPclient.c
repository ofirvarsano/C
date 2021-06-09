#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#define SERVER_PORT 1111

void Client_TCP()
{
    int read_bytes;
    struct sockaddr_in sin;
    char buffer[4096];
    char* datagram = "just like whatsapp";
    int expected_data_len = sizeof(buffer);
    int send_bytes, data_len = 20, optval = 1, sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("failed connection to socket\n");
        return;
    }

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse of port failed\n");
        return;
    }

    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port = htons(SERVER_PORT);
    
    if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("connect error\n");
        return;
    }

    send_bytes = send(sock, (const char*)datagram, data_len, 0);
    if (send_bytes < 0)
    {
        perror("send func failed\n");
    }

    read_bytes = recv(sock, buffer, expected_data_len, 0);
    if (read_bytes < 0 && ((errno != EAGAIN) && (errno != EWOULDBLOCK)))
    {
        perror("recv failed\n");
        close(sock);
        return;
    }
    printf("server said: %s\n", buffer);

    close(sock);
    return;
}

int main()
{
    Client_TCP();
    return 0;
}