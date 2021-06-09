#include "vector.h"
#include "stack.h"
#include <stdio.h>

#define EXNUM	7
#define EXIT	0

#define CREATE_STACK	1
#define PUSH			2
#define POP				3
#define TOP				4
#define IS_EMPTY		5
#define PRINT			6
#define DESTROY			7

void PrintOptions()
{
	printf("1---> CREATE_STACK\n");
	printf("2---> PUSH\n");
	printf("3---> POP\n");
	printf("4---> TOP\n");
	printf("5---> IS_EMPTY\n");
	printf("6---> PRINT	\n");
	printf("7---> DESTROY\n");
	printf("%d---> EXIT\n\n",EXIT);
}

void Menu()
{
	size_t size;
	ADTErr err;
	size_t blockSize;
	int select,tempItem;
	Stack* stackPtr = NULL;

	do
	{
		PrintOptions();
		do
		{
			select=0;
			printf("Select %d-%d: ",EXIT,EXNUM);
			scanf("%d",&select);
		
		}while((select<EXIT) || (select>EXNUM));
		
		switch(select)
		{
			case CREATE_STACK:
					if(stackPtr != NULL)
					{
						printf("a stack exist already\n");
						break;
					}
					printf("Enter Size\n");
					scanf("%lu",&size);
					printf("Enter Block Size\n");
					scanf("%lu",&blockSize);
					if((stackPtr = StackCreate(size,blockSize)))
					
					{
						printf("stack Created\n");
					}
					break;
			case PUSH:
						printf("Enter item to add\n");
						scanf("%d",&tempItem);
						StackPush(stackPtr,tempItem);
						break;
			case POP:
						err = StackPop(stackPtr,&tempItem);
						if(err == ERR_OK)
						{
							printf("%d poped\n",tempItem);
						}
						break;
			case PRINT: 
						StackPrint(stackPtr);
						break;
			case TOP:
						err = StackTop(stackPtr,&tempItem);
						if(err == ERR_OK)
						{
							printf("Top item: %d\n",tempItem);
						}                                                                                                 
						break;
			case IS_EMPTY:
						if(StackIsEmpty(stackPtr))
						{
							printf("Empty\n");
						}
						else
						{
							printf("Not Empty\n");
						}
						break;

			case DESTROY: StackDestroy(stackPtr);
							stackPtr = NULL;break;
		}
	}while(select);
	
	if(stackPtr)
	{
		StackDestroy(stackPtr);
	}
}

int main()
{
	Menu();
	return 0;
}
