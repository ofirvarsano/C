#include "wordTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ERR_FAIL	0
#define ERR_OK		1
#define SIZE		100
typedef int ERR;

ERR wordFrequency(char* _fileName)
{
	FILE* fp;
	char str[SIZE];
	const char s[] = " \n-:";
	char *token;
	Tree* tree = TreeCreate();
	fp = fopen(_fileName,"r");
	
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
			TreeInsert(tree,token);
			token = strtok(NULL,s);
		}
		fgets(str,SIZE,fp);
	}
	fclose(fp);
	TreePrint(tree,IN_ORDER);
	TreeDestroy(tree);
	
	return ERR_OK;
}

int main()
{
	wordFrequency("txtWordFreq.txt");
	return 0;
}
