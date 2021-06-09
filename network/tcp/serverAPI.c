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

#define SERVER_PORT     1233
#define MAXFD           1024
#define N_CLIENTS       5
#define MAX_OF_CLIENTS  1010
#define CLOSE           -1
#define FAIL            -1
#define OK              1

typedef struct Server Server;
typedef void (*gotMsg)(char* buffer, int sock, int size);
typedef void (*newClient)();
typedef void (*closeClient)(int sock);
typedef void (*failClient)();

static void Unblock_Sock(int* _sock);
static int initialListener();
static void acceptClients(Server* server, int* client_sock);
static int CheckCurrentClient(Server* server, int _clientSock);
void destroyInt(void* _element);

struct Server
{
    List* m_clients;
    gotMsg m_gotMsg;
    newClient m_newClientFunc;
    closeClient m_closeClientFunc;
    failClient m_failClientFunc;
    int m_maxClients;
    int m_sockListen;
    fd_set m_masterfd;
    int m_numOfClients;
};

Server* ServerCreate(int maxClients, gotMsg msgFunc, newClient newClientFunc, closeClient closeClientFunc, failClient failClientFunc)
{
    Server* server = NULL;
    List* clientsList = NULL;

    if (maxClients <= 0 || maxClients > 1000 || msgFunc == NULL)
    {
        return NULL;
    }
    clientsList = List_Create();
    if (clientsList == NULL)
    {
        return NULL;
    }
    server = (Server*)malloc(sizeof(Server));
    if (server == NULL)
    {
        List_Destroy(&clientsList, NULL);
        return NULL;
    }
    server->m_clients = clientsList;
    server->m_maxClients = maxClients;
    server->m_numOfClients = 0;
    server->m_gotMsg = msgFunc;
    server->m_closeClientFunc = closeClientFunc;
    server->m_failClientFunc = failClientFunc;
    server->m_newClientFunc = newClientFunc;
    server->m_sockListen = initialListener(maxClients);

    if (server->m_sockListen == FAIL)
    {
        if (server->m_failClientFunc)
        {
            server->m_failClientFunc();
        }
        List_Destroy(&clientsList, NULL);
        free(server);
        return NULL;
    }
    FD_ZERO(&server->m_masterfd);
    FD_SET(server->m_sockListen, &server->m_masterfd);

    return server;
}

void ServerDestroy(Server** server)
{
    if (server && *server)
    {
        List_Destroy(&((*server)->m_clients), destroyInt);
        close((*server)->m_sockListen);
        free(*server);
        *server = NULL;
    }
}

void ServerRun(Server* server)
{
    fd_set tempfd;
    int activity, i, data, client_sock;
    int* curClient;
    ListItr curr, end;
    int* deleteClient = NULL;

    while(1)
    {
        tempfd = server->m_masterfd;
        activity = select(MAXFD, &tempfd , NULL , NULL , NULL);

        if (activity < 0 && errno != EINTR)
        {
            break;
        }

        if (activity > 0 && FD_ISSET(server->m_sockListen, &tempfd))
        {
             /* New client await */
            acceptClients(server, &client_sock);
            --activity;
        }
        curr = ListItr_Begin(server->m_clients);
        end = ListItr_End(server->m_clients);

        while (activity > 0 && curr != end)
        {
            data = *(int*)ListItr_Get(curr);
            curr = ListItr_Next(curr);
            if (FD_ISSET(data, &tempfd))
            {
                if (CLOSE == CheckCurrentClient(server, data))
                {
                    close(data);
                    server->m_numOfClients--;
                    FD_CLR(data, &server->m_masterfd);
                    deleteClient = (int*)ListItr_Remove(ListItr_Prev(curr));
                    free(deleteClient);
                    if (server->m_closeClientFunc)
                    {
                        server->m_closeClientFunc(data);
                    }
                }
                --activity;
            }
        }
    }
}

void ServerSendMessage(Server* server, char* message, int size, int clientSock)
{
    int sent_bytes;

    sent_bytes = send(clientSock, message, size, 0);
    if (sent_bytes < 0 && server->m_failClientFunc)
    {
        server->m_failClientFunc();
    }
}

static int initialListener(int maxClients)
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

    if (listen(sock, maxClients) < 0)
    {
        perror("listen failed\n");
        return FAIL;
    }
    return sock;
}

static void Unblock_Sock(int* _sock)
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

static int CheckCurrentClient(Server* server, int _clientSock)
{
    int read_byte;
    char buffer[4096];
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
        server->m_gotMsg(buffer, _clientSock, read_byte);
    }
    return OK;
}

static void acceptClients(Server* server, int* client_sock)
{
    int i;
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int* curClient;
    /* New client await */
    for (i = 0; i < N_CLIENTS; ++i)
    {
        *client_sock = accept(server->m_sockListen, (struct sockaddr*) &client_sin, &addr_len);
        if(*client_sock >= 0)
        {
            if (server->m_numOfClients >= server->m_maxClients)
            {
                close(*client_sock);
                if (server->m_closeClientFunc)
                {
                    server->m_closeClientFunc(*client_sock);
                }
            }
            else
            {
                curClient = (int*)malloc(sizeof(int));
                *curClient = *client_sock;
                List_PushHead(server->m_clients, curClient);
                server->m_numOfClients++;
                FD_SET(*client_sock, &server->m_masterfd);
                if (server->m_newClientFunc)
                {
                    server->m_newClientFunc();
                }
            }
        }
    }
}
