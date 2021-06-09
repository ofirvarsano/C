#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXNUM	3
#define EXIT	0
void FileCompare(char* _fileName1,char* _fileName2);
int CountLines(char* _fileName);
void CountLinesAndWords(char* _fileName);
void LastN(char* _fileName, int _n);
enum options 
{PRINT_LAST_N=1,
COMPARE_FILES,
COUNT_LINES_WORDS};

void FileCompare(char* _fileName1,char* _fileName2)
{
	char str1[100];
	char str2[100];
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	int s;
	
	fp1 = fopen(_fileName1,"r");
	if(!fp1)
	{
		exit(0);
	}
	fp2 = fopen(_fileName2,"r");
	if(!fp2)
	{
		fclose(fp1);
		exit(0);
	}
	do
	{
		fgets(str1,90,fp1);
		fgets(str2,90,fp2);
		s = strcmp(str1,str2);
		if(s)
		{
			printf("%d\n",s);
		}
	}while(!feof(fp1) && !feof(fp2));

	fclose(fp1);
	fclose(fp2);
}

int CountLines(char* _fileName)
{
	int count = 0;
	char str[100];
	FILE* fp = NULL;
	
	fp = fopen(_fileName,"r");
	if(!fp)
	{
		return 0;
	}
	do
	{
		fgets(str,90,fp);
		++count;
	}while(!feof(fp));
	--count;
	fclose(fp);
	return count;
}

void CountLinesAndWords(char* _fileName)
{
	int countWords = 0;
	int countLines = 0;
	char c;
	FILE* fp = NULL;
	
	countLines = CountLines(_fileName);
	fp = fopen(_fileName,"r");
	if(!fp)
	{
		exit(0);
	}
	while((c=fgetc(fp)) != EOF)
	{
		if(c==' ' || c =='\n')
		{
			countWords++;
		}
	}
	
	printf("Lines: %d words: %d\n",countLines, countWords);
	fclose(fp);
}

void LastN(char* _fileName, int _n)
{
	int i;
	FILE* fp = NULL;
	int countLines = 0;
	char str[100];
	countLines = CountLines(_fileName);
	fp = fopen(_fileName,"r");
	if(!fp)
	{
		exit(0);
	}
	
	for(i=0;i<countLines-_n;i++)
	{
		fgets(str,90,fp);
	}
	for(;i<countLines;i++)
	{
		fgets(str,90,fp);
		printf("%s\n",str);
	}
	fclose(fp);
}

int main()
{
	int select;
	char fileName1[100];
	char fileName2[100];
	int lines;
	
	do
	{
		printf("1---> Print last N lines\n");
		printf("2---> Compare two files\n");
		printf("3---> Count lines and words\n");
		printf("%d---> EXIT\n\n",EXIT);
		do
		{
			select=0;
			printf("Select %d-%d: ",EXIT,EXNUM);
			scanf("%d",&select);
		
		}while((select<EXIT) || (select>EXNUM));
		
		switch(select)
		{
			case PRINT_LAST_N: printf("Enter file name\n");
								scanf("%s",fileName1);
								strcat(fileName1,".txt");
								printf("Enter number of lines to print\n");
								scanf("%d",&lines);
								LastN(fileName1,lines);
								break;
			case COMPARE_FILES: printf("Enter first file name\n");
								scanf("%s",fileName1);
								strcat(fileName1,".txt");
								printf("Enter second file name\n");
								scanf("%s",fileName2);
								strcat(fileName2,".txt");
								FileCompare(fileName1,fileName2);
								break;
			case COUNT_LINES_WORDS: printf("Enter file name\n");
								scanf("%s",fileName1);
								strcat(fileName1,".txt");
								CountLinesAndWords(fileName1);
								break;
		}
	}while(select);

	return 0;
}
