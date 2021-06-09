#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "../../genericList/genericList.h"
#include "../../genericList/list_functions.h"
#include "../../genericList/listIterator/list_itr.h"

#define SERVER_PORT 1233
#define MAXFD   1024
#define N_CLIENTS   5
#define MAX_OF_CLIENTS 1010
#define CLOSE -1
#define FAIL -1
#define OK 1

void Unblock_Sock(int* _sock)
{
    int sock_Flags;

    if((sock_Flags = fcntl(*_sock, F_GETFL)) == -1)
    {
        perror("error on fcntl getfl\n");
        return;
    }

    if(fcntl(*_sock, F_SETFL, sock_Flags | O_NONBLOCK))
    {
        perror("error on fcntl setfl\n");
        return;
    }
}

void destroyInt(void* _element)
{
    if ((int*)_element)
    {
        close(*(int*)_element);
        free(_element);
    }
}

int CheckCurrentClient(int _clientSock)
{
    int read_byte, sent_byte;
    char buffer[4096];
    char* datagram = "thank you bye ";
    int dataLen = strlen(datagram);

    read_byte = recv(_clientSock, buffer, sizeof(buffer), 0);

    if (read_byte == 0)
    {
        return CLOSE;
    }
    else if (read_byte < 0)
    {
        perror("rcvfrom failed");
        return CLOSE;
    }
    else
    {
        printf("client said %s\n", buffer);

        sent_byte = send(_clientSock, datagram, strlen(datagram), 0);
        if (sent_byte < 0)
        {
            perror("send func failed\n");
        }
    }
    return OK;
}
int initialServer()
{
    struct sockaddr_in sin;
    int optval = 1;
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        perror("socket func failure\n");
        return FAIL;
    }

    Unblock_Sock(&sock);

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse of port failed\n");
        return FAIL;
    }
    
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("binding failed\n");
        return FAIL;
    }

    if (listen(sock, MAX_OF_CLIENTS) < 0)
    {
        perror("listen failed\n");
        return FAIL;
    }
    return sock;
}

void acceptClients(int sock, int* countClients, int* client_sock, List* clientsList, fd_set* masterfd)
{
    int i;
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int* curClient;
    /* New client await */
    for (i = 0; i < N_CLIENTS; ++i)
    {
        *client_sock = accept(sock, (struct sockaddr*) &client_sin, &addr_len);
        if(*client_sock >= 0)
        {
            if (*countClients == 0)
            {
                close(*client_sock);
            }
            else
            {
                curClient = (int*)malloc(sizeof(int));
                *curClient = *client_sock;
                List_PushHead(clientsList, curClient);
                --(*countClients);
                FD_SET(*client_sock, masterfd);
            }
        }
    }
}

void Server_TCP()
{
    List* clientsList;
    

    char buffer[4096];
    int* curClient;
    ListItr curr, end;
    int countClients = MAX_OF_CLIENTS;
    int* deleteClient = NULL;

    fd_set masterfd, tempfd;
    int activity, i, data;
    int client_sock, sock;
    clientsList = List_Create();

    sock = initialServer();
    if (sock == FAIL)
    {
        return;
    }

    FD_ZERO(&masterfd);
    FD_SET(sock, &masterfd);

    while(1)
    {
        tempfd = masterfd;
        activity = select(MAXFD, &tempfd , NULL , NULL , NULL);

        if (activity < 0 && errno != EINTR)
        {
            break;
        }

        if (activity > 0 && FD_ISSET(sock, &tempfd))
        {
             /* New client await */
            acceptClients(sock, &countClients, &client_sock, clientsList, &masterfd);
            --activity;
        }
        curr = ListItr_Begin(clientsList);
        end = ListItr_End(clientsList);

        while (activity > 0 && curr != end)
        {
            data = *(int*)ListItr_Get(curr);
            curr = ListItr_Next(curr);
            if (FD_ISSET(data, &tempfd))
            {
                if (CLOSE == CheckCurrentClient(data))
                {
                    close(data);
                    ++countClients;
                    FD_CLR(data, &masterfd);
                    deleteClient = (int*)ListItr_Remove(ListItr_Prev(curr));
                    free(deleteClient);
                }
                --activity;
            }
        }
    }
    close(sock);
    List_Destroy(&clientsList, destroyInt);
}

int main()
{
    Server_TCP();
    return 0;
}