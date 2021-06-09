#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "stack.h"
#define SIZE 100
#include <ctype.h>
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

int Precedence(char _symbol)
{
	switch(_symbol)
	{
		case '^': return 3; break;
		case '*':
		case '/': return 2; break;
		case '+':
		case '-': return 1; break;
		default: return 0; break;
	}
}

int IsOperator(char _symbol)
{
	if(_symbol == '^' || _symbol == '*' || _symbol == '/' || _symbol == '+' || _symbol == '-')
	{
		return 1;
	}
	return 0;
}

void InfixToPostfix(char _infix[],char _postfix[])
{
	int i,j;
	char item;
	int x;
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(strlen(_infix),2);
	if(stackPtr == NULL)
	{
		return;
	}

	i=0;
	j=0;
	item = _infix[i];
	while(item != '\0')
	{
		if(item == '(')
		{
			StackPush(stackPtr,item);
		}
		else if(isdigit(item) || isalpha(item))
		{
			_postfix[j] = item;
			j++;
		}
		else if(IsOperator(item))
		{
			while(!StackIsEmpty(stackPtr))
			{
				StackPop(stackPtr,&x);
				if(x =='(' || Precedence(x) < Precedence(item))
				{
					StackPush(stackPtr,x);
					break;
				}
				_postfix[j] = x;
				j++;
			}
			StackPush(stackPtr,item);
		}
		else if(item == ')')
		{
			while(!StackIsEmpty(stackPtr))
			{
				StackPop(stackPtr,&x);
				if(x =='(') break;
				_postfix[j] = x;
				j++;
			}
		}
		else
		{
			printf("Invalid infix\n");
			return;
		}
		i++;
		item = _infix[i];
	}
	
	while(!StackIsEmpty(stackPtr))
	{
		StackPop(stackPtr,&x);
		_postfix[j] = x;
		j++;
	}
	_postfix[j] = '\0';
}

int EvaluatePostfix(char* _exp)
{
	int i,val1,val2,result;
	Stack* stackPtr = NULL;
	stackPtr = StackCreate(strlen(_exp),2);
	if(stackPtr == NULL)
	{
		return 0;
	}

	for(i=0;_exp[i];i++)
	{
		if(isdigit(_exp[i]))
		{
			StackPush(stackPtr,_exp[i] - '0');
		}
		else if(isalpha(_exp[i]))
		{
			StackPush(stackPtr,_exp[i] - 'a');
		}
		else
		{
			StackPop(stackPtr,&val1);
			StackPop(stackPtr,&val2);
			switch(_exp[i])
			{
				case '+': StackPush(stackPtr,val2 + val1); break;
				case '-': StackPush(stackPtr,val2 - val1); break;
				case '*': StackPush(stackPtr,val2 * val1); break;
				case '/': StackPush(stackPtr,val2 / val1); break;
				case '^': StackPush(stackPtr,val2 ^ val1); break;
			}
		}
	}
	StackPop(stackPtr,&result);
	return result;
}

int main()
{
	char infix[SIZE], postfix[SIZE];
	printf("Enter infix expression (single digit and single letter variables only!)\n");
	scanf("%s",infix);
	if(!isCorrect(infix))
	{
		return 0;
	}
	InfixToPostfix(infix,postfix);
	printf("Postfix: %s\nResult:  %d\n",postfix,EvaluatePostfix(postfix));
	return 0;
}
