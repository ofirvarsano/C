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

AD* CreateAD(size_t, size_t);
void DestroyAD(AD**);
meeting* CreateMeeting(float, float, int);
void SortAD(AD* _ad);
ErrorCode InsertMeeting(AD*, meeting*);
ErrorCode RemoveMeeting(AD*,float);
size_t FindMeeting(AD*,float);
void PrintAD(AD*);
ErrorCode StoreAD(AD*,char*);
AD* LoadAD(char*);
void PrintOptions();
