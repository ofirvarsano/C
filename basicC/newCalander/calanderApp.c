#include "calander.h"

void PrintOptions()
{
	printf("1---> Create AD\n");
	printf("2---> Create meeting\n");
	printf("3---> Insert meeting into AD\n");
	printf("4---> Remove appointment\n");
	printf("5---> Print AD\n");
	printf("6---> Find Meeting\n");
	printf("7---> Store AD\n");
	printf("8---> Load AD from file\n");
	printf("9---> Destroy\n");
	printf("%d---> EXIT\n\n",EXIT);
}

void Menu()
{
	size_t size;
	size_t blockSize;
	size_t temp;
	float beginHour;
	float begin;	
	float end;
	int room;
	int beginH;
	int beginM;
	int select;
	char fileName[40];
	meeting* tempMeeting = NULL;
	AD* adPtr = NULL;

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
			case CREATE_AD:
					if(adPtr != NULL)
					{
						printf("an AD exist already\n");
						break;
					}
					printf("Enter Size\n");
					scanf("%lu",&size);
					printf("Enter Block Size\n");
					scanf("%lu",&blockSize);
					if((adPtr = CreateAD(size,blockSize)))
					{
						printf("Appointment Diary Created\n");
					}
					break;
					
			case CREATE_MEETING:	printf("Enter begin time\n");
					scanf("%f",&begin);
					printf("Enter end time\n");
					scanf("%f",&end);
					if((end<=begin) || begin > 24 || begin < 1 || end > 24 || end < 1)
					{
						printf("Invalid meeting hours\n");
						break;
					}
					printf("Enter room number\n");
					scanf("%d",&room);
					if((tempMeeting = CreateMeeting(begin,end,room)))
					{
						printf("Meeting Created\n");
					}
					break;
			case INSERT_MEETING: if(InsertMeeting(adPtr,tempMeeting))
					{
						printf("Meeting Added\n");
					}
					else
					{
						printf("Meeting can't be added!\n");
					}
					break;
					
			case REMOVE_MEETING: printf("Pick meeting to delete by begin hour\n");
					scanf("%f",&beginHour);
					RemoveMeeting(adPtr,beginHour)? printf("Meeting deleted\n") : printf("Meeting can't be deleted!\n");
					break;
					
			case PRINT_AD: PrintAD(adPtr);break;
			
			case FIND_MEETING: printf("Pick meeting to find by begin hour\n");
					scanf("%f",&beginHour);
					temp = FindMeeting(adPtr,beginHour);
					if(temp)
					{
						beginH = (int)adPtr->m_day[temp-1]->m_begin;
						beginM = (int)(adPtr->m_day[temp-1]->m_begin *10)%10;
						
						printf("Meeting at %02d:%d0 is meething number %lu\n",beginH,beginM,temp);
					}
					else
					{
						printf("No such meeting\n");
					}
					break;
					
			case STORE_AD:	printf("Enter File Name\n");
							scanf("%s",fileName);
							strcat(fileName,".txt");
							if((StoreAD(adPtr,fileName)))
							{
								printf("AD Saved!\n");
							}
							else
							{
								printf("Can't save file\n");
							}
							break;
					
			case LOAD_AD: if(adPtr != NULL)
							{
								printf("an AD exist already\n");
								break;
							}
						printf("Enter file name to load from\n");
						scanf("%s",fileName);
						strcat(fileName,".txt");
						if((adPtr = LoadAD(fileName)))
						{
							printf("AD loaded from file\n");
						}
						else
						{
							printf("file load failed\n");
						}
						break;
						
			case DESTROY_AD: DestroyAD(&adPtr);break;
		}
	}while(select);
	
	if(adPtr)
	{
		DestroyAD(&adPtr);
	}
	if(NULL != tempMeeting)
	{
		free(tempMeeting);
	}
}

int main()
{
	Menu();
	return 0;
}
