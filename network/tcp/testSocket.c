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


int main()
{
    int temp, i;
    for (i = 0; i < 2000 ; ++i)
    {
        temp = socket(AF_INET, SOCK_STREAM, 0);
        printf("socket num : %d\n", temp);
    }
    return 0;
}