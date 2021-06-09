#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CH_SIZE 4

int toValue(char ch);
char* encode(char str[]);
void printStringInBits(char str[]);
void printCharBits(unsigned char number,int n);
void setBites(char str[],int j,int size,unsigned int cVal);

int main()
{
	char str[] = "abcdef";
	printStringInBits(str);
	printf("\n");
	
	encode(str);
	
	printStringInBits(str);
	
	return 0;
}

void setBites(char str[],int j,int size,unsigned int cVal)
{
	int e,k;
	for(k = 0; k < CH_SIZE ; k++)
	{
		e = cVal & (1 << k);
		if(e)
		{
			str[j] |= (1 << (k + size));
		}
		else
		{
			str[j] &= ~(1 << (k + size));
		}
	}
}

char* encode(char str[])
{
	unsigned int cVal;
	char c;
	int j = 0;
	int i = 0;
	
	for(i = 0,j = 0; str[i] != '\0'; i++, j++)
	{
		c = str[i];
		cVal = toValue(c);
		setBites(str,j,CH_SIZE,cVal);

		i++;
		c = str[i];
		if(c == '\0')
		{
			setBites(str,j,0,0);
			j++;
			break;
		}
		cVal = toValue(c);
		setBites(str,j,0,cVal);
	}
	str[j] = '\0';

	return str;
}

int toValue(char ch)
{
	int chVal = 0;
	switch(ch)
	{
		case ' ': chVal=0;break;
		case 'a': chVal=1;break;
		case 'b': chVal=2;break;
		case 'c': chVal=3;break;
		case 'd': chVal=4;break;
		case 'e': chVal=5;break;
		case 'f': chVal=6;break;
		case 'g': chVal=7;break;
		case 'h': chVal=8;break;
		case 'i': chVal=9;break;
		case 'j': chVal=10;break;
		case 'k': chVal=11;break;
		case 'l': chVal=12;break;
		case 'm': chVal=12;break;
		case 'n': chVal=14;break;
		case 'o': chVal=15;break;
		default: chVal=0;break;
	}
	return chVal;
}

void printCharBits(unsigned char number,int n)
{
	int bit;
	if(number || n)
	{
		printCharBits(number >>1,n-1);
		bit = (number & 1) ? 1 : 0;
		printf("%d",bit);
	}
}

void printStringInBits(char str[])
{
	int i;
	for(i = 0; str[i] != '\0'; i++)
	{
		printCharBits(str[i],8);
		printf("\n");
	}
}

