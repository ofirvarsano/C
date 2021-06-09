#include "vector.h"
#include <stdio.h>

#define EXNUM	8
#define EXIT	0

#define CREATE_VEC		1
#define ADD_END			2
#define REMOVE_ITEM		3
#define PRINT_VEC		4
#define NUM_ITEMS		5
#define GET_ITEM		6
#define SET_ITEM		7
#define DESTROY_VEC		8

void PrintOptions()
{
	printf("1---> Create Vector\n");
	printf("2---> Add Item\n");
	printf("3---> Remove Item\n");
	printf("4---> Print Items\n");
	printf("5---> Get num of items\n");
	printf("6---> Get item by index\n");
	printf("7---> Set item by index\n");
	printf("8---> Destroy\n");
	printf("%d---> EXIT\n\n",EXIT);
}

void Menu()
{
	size_t size;
	ADTErr err;
	size_t blockSize;
	int select,tempItem,index;
	Vector* vecPtr = NULL;

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
			case CREATE_VEC:
					if(vecPtr != NULL)
					{
						printf("a Vector exist already\n");
						break;
					}
					printf("Enter Size\n");
					scanf("%lu",&size);
					printf("Enter Block Size\n");
					scanf("%lu",&blockSize);
					if((vecPtr = VectorCreate(size,blockSize)))
					
					{
						printf("Vector Created\n");
					}
					break;
			case ADD_END:
						printf("Enter item to add\n");
						scanf("%d",&tempItem);
						VectorAddEnd(vecPtr,tempItem);
						break;
			case REMOVE_ITEM:
						err = VectorDeleteEnd(vecPtr,&tempItem);
						if(err == ERR_OK)
						{
							printf("%d deleted\n",tempItem);
						}
						break;
			case PRINT_VEC: 
						VectorPrint(vecPtr);
						break;
			case NUM_ITEMS:
						err = VectorItemsNum(vecPtr,&tempItem);
						if(err == ERR_OK)
						{
							printf("there are %d items\n",tempItem);
						}                                                                                                 
						break;
			case GET_ITEM:
						printf("Enter item index to get\n");
						scanf("%d",&index);
						err = VectorGet(vecPtr,index,&tempItem);
						if(err == ERR_OK)
						{
							printf("item %d is: %d\n",index,tempItem);
						}
						break;
			case SET_ITEM:
						printf("Enter index to set\n");
						scanf("%d",&index);
						printf("Enter item value to set\n");
						scanf("%d",&tempItem);
						err = VectorSet(vecPtr,index,tempItem);
						break;
			case DESTROY_VEC: VectorDestroy(vecPtr);
							vecPtr = NULL;break;
		}
	}while(select);
	
	if(vecPtr)
	{
		VectorDestroy(vecPtr);
	}
}

int main()
{
	Menu();
	return 0;
}
