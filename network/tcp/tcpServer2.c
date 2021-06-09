#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

#define SERVER_PORT 2023
#define BACK_LOG 15

void ServerCreate()
{
    struct sockaddr_in sin;
    int port = SERVER_PORT;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int flags;
    int sin_len;
    int optval = 1;
    int i, n;
    char buffer[4096];

    int read_bytes;
    int sent_bytes;

    int count = 10;

    struct sockaddr_in client_sin;
    int addr_len;
    int client_sock, newSock, last_sock;

    int expected_data_len;

    if (sock < 0)
    {
        perror("socket error");
        exit(0);
    }

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("socket error");
        exit(0);
    }

    memset(&sin, 0, sizeof(sin));
    last_sock = sock;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("bind error");
        exit(0);
    }
    if (listen(sock, BACK_LOG) < 0)
    {
        perror("listen error");
        exit(0);
    }

    addr_len = sizeof(client_sin);

    client_sock = accept(sock, (struct sockaddr *)&client_sin, &addr_len);

    if (client_sock < 0)
    {
        perror("accept error");
        exit(0);
    }

    if (-1 == (flags = fcntl(sock, F_GETFL)))
    {
        perror("error at fcntl. F_GETFL.");
        return;
    }

    if (-1 == fcntl(sock, F_SETFL, flags | O_NONBLOCK))
    {
        perror("error at fcntl. F_SETFL.");
        return;
    }

    if (-1 == (flags = fcntl(client_sock, F_GETFL)))
    {
        perror("error at fcntl. F_GETFL.");
        return;
    }

    if (-1 == fcntl(client_sock, F_SETFL, flags | O_NONBLOCK))
    {
        perror("error at fcntl. F_SETFL.");
        return;
    }
    last_sock = client_sock;
    while (1)
    {
        for (i = sock; i <= last_sock; i++)
        {
            printf("Round number %d\n", i);
            if (i = sock)
            {
                addr_len = sizeof(struct sockaddr_in);
                if ((client_sock = accept(sock, (struct sockaddr *)&client_sin, &addr_len)) == -1)
                {
                    perror("accept");
                }
                printf("server: got connection from %d\n", client_sin.sin_addr.s_addr);
                if (-1 == (flags = fcntl(client_sock, F_GETFL)))
                {
                    perror("error at fcntl. F_GETFL.");
                    return;
                }
                if (-1 == fcntl(client_sock, F_SETFL, flags | O_NONBLOCK))
                {
                    perror("error at fcntl. F_SETFL.");
                    return;
                }
                last_sock = client_sock;
            }
            else
            {
                n = recv(client_sock, buffer, sizeof(buffer), 0);
                if (n < 1)
                {
                    perror("recv - non blocking \n");
                    printf("Round %d, and the data read size is: n=%d \n", i, n);
                }
                else
                {
                    buffer[n] = '\0';
                    printf("The string is: %s \n", buffer);
                    if (send(client_sock, "Hello, world!\n", 14, 0) == -1)
                    {
                        perror("send");
                    }
                }
            }
        }
    }
    close(sock);
    /*
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
    close(client_sock);
    close(sock);
    */
}

int main()
{
    ServerCreate();

    return 0;
}