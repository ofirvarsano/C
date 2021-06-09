#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define EXNUM	7
#define EXIT	0
#define ERROR_ILLIGAL_INPUT 0
#define ERROR_OVERFLOW	0
#define ERROR_UNDERFLOW	0
#define ERROR_NOT_EXIST 0

#define CREATE_AD		1
#define CREATE_MEETING	2
#define INSERT_MEETING	3
#define REMOVE_MEETING	4
#define PRINT_AD		5
#define FIND_MEETING	6
#define DESTROY_AD		7
#define SUCCESS			1

typedef int ErrorCode;

struct meeting
{
	float m_begin;
	float m_end;
	int m_room;
};

struct AD
{
	struct meeting* m_day;
	size_t m_initSize;
	size_t m_blockSize;
	size_t m_actualSize;
	size_t m_numOfMeetings;
};

/*
Description:
function receives init size and block size and creates new AD,
fills its values including a pointer to a new meetings day
*/
struct AD* CreateAD(size_t _initSize, size_t _blockSize)
{
	struct meeting* newDay = NULL;
	struct AD* newAD = (struct AD*)malloc(sizeof(struct AD));
	if(NULL == newAD)
	{
		return newAD;
	}
	newDay= (struct meeting*)malloc(sizeof(struct meeting) * _initSize);
	if(NULL == newDay)
	{
		free(newAD);
		return NULL;
	}
	newAD->m_initSize = _initSize;
	newAD->m_actualSize = _initSize;
	newAD->m_numOfMeetings = 0;
	newAD->m_blockSize = _blockSize;
	newAD->m_day = newDay;
	return newAD;
}

/*
Description:
function destroys the meeting day that AD keeps, and destroys AD
*/
void DestroyAD(struct AD** _ad)
{
	if(*_ad && _ad)
	{
		if((struct AD*)(*_ad)->m_day)
		{
			free((struct AD*)(*_ad)->m_day);
		}
		free(*_ad);
		*_ad = NULL;
		
		printf("AD has been destroyed!\n");
	}
}

/*
Description:
creates a new meeting
*/
struct meeting* CreateMeeting(float _begin, float _end, int _room)
{
	struct meeting* meet = (struct meeting*)malloc(sizeof(struct meeting));
	if(meet)
	{
		meet->m_begin = _begin;
		meet->m_end = _end;
		meet->m_room = _room;
	}
	return meet;
}

void Swap(struct meeting* _meeting1, struct meeting* _meeting2) 
{ 
    struct meeting temp = *_meeting1; 
    *_meeting1 = *_meeting2; 
    *_meeting2 = temp; 
}

void SortAD(struct AD* _ad)
{
	int i, j; 
	int swapped;
	
	if(_ad != NULL && _ad->m_day != NULL)
	{
		for(i=0;i<_ad->m_numOfMeetings;i++)
		{
			swapped = 0; 
			for (j = 0; j < _ad->m_numOfMeetings-i-1; j++) 
			{
				if((_ad->m_day+j)->m_begin > (_ad->m_day+j+1)->m_begin)
				{
					Swap(_ad->m_day+j, _ad->m_day+j+1); 
					swapped = 1;
				}
			}
		if (!swapped) 
		break;
		}
	} 
}

ErrorCode CheckIfLegal(struct AD* _ad, float _begin, float _end)
{
	int i;
	float a,b;
	
	for(i=0;i<_ad->m_numOfMeetings;i++)
	{
		a = _ad->m_day[i].m_begin;
		b = _ad->m_day[i].m_end;
		if(!((_begin < a && _end <= a) || (_begin >= a && _end >b)))
		{
			return ERROR_ILLIGAL_INPUT;
		}
	}
	return SUCCESS;
}

/*
Description:
function 
*/
struct meeting* ResizeArray(struct meeting* _meetings,size_t newSize)
{
	struct meeting* ptrRealloc=NULL;
	ptrRealloc = (struct meeting*)realloc(_meetings,newSize * sizeof(struct meeting));
	if(ptrRealloc)
	{
		printf("Realloc Succeed!\n");
	}
	else
	{
		printf("Realloc Failed!\n");
	}
	return ptrRealloc;
}

ErrorCode InsertMeeting(struct AD* _ad, struct meeting* _newMeet)
{
	struct meeting* newDay = NULL;
	
	if(_ad == NULL || _newMeet == NULL || _ad->m_day == NULL)
	{
		return ERROR_ILLIGAL_INPUT;
	}

	if(CheckIfLegal(_ad,_newMeet->m_begin,_newMeet->m_end))
	{
		if(_ad->m_numOfMeetings >= _ad->m_actualSize)
		{
			newDay = ResizeArray(_ad->m_day,_ad->m_actualSize+_ad->m_blockSize);
			if(NULL == newDay)
			{
				return ERROR_OVERFLOW;
			}
			_ad->m_day = newDay;
			_ad->m_actualSize += _ad->m_blockSize;
		}

		_ad->m_day[_ad->m_numOfMeetings] = *_newMeet;
		_ad->m_numOfMeetings++;
		SortAD(_ad);
		return SUCCESS;
	}
	return ERROR_ILLIGAL_INPUT;
}

void Remove(struct AD* _ad,struct meeting* _meetToDelete,int _i)
{
	int i;
	for(i=_i;i<_ad->m_numOfMeetings-1;i++)
	{
		_ad->m_day[i] = _ad->m_day[i+1];
	}
}

ErrorCode RemoveMeeting(struct AD* _ad,float _beginHour)
{
	int i;
	struct meeting* newDay = NULL;
	if(_ad != NULL && _ad->m_day != NULL)
	{
		for(i=0;i<_ad->m_numOfMeetings;i++)
		{
			if(_ad->m_day[i].m_begin == _beginHour)
			{
				Remove(_ad,_ad->m_day+i,i);
				_ad->m_numOfMeetings--;
				if(_ad->m_actualSize-_ad->m_numOfMeetings > _ad->m_blockSize)
				{
					newDay = ResizeArray(_ad->m_day,_ad->m_numOfMeetings+_ad->m_blockSize);
					if(NULL == newDay)
					{
						return ERROR_OVERFLOW;
					}
					_ad->m_day = newDay;
					_ad->m_actualSize = _ad->m_numOfMeetings+_ad->m_blockSize;
				}
				return SUCCESS;
				break;
			}
		}
		return ERROR_ILLIGAL_INPUT;
	}
	return ERROR_OVERFLOW;
}

size_t FindMeeting(struct AD* _ad,float _begin)
{
	int i;
	if(_ad != NULL && _ad->m_day != NULL)
	{
		for(i=0;i<_ad->m_numOfMeetings;i++)
		{
			if(_ad->m_day[i].m_begin == _begin)
			{
				return i+1;
				break;
			}
		}
		return ERROR_NOT_EXIST;
	}
	return ERROR_UNDERFLOW;
}

void PrintAD(struct AD* _ad)
{
	int i;
	if(_ad != NULL && _ad->m_day != NULL)
	{
		int beginHour,beginMin,endHour,endMin;
		
		
		for(i=0;i<_ad->m_numOfMeetings;i++)
		{
			beginHour = (int)_ad->m_day[i].m_begin;
			beginMin = (int)(_ad->m_day[i].m_begin *10)%10;
			endHour = (int)_ad->m_day[i].m_end;
			endMin = (int)(_ad->m_day[i].m_end *10)%10;
			
			printf("(%d) %02d:%d0-%02d:%d0 in room %d\n",i+1,beginHour,beginMin,endHour,endMin,_ad->m_day[i].m_room);
		}
	}
}

void PrintOptions()
{
	printf("1---> Create AD\n");
	printf("2---> Create meeting\n");
	printf("3---> Insert meeting into AD\n");
	printf("4---> Remove appointment\n");
	printf("5---> Print AD\n");
	printf("6---> Find Meeting\n");
	printf("7---> Destroy\n");
	printf("%d---> EXIT\n\n",EXIT);
}

void Menu()
{
	size_t size;
	size_t blockSize;
	size_t temp;
	float begin;
	float beginHour;
	float end;
	int room;
	int select;
	struct meeting* meeting = NULL;
	struct AD* adPtr = NULL;

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
					if((meeting = CreateMeeting(begin,end,room)))
					{
						printf("Meeting Created\n");
					}
					break;
			case INSERT_MEETING: if(InsertMeeting(adPtr,meeting))
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
					temp=FindMeeting(adPtr,beginHour);
					if(temp)
					{
						printf("Meeting at %.2f is meething number %lu\n",beginHour,temp);
					}
					else
					{
						printf("No such meeting\n");
					}
					break;
					
					
			case DESTROY_AD: DestroyAD(&adPtr);break;
		}
	}
	while(select);
	DestroyAD(&adPtr);
	if(NULL != meeting)
	{
		free(meeting);
	}
}

int main()
{
	Menu();
	return 0;
}
