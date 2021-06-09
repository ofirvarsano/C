#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 256
#define BYTES_TO_READ 200
#define ERR_FAIL	0
#define ERR_OK		1
typedef int ERR;

ERR CharFreq(char _fileName[])
{
	int i = 0;
	FILE* fp;
	int freq[SIZE] = {0};
	char str[BYTES_TO_READ];
	int num = 0;
	fp = fopen(_fileName,"r");
	
	if(!fp)
	{
		return ERR_FAIL;
	}
	num = fread(str,sizeof(char),BYTES_TO_READ,fp);
	while(num > 0)
	{
		for(i = 0; str[i] != '\0'; i++)
		{
			freq[(int)str[i]]++;
		}
		num = fread(str,sizeof(char),BYTES_TO_READ,fp);
	}
	for(i = 0; i < SIZE; i++)
	{
		if(freq[i] != 0 && isalpha((char)i))
		{
			printf("%c %d\n", i, freq[i]);
		}
	}
	return ERR_OK;
}

int main() 
{
	CharFreq("abc.txt");
    
    return 0; 
} 


