
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h> /*socket*/
#include <time.h> /* rand */
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT     1200
#define MAX_LINE     1024
#define NUM_OF_CLIENTS 1000
#define CONNECT 30
#define SEND_RECV 70
#define ALL_DISCONNECT 100
#define TURN_DISCONNECT 5
#define DISCONNECT_VALUE -1
#define TRUE 1

static void InitDisconnectedArray(int *_arr, int _n);
static void MyItoa(int _n, char s[]);
static void Reverse(char s[]);

int main ()
{
    int sent_byte, read_byte, num, i = 0, count = 2000;
    struct sockaddr_in sin;
    char str[50] = "I'm client:";
    char buffer[MAX_LINE];
    size_t bufferLen = sizeof(buffer), str_len = strlen(str) + 5;
    char clientNum[20];


    int* arr = malloc(NUM_OF_CLIENTS * sizeof(int));
    InitDisconnectedArray(arr, NUM_OF_CLIENTS);

    srand(time(NULL));

    while (TRUE)
    {
        num = rand() % ALL_DISCONNECT;
        strcpy(str, "I'm client:");

        if (arr[i] == DISCONNECT_VALUE)
        {
            if (num < CONNECT)
            {
                arr[i] = socket(AF_INET, SOCK_STREAM, 0);
                if (arr[i] < 0)
                {
                    perror("socket failed");
                    i = (i + 1) % NUM_OF_CLIENTS;
                    --count;
                    continue;
                }
                memset(&sin, 0, sizeof(sin));
                sin.sin_family = AF_INET;
                sin.sin_addr.s_addr = inet_addr("192.168.0.92");
                sin.sin_port = htons(PORT);

                if (connect(arr[i], (struct sockaddr *) &sin, sizeof(sin)) < 0)
                {
                    perror("connection failed");
                    i = (i + 1) % NUM_OF_CLIENTS;
                    --count;
                    continue;
                }
            }
        }
        else
        {
            if (num < TURN_DISCONNECT)
            {
                close(arr[i]);
                arr[i] = DISCONNECT_VALUE;
            }

            if (num > SEND_RECV)
            {
                MyItoa(i, clientNum);
                strcat(str, clientNum);

                sent_byte = (int)send(arr[i], str, str_len, 0);
                if (sent_byte < 0)
                {
                    perror("send failed");
                    i = (i + 1) % NUM_OF_CLIENTS;
                    --count;
                    continue;
                }

                read_byte = (int)recv(arr[i], buffer, bufferLen, 0);
                if (read_byte == 0)
                {
                    close(arr[i]);
                    arr[i] = -1;
                }
                else if (read_byte < 0)
                {
                    perror("rcvfrom failed");
                    close(arr[i]);
                    arr[i] = -1;
                }
                else
                {
                    buffer[read_byte] = '\0';
                    printf("Server : %s\n", buffer);
                }

            }
        }
        i = (i + 1) % NUM_OF_CLIENTS;
        --count;
    }

    for ( i = 0; i < NUM_OF_CLIENTS; ++i)
    {
        close(arr[i]);
    }
    free(arr);

    return 0;
}

static void InitDisconnectedArray(int *_arr, int _n)
{
	int i;

	for (i = 0; i < _n; ++i)
	{
        _arr[i] = DISCONNECT_VALUE;
	}
}




static void Reverse(char s[])
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

static void MyItoa(int _n, char s[])
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

