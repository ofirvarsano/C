#include <stdio.h>
#include <stdlib.h>

struct Patient
{
	int* ID;
	float money;
};



void Swap(struct Patient* _patient1, struct Patient* _patient2) 
{ 
    struct Patient temp = *_patient1; 
    *_patient1 = *_patient2; 
    *_patient2 = temp; 
}

void SortPatients(struct Patient* _patients,size_t _size,int _flag)
{
	int i, j; 
	int swapped;
	
	if(_patients != NULL)
	{
		if(_flag == 1)
		{
			for(i = 0; i < _size; i++)
			{
				swapped = 0; 
				for (j = 0; j < _size-i-1; j++) 
				{
					if(_patients[j].money > _patients[j+1].money)
					{
						Swap(&_patients[j], &_patients[j+1]); 
						swapped = 1;
					}
				}
			if (!swapped) 
			break;
			}
		}
		else if(_flag == 0)
		for(i = 0; i < _size; i++)
		{
			swapped = 0; 
			for (j = 0; j < _size-i-1; j++) 
			{
				if(*(_patients[j].ID) > *(_patients[j+1].ID))
				{
					Swap(&_patients[j], &_patients[j+1]); 
					swapped = 1;
				}
			}
		if (!swapped) 
		break;
		}
	} 
}

void PrintP(struct Patient* _patients,size_t _size)
{
	int i;
	if(_patients)
	{
		for(i=0;i<_size;i++)
		{
			printf("%d %.2f\n",*_patients[i].ID,_patients[i].money);
		}
	}
}
int main()
{
	int x = 222;
	int y = 333;
	int z = 444;
	struct Patient* p = NULL;
	p = (struct Patient*)malloc(sizeof(struct Patient)*4);
	if(p)
	{
		p[0].ID = &z;
		p[0].money = 100;
		p[1].ID = &z;
		p[1].money = 500;
		p[2].ID = &y;
		p[2].money = 300;
		p[3].ID = &x;
		p[3].money = 100;
	}
	SortPatients(p,4,1);
	PrintP(p,4);
	return 0;
}
