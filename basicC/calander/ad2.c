#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXNUM	9
#define EXIT	0
#define ERROR_ILLIGAL_INPUT 0
#define ERROR_OVERFLOW	0
#define ERROR_UNDERFLOW	0
#define ERROR_NOT_EXIST 0
#define SUCCESS			1
#define DEFAULT_BLOCK_SIZE 3

enum options 
{CREATE_AD = 1,
CREATE_MEETING,
INSERT_MEETING,
REMOVE_MEETING,
PRINT_AD,
FIND_MEETING,
STORE_AD,
LOAD_AD,
DESTROY_AD};

typedef int ErrorCode;

typedef struct meeting
{
	float m_begin;
	float m_end;
	int m_room;
}meeting;

typedef struct AD
{
	struct meeting** m_day;
	size_t m_initSize;
	size_t m_blockSize;
	size_t m_actualSize;
	size_t m_numOfMeetings;
}AD;

/*
Description:
function receives init size and block size and creates new AD,
fills its values including a pointer to a pointers array of meetings day
*/
AD* CreateAD(size_t _initSize, size_t _blockSize)
{
	meeting** newDay = NULL;
	AD* newAD = (AD*)malloc(sizeof(AD));
	if(NULL == newAD)
	{
		return newAD;
	}
	newDay= (meeting**)malloc(sizeof(meeting*) * _initSize);
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
function frees all the meeting pointers from day that AD keeps, and frees AD
*/
void DestroyAD(AD** _ad)
{
	int i;
	if(*_ad && _ad)
	{
		if((*_ad)->m_day)
		{
			for(i=0;i<(*_ad)->m_numOfMeetings;i++)
			{
				free((*_ad)->m_day[i]);
			}
			free((*_ad)->m_day);
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
meeting* CreateMeeting(float _begin, float _end, int _room)
{
	meeting* meet = (meeting*)malloc(sizeof(meeting));
	if(meet)
	{
		meet->m_begin = _begin;
		meet->m_end = _end;
		meet->m_room = _room;
	}
	return meet;
}

void Swap(meeting** _meeting1, meeting** _meeting2) 
{ 
    meeting* temp = *_meeting1; 
    *_meeting1 = *_meeting2; 
    *_meeting2 = temp; 
}

/*
Description:
sort the meetings by begin hour using bubble sort
*/
void SortAD(AD* _ad)
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
				if(_ad->m_day[j]->m_begin > _ad->m_day[j+1]->m_begin)
				{
					Swap(&_ad->m_day[j], &_ad->m_day[j+1]); 
					swapped = 1;
				}
			}
		if (!swapped) 
		break;
		}
	} 
}

/*
Description:
function receives begin and end time for a new meeting and checks if it overlap another meeting, returns error if so
*/
ErrorCode CheckIfLegal(AD* _ad, float _begin, float _end)
{
	int i;
	float a,b;
	
	for(i=0;i<_ad->m_numOfMeetings;i++)
	{
		a = _ad->m_day[i]->m_begin;
		b = _ad->m_day[i]->m_end;
		if(!((_begin < a && _end <= a) || (_begin >= a && _end >b)))
		{
			return ERROR_ILLIGAL_INPUT;
		}
	}
	return SUCCESS;
}

/*
Description:
reallocates a new memory for meeting pointers array
*/
meeting** ResizeArray(meeting** _meetings,size_t newSize)
{
	meeting** ptrRealloc=NULL;
	ptrRealloc = (meeting**)realloc(_meetings,newSize * sizeof(meeting*));
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

/*
Description:
function receives AD and new meeting to insert.
insert if meeting is valid,
resize the meeting pointers array if necessary
and sort the array by begin hour
*/
ErrorCode InsertMeeting(AD* _ad, meeting* _newMeet)
{
	meeting** newDay = NULL;
	
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
		
		_ad->m_day[_ad->m_numOfMeetings] = _newMeet;
		_ad->m_numOfMeetings++;
		SortAD(_ad);
		return SUCCESS;
	}
	free(_newMeet);
	return ERROR_ILLIGAL_INPUT;
}

/*
Description:
free meeting memory and reorganize the meeting array by moving pointers
*/
void Remove(AD* _ad,int _i)
{
	int i;
	free(_ad->m_day[_i]);
	for(i=_i;i<_ad->m_numOfMeetings-1;i++)
	{
		_ad->m_day[i] = _ad->m_day[i+1];
	}
}

/*
Description:
removes a meeting by begin hour
and resize the meeting pointers array if necessary
*/
ErrorCode RemoveMeeting(AD* _ad,float _beginHour)
{
	int i;
	size_t newSize;
	size_t meetingsPlusBlock;
	size_t initPlusBlock;
	
	meeting** newDay = NULL;
	if(_ad != NULL && _ad->m_day != NULL)
	{
		for(i=0;i<_ad->m_numOfMeetings;i++)
		{
			if(_ad->m_day[i]->m_begin == _beginHour)
			{
				Remove(_ad,i);
				_ad->m_numOfMeetings--;
				if((_ad->m_actualSize > _ad->m_initSize) && (_ad->m_actualSize-_ad->m_numOfMeetings > _ad->m_blockSize))
				{
					meetingsPlusBlock = _ad->m_numOfMeetings+_ad->m_blockSize;
					initPlusBlock = _ad->m_initSize+_ad->m_blockSize;
					newSize = meetingsPlusBlock > initPlusBlock ? meetingsPlusBlock : initPlusBlock;
					newDay = ResizeArray(_ad->m_day,newSize);
					if(NULL == newDay)
					{
						return ERROR_OVERFLOW;
					}
					_ad->m_day = newDay;
					_ad->m_actualSize = newSize;
				}
				return SUCCESS;
				break;
			}
		}
		return ERROR_ILLIGAL_INPUT;
	}
	return ERROR_OVERFLOW;
}

/*
Description:
search a meeting by begin hour and returns its number in AD
if not exists returns error
*/
size_t FindMeeting(AD* _ad,float _begin)
{
	int i;
	if(_ad != NULL && _ad->m_day != NULL)
	{
		for(i=0;i<_ad->m_numOfMeetings;i++)
		{
			if(_ad->m_day[i]->m_begin == _begin)
			{
				return i+1;
				break;
			}
		}
		return ERROR_NOT_EXIST;
	}
	return ERROR_UNDERFLOW;
}

/*
Description:
prints all meetings
*/
void PrintAD(AD* _ad)
{
	int i;
	if(_ad != NULL && _ad->m_day != NULL)
	{
		int beginHour,beginMin,endHour,endMin;
		
		for(i=0;i<_ad->m_numOfMeetings;i++)
		{
			beginHour = (int)_ad->m_day[i]->m_begin;
			beginMin = (int)(_ad->m_day[i]->m_begin *10)%10;
			endHour = (int)_ad->m_day[i]->m_end;
			endMin = (int)(_ad->m_day[i]->m_end *10)%10;
			
			printf("(%d) %02d:%d0-%02d:%d0 in room %d\n",i+1,beginHour,beginMin,endHour,endMin,_ad->m_day[i]->m_room);
		}
	}
}

/*
Description:
saves AD to a file chosen by user
if file already exist -> overwrites
*/
ErrorCode StoreAD(AD*_ad,char* _fileName)
{
	int i;
	FILE* fp;
	
	if(NULL == _ad)
	{
		return ERROR_NOT_EXIST;
	}
	fp = fopen(_fileName,"w");
	if(fp)
	{
		for(i=0;i<_ad->m_numOfMeetings;i++)
		{
			fprintf(fp,"%f %f %d\n",_ad->m_day[i]->m_begin,_ad->m_day[i]->m_end,_ad->m_day[i]->m_room);
		}
		
		fclose(fp);
		return SUCCESS;
	}
	return ERROR_NOT_EXIST;
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
	fclose(fp);
	return count;
}

AD* LoadAD(char* _fileName)
{
	int i;
	AD* newAD = NULL;
	FILE* fp = NULL;
	int countLines = 0;
	float begin,end;
	int room;
	meeting* newMeet = NULL;
	
	countLines = CountLines(_fileName);
	
	fp = fopen(_fileName,"r");
	if(!fp)
	{
		return NULL;
	}
	newAD = CreateAD(countLines,DEFAULT_BLOCK_SIZE);
	if(newAD != NULL)
	{
		for(i=0;i<countLines;i++)
		{
			fscanf(fp,"%f %f %d",&begin,&end,&room);
			newMeet = CreateMeeting(begin,end,room);
			if(newMeet)
			{
				InsertMeeting(newAD,newMeet);
			}
		}
	}
	fclose(fp);
	return newAD;
}
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
					temp=FindMeeting(adPtr,beginHour);
					if(temp)
					{
						printf("Meeting at %02d:%d0 is meething number %lu\n",(int)adPtr->m_day[temp-1]->m_begin,(int)(adPtr->m_day[temp-1]->m_begin *10)%10,temp);
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
