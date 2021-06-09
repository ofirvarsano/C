#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#define SERVER_PORT 1233
#define ARRAY_SIZE 3000
#define DISCONNECT  -1

void Reverse(char s[])
{
	int i, j;
	char c;
 
	for (i = 0, j = strlen(s)-1; i<j; i++, j--)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
 
void MyItoa(int _n, char s[])
{
     int i, sign;
 
     if ((sign = _n) < 0)
     {
         _n = -_n;
     }
     i = 0;
     do 
     {
		s[i++] = _n % 10 + '0';
     }while ((_n /= 10) > 0);
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     Reverse(s);
}

void Client_TCP()
{
    int* arr;
    int read_bytes;
    struct sockaddr_in sin;
    char buffer[4096];
    char datagram[50] = "just like whatsapp ";
    int expected_data_len = sizeof(buffer);
    int send_bytes, data_len = 50, optval = 1, sock;
    int i, num;
    char str[20];
    int count = 30;

    arr = (int*)malloc(ARRAY_SIZE * sizeof(int));
    for ( i = 0; i < ARRAY_SIZE; ++i)
    {
        arr[i] = DISCONNECT;
    }
    srand(time(NULL));
    while (1)
    {
        for ( i = 0; i < ARRAY_SIZE; ++i)
        {
            strcpy(datagram,"just like whatsapp ");
            num = rand() % 100;
            if (arr[i] < 0)
            {
                if (num < 30)
                {
                    sock = socket(AF_INET, SOCK_STREAM, 0);
                    if (sock < 0)
                    {
                        perror("failed connection to socket\n");
                        continue;
                    }

                    memset (&sin, 0, sizeof(sin));
                    sin.sin_family = AF_INET;
                    /*
                    sin.sin_addr.s_addr = inet_addr("192.168.0.227");
                    */
                    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
                    sin.sin_port = htons(SERVER_PORT);
                    
                    if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
                    {
                        perror("connect error\n");
                        continue;
                    }
                    arr[i] = sock;
                }
            }
            else
            {
                if (num < 5)
                {
                    close(arr[i]);
                    arr[i] = DISCONNECT;
                }
                else if (num > 70)
                {
                    MyItoa(arr[i], str);
                    strcat(datagram, str);
                    printf("count: %d\n",count);
                    printf("socket: %d\n",arr[i]);
                    printf("index: %d\n",i);

                    send_bytes = send(arr[i], datagram, strlen(datagram), 0);
                    if (send_bytes < 0)
                    {
                        perror("send func failed\n");
                        continue;
                    }

                    read_bytes = recv(arr[i], buffer, expected_data_len, 0);
                    if (read_bytes < 0)
                    {
                        perror("recv failed\n");
                    }
                    else if(read_bytes == 0)
                    {
                        close(arr[i]);
                        arr[i] = DISCONNECT;
                    }
                    else if(read_bytes > 0)
                    {
                        printf("server said: %s\n", buffer);
                    }  
                }
            }
        }
    }

    for ( i = 0; i < ARRAY_SIZE; ++i)
    {
        close(arr[i]);
        arr[i] = DISCONNECT;
    }
    free(arr);
}

int main()
{
    Client_TCP();
    return 0;
}