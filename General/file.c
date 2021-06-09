#include <stdio.h>
#include <stdlib.h>

int CountL(FILE* _f,int seek)
{
	int countLines = 0;
	char str[100];
	fseek(_f,seek,SEEK_END);
	fgets(str,90,_f);
	while(!feof(_f))
	{
		++countLines;
		fgets(str,90,_f);
	}
	return countLines;
}

void LastN(char* _fileName, int _n)
{
	FILE* fp;
	int countLines = 0;
	char str[100];
	int seek = -5;
	fp = fopen(_fileName,"r");
	
	if(!fp)
	{
		exit(0);
	}
	countLines = CountL(fp,seek);
	while(countLines < _n + 1 && ftell(fp) != 0)
	{
		seek -= 5;
		countLines = CountL(fp,seek);
	}

	fseek(fp,seek,SEEK_END);
	fgets(str,90,fp);
	while(!feof(fp))
	{
		printf("%s\n",str);
		fgets(str,90,fp);
	}
	fclose(fp);
}

int main()
{
	int lines;
	/*char fileName1[100];
	printf("Enter file name\n");
	scanf("%s",fileName1);*/
	printf("Enter number of lines to print\n");
	scanf("%d",&lines);
	LastN("abc.txt",lines);
	return 0;
}
