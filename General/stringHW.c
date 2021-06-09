#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int IsNumChar(char _c) 
{ 
    return (_c >= '0' && _c <= '9') ? 1 : 0;
} 

int MyAtoi(char* str) 
{ 
	int res = 0; 
    int sign = 1; 
    int i = 0; 
    if (*str == '\0')
    {
        return 0; 
	}
    while (str[i] == ' ')
    { 
        i++; 
    }
    if (str[i] == '-')
    { 
        sign = -1; 
        i++; 
    }
    else if(str[i] == '+')
    { 
        sign = 1; 
        i++; 
    } 
    for (; str[i] != '\0'; ++i)
    { 
        if (!IsNumChar(str[i])) 
            break;
        res = res * 10 + str[i] - '0'; 
    } 
    return sign * res; 
}

void squeeze(char s1[],char s2[])
{
	int i,j,k;
	int found = 0;
	for(i=0,j=0; s1[i] != '\0'; i++)
	{
		for(k=0; s2[k] != '\0'; k++)
		{
			if(s1[i] == s2[k])
			{
				found = 1;
				break;
			}
		}
		if(!found)
		{
			s1[j++] = s1[i];
		}
		found = 0;
	}
	s1[j] = '\0';
}

int compare(char* s1,char* s2)
{
	while(*s1 && *s2)
	{
		if(*s1 != *s2)
		{
			return 0;
		}
		s1++;
		s2++;
	}
	return (*s2 == '\0');
}

int location(char* s1,char* s2)
{
	int i = 0;
	while(*s1 != '\0')
	{
		if((*s1 == *s2) && compare(s1,s2))
		{
			return i;
		}
		s1++;
		i++;
	}
	return -1;
}

int main()
{	
	int val;
	char* x = "dbbbc";
	char* y = "bbc";
	
	char str[20];
	char str2[] = " -44 55";
	char s[] = "Have a nice day";
	char q[] = "ai";
	printf("%d\n",location(x,y));
	printf("%s\n",s);
	squeeze(s,q);
	printf("%s\n",s);
	
    val = MyAtoi(str2);
    printf("%d ", val);
    
	MyItoa(0,str);
	printf("%s\n",str);
	
	return 0;
}
