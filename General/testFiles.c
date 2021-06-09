#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 50
#define ERR_FAIL	0
#define ERR_OK		1

typedef int ERR;

ERR getFile(char fileName[],char word[])
{
	FILE* fp;
	const char s[] = " \n";
	char *token;
	char str[SIZE];
	fp = fopen("SOMEFILE.txt","r");
	if(!fp)
	{
		return ERR_FAIL;
	}
	fgets(str,SIZE,fp);
	if(!feof(fp))
	{
		token = strtok(str,s);
		if(token != NULL)
		{
			strcpy(fileName,token);
			token = strtok(NULL,s);
		}
		if(token != NULL)
		{
			strcpy(word,token);
		}
	}
	fclose(fp);
	return ERR_OK;
}

ERR wordOccurrences()
{
	FILE* fp;
	char str[SIZE];
	int countWord = 0;
	char word[SIZE];
	char fileName[SIZE];
	const char s[] = " \n";
	char *token;
	
	getFile(fileName,word);
	fp = fopen(fileName,"r");
	
	if(!fp)
	{
		return ERR_FAIL;
	}
	fgets(str,SIZE,fp);
	while(!feof(fp))
	{
		token = strtok(str,s);
		while(token != NULL)
		{
			if(strcmp(word,token) == 0)
			{
				++countWord;
			}
			token = strtok(NULL,s);
		}
		fgets(str,SIZE,fp);
	}
	printf("In file %s the word %s appeared %d times.\n",fileName,word,countWord);
	fclose(fp);
	
	return ERR_OK;
}

int main()
{
	wordOccurrences();
	return 0;
}
