#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../../genericList/genericList.h"
#include "../../genericList/list_functions.h"
#include "../../genericList/listIterator/list_itr.h"

#define SERVER_PORT 1233

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

int recv_send(ListItr curr, ListItr end, int* countClients)
{
    int read_bytes, send_bytes;
    char buffer[4096];
    void* data;
    char* datagram = "thank you bye ";
    ListItr temp;
    int expected_data_len = sizeof(buffer);

    while (curr != end)
    {
        data = ListItr_Get(curr);

        read_bytes = recv(*(int*)data, buffer, expected_data_len, 0);
        if (read_bytes < 0)
        {
            if (errno != EAGAIN && errno != EWOULDBLOCK)
            {
                perror("recv failed\n");
                temp = curr;
                curr = ListItr_Next(curr);
                close(*(int*)data);
                (*countClients)++;
                free(ListItr_Remove(temp));
            }
            else
            {
                curr = ListItr_Next(curr);
            }
        }
        else if (read_bytes == 0)
        {
            temp = curr;
            curr = ListItr_Next(curr);
            close(*(int*)data);
            (*countClients)++;
            free(ListItr_Remove(temp));
        }
        else if (read_bytes > 0)
        {
            printf("client said %s\n", buffer);

            send_bytes = send(*(int*)data, (const char*)datagram, strlen(datagram), 0);
            if (send_bytes < 0 && ((errno != EAGAIN) && (errno != EWOULDBLOCK)))
            {
                perror("send func failed\n");
            }
            curr = ListItr_Next(curr);
        }
    }
}

void Server_TCP()
{
    List* clientsList;
    struct sockaddr_in sin;
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    char buffer[4096];
    int* curClient;
    ListItr curr, end;
    int countClients = 1000;

    int client_sock, optval = 1, sock = socket(AF_INET, SOCK_STREAM, 0);
    clientsList = List_Create();

    if (sock < 0)
    {
        perror("socket func failure\n");
        return;
    }

    Unblock_Sock(&sock);

    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse of port failed\n");
        return;
    }
    
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("binding failed\n");
        return;
    }

    if (listen(sock, 1000) < 0)
    {
        perror("listen failed\n");
        return;
    }

    while(1)
    {
        client_sock = accept(sock, (struct sockaddr *)&client_sin, &addr_len);
        if (client_sock < 0 && ((errno != EAGAIN) && (errno != EWOULDBLOCK)))
        {
            perror("accept failed\n");
            continue;
        }
        
        else if(client_sock >= 0)
        {
            if (countClients == 0)
            {
                close(client_sock);
            }
            Unblock_Sock(&client_sock);
            curClient = (int*)malloc(sizeof(int));
            *curClient = client_sock;
            List_PushHead(clientsList, curClient);
            --countClients;
        }
        
        curr = ListItr_Begin(clientsList);
        end = ListItr_End(clientsList);
        recv_send(curr, end, &countClients);
    }
    close(sock);
    List_Destroy(&clientsList, destroyInt);
}

int main()
{
    Server_TCP();
    return 0;
}