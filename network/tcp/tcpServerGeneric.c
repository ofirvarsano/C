
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> /*memset*/
#include <sys/types.h> /*bind, fd_set*/
#include <sys/socket.h> /*socket*/
#include <arpa/inet.h> /*htons*/
#include <fcntl.h> /*fcntl*/
#include <errno.h> /*errno*/
#include <sys/select.h> /* select */
#include <sys/time.h> /* fd_set */
#include "../../advancedC/genericList/list_itr.h"
#include "../../advancedC/genericList/list_functions.h"




#define PORT 1200
#define MAXLINE 1024
#define MAX_OF_CLIENTS 1010
#define TRUE 1
#define FALSE 0
#define FAIL -1
#define CLOSE -1
#define OK 1
#define GET_N_CLIENTS 5

int Init_Server();
int CheckNewClient(int _listenSock, List* _clients, fd_set* _master);
int CheckCurrentClient(int _clientSock);
void DestroyServer(int _listenSock, List* _clients);
int NoBlockinSock(int _socket);
static void DestroySock(void* _clientSock);

int main ()
{
    int sockListen, currClientSock, activity = 0;
    List* clients = NULL;
    ListItr currItr = NULL, endItr = NULL;
    int * deleteClient = NULL;
    fd_set master, temp;

    if (FAIL == (sockListen = Init_Server()))
    {
        return 1;
    }
    if ((clients = List_Create()) == NULL)
    {
        return 1;
    }
    /* Listen socket set in the fd */
    FD_ZERO(&master);
    FD_SET(sockListen, &master);

    while(TRUE)
    {
        temp = master;
        activity = select(MAXLINE, &temp, NULL, NULL, NULL);

        if (activity < 0 && errno != EINTR)
        {
            break;
        }

        if (activity > 0 && FD_ISSET(sockListen, &temp))
        {
            /* New client await */
            CheckNewClient(sockListen, clients, &master);
            --activity;
        }

        currItr = ListItr_Begin(clients);
        endItr = ListItr_End(clients);

        while (activity > 0 && currItr != endItr)
        {
            currClientSock = *((int*)(ListItr_Get(currItr)));
            currItr = ListItr_Next(currItr);
            if (FD_ISSET(currClientSock, &temp))
            {
                if (CLOSE == CheckCurrentClient(currClientSock))
                {
                    close(currClientSock);
                    FD_CLR(currClientSock, &master);
                    deleteClient = (int*)ListItr_Remove(ListItr_Prev(currItr));
                    free(deleteClient);
                }
                --activity;
            }
        }
    }
    DestroyServer(sockListen, clients);
    return 0;
}


int NoBlockinSock(int _socket)
{
    int flags;

    if (FAIL == (flags = fcntl(_socket, F_GETFL)))
    {
        perror("error at fcntl. F_GETFL.");
        return _socket;
    }
    if (FAIL == fcntl(_socket, F_SETFL, flags | O_NONBLOCK))
    {
        perror("error at fcntl. F_SETFL.");
    }
    return _socket;
}


int Init_Server()
{
    struct sockaddr_in sin;
    int sockListen, optval = 1;

    sockListen = socket(AF_INET, SOCK_STREAM, 0);
    if (sockListen < 0)
    {
        perror("socket failed");
        return FAIL;
    }
    sockListen = NoBlockinSock(sockListen);

    if (setsockopt(sockListen, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse error");
        return FAIL;
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(PORT);

    if( bind(sockListen, (struct sockaddr *) &sin , sizeof(sin)) < 0)
    {
        perror("bind failed");
        return FAIL;
    }

    if (listen(sockListen, MAX_OF_CLIENTS))
    {
        perror("listen error");
        return FAIL;
    }
    return sockListen;
}


int CheckNewClient(int _listenSock, List* _clients, fd_set* _master)
{
    struct sockaddr_in client_sin;
    int clientSock, i;
    unsigned int addr_sin = sizeof(client_sin);
    int* pCurrClient = NULL;

    for (i = 0; i < GET_N_CLIENTS; ++i)
    {
        clientSock = accept(_listenSock, (struct sockaddr*) &client_sin, &addr_sin);
        if (List_Size(_clients) >= MAX_OF_CLIENTS)
        {
            close(clientSock);
            return FAIL;
        }
        if (clientSock < 0)
        {
            return FAIL;
        }
        if ((pCurrClient = (int*) malloc(sizeof(int))) == NULL)
        {
            return FAIL;
        }
        *pCurrClient = clientSock;
        FD_SET(clientSock, _master);
        List_PushHead(_clients, pCurrClient);
    }
    return clientSock;
}

int CheckCurrentClient(int _clientSock)
{
    int read_byte, sent_byte;
    char buffer[5000];
    char *str = "Hi, you were connected to Ofir's server!";
    int dataLen = strlen(str);

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
        buffer[read_byte] = '\0';
        printf("Server : %s\n", buffer);
        sent_byte = send(_clientSock, str, dataLen, 0);
        if (sent_byte < 0)
        {
            perror("send failed");
        }
    }
    return OK;
}

void DestroySock(void* _clientSock)
{
    close(*((int*)_clientSock));
    free((int*)_clientSock);
}

void DestroyServer(int _listenSock, List* _clients)
{

    close(_listenSock);
    List_Destroy(&_clients, DestroySock);
}
/*
    sockListen = socket(AF_INET, SOCK_STREAM, 0);
    if (sockListen < 0)
    {
        perror("socket failed");
    }

    if (setsockopt(sockListen, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("reuse error");
    }

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(PORT);

    if( bind(sockListen, (struct sockaddr *) &sin , sizeof(sin)) < 0)
    {
        perror("bind failed");
    }

    if (listen(sockListen, MAX_OF_CLIENTS))
    {
        perror("listen error");
    }

    clientSock = accept(sockListen, (struct sockaddr*) &client_sin, &addr_sin);
    if (clientSock < 0)
    {
        perror("accept Failed");
    }

    read_byte = recv(clientSock, buffer, sizeof(buffer), 0);

    if (read_byte == 0)
    {
        close(clientSock);
    }
    else if (read_byte < 0)
    {
        perror("rcvfrom failed");
    }
    else
    {
        buffer[read_byte] = '\0';
        printf("Server : %s\n", buffer);
    }

    sent_byte = send(clientSock, str, dataLen, 0);
    if (sent_byte < 0)
    {
        perror("send failed");
    }

    close(sockListen);
*/
