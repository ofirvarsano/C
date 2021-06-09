#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVER_PORT 2022
#define BACK_LOG 15

void ServerCreate()
{
    struct sockaddr_in sin;
    int port = SERVER_PORT;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    int sin_len;
    int optval = 1;

    char buffer[4096];

    int read_bytes;
    int sent_bytes;

    int count = 10;

    struct sockaddr_in client_sin;
    int addr_len;
    int client_sock;

    int expected_data_len;

    if (sock < 0)
    {
        printf("socket error");
        exit(0);
    }

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        printf("socket error");
        exit(0);
    }

    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;

    sin.sin_addr.s_addr = INADDR_ANY;

    sin.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0)
    {
        printf("bind error");
        exit(0);
    }
    if (listen(sock, BACK_LOG) < 0) 
    {
        printf("listen error");
        exit(0);
    }

    addr_len = sizeof(client_sin);

    client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);

    if (client_sock < 0)
    {
        printf("accept error");
        exit(0);
    }

    expected_data_len = sizeof(buffer);

    read_bytes = recv(client_sock, buffer, expected_data_len, 0);

    if (read_bytes == 0)
    {
        close(sock);
        exit(0);
    }
    else if (read_bytes < 0)
    { // error
        printf("recv error");
    }
    else
    {
        printf("%s\n", buffer);
    }
/*
    sin_len = sizeof(sin);
    while (count--)
    {
        read_bytes = recvfrom(sock, buffer, sizeof(buffer), 0,(struct sockaddr *) &sin, &sin_len);
        if (read_bytes < 0) 
        {
            printf("read error");
            exit(0);
        }
        printf("%s\n", buffer);

        sent_bytes = sendto(sock, "Hi Client", 10, 0,(struct sockaddr *) &sin, sizeof(sin));
    }
*/
    close(client_sock);
    close(sock);
}

int main()
{
	ServerCreate();

    return 0;
}