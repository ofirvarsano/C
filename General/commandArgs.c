#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc,char* argv[])
{
	int num1,num2;

	if(argc < 3)
	{
		return 0;
	}
	/*CAN USE sscanf(argv[1],"%d",&num1);*/
	num1 = MyAtoi(argv[1]);
	num2 = MyAtoi(argv[2]);
	printf("%d * %d = %d\n",num1,num2,num1*num2);
	printf("%d + %d = %d\n",num1,num2,num1+num2);
	
	return 0;
}
