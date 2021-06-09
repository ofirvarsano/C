#include "vector.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>
#define BALANCED	1
#define NOT_BALANCED 0

int CasePop(Stack* _ptr,char _c)
{
	int x;
	if(StackIsEmpty(_ptr))
	{
		return NOT_BALANCED;
	}
	StackPop(_ptr,&x);
	if(x != _c)
	{
		return NOT_BALANCED;
	}
	return BALANCED;
}

int isCorrect(char* _str)
{
	int i;
	char c;
	size_t len;
	Stack* stackPtr = NULL;
	if(NULL == _str)
	{
		return NOT_BALANCED;
	}
	len = strlen(_str);
	if(len == 0)
	{
		return BALANCED;
	}
	stackPtr = StackCreate(len,2);
	if(NULL == stackPtr)
	{
		return NOT_BALANCED;
	}
	for(i=0; i<len; i++)
	{
		c = _str[i];
		switch(c)
		{
			case '(':
			case '{':
			case '[': StackPush(stackPtr,(int)c);
						break;
			
			case ')': if(!CasePop(stackPtr,'('))
						{
							return NOT_BALANCED;
						}
						break;
			case '}': if(!CasePop(stackPtr,'{'))
						{
							return NOT_BALANCED;
						}
						break;			
			case ']': if(!CasePop(stackPtr,'['))
						{
							return NOT_BALANCED;
						}
						break;
			case ' ':
			default: break;
		}
	}
	if(!StackIsEmpty(stackPtr))
	{
		return NOT_BALANCED;
	}
	return BALANCED;
}

int main()
{
	char str[100];
	printf("Enter a phrase\n");
	scanf("%[^\n]%*c",str);
	isCorrect(str) ? printf("Phrase is balanced\n") : printf("Phrase is not balanced\n");
	return 0;
}
