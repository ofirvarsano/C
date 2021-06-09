#include <stdio.h>
#include <string.h>


int fact(int _n)
{
	if(_n<=1)
	{
		return 1;
	}
	return _n*fact(_n-1);
}

int power(int _n, int _k)
{
	if(_k == 0)
	{
		return 1;
	}
	return power(_n,_k-1)*_n;
}

int MaxInArray(int _arr[],int _n)
{
	int tempMax;
	if(_n == 1)
	{
		return _arr[0];
	}
	tempMax = MaxInArray(_arr,_n-1) > _arr[_n-1] ? MaxInArray(_arr,_n-1) : _arr[_n-1];
	return tempMax;
}

size_t Fib(int _n)
{
	if(_n <= 1)
	{
		return _n;
	}
	return Fib(_n-1) + Fib(_n-2);
}

size_t ItFib(int _n)
{
	int first = 0, second=1, next=0,i;

	if(_n <= 1)
	{
		return _n;
	}
	for(i=2;i<=_n;i++)
	{
		next = first + second;
		first = second;
		second = next;
	}
	return next;
}
void ReverseString(char* _word,int _start,int _end)
{
	char temp;
	if(_start >= _end)
	{
		return;
	}
	temp = _word[_start];
	_word[_start] = _word[_end];
	_word[_end] = temp;
	ReverseString(_word,_start+1,_end-1);
}

int IsPalindrome(char* _word,int _start,int _end)
{
	if(_start >= _end)
	{
		return 1;
	}
	if(_word[_start] != _word[_end])
	{
		return 0;
	}
	return IsPalindrome(_word,_start+1,_end-1);
}

void Hanoi(int _n,char _from, char _to, char _via)
{
	if(_n == 1)
	{
		printf("Move disk %d from %c to %c\n",_n,_from,_to);
		return;
	}
		Hanoi(_n-1,_from,_via,_to);
		printf("Move disk %d from %c to %c\n",_n,_from,_to);
		Hanoi(_n-1,_via,_to,_from);
}

char LastChar(char* _s)
{
	if(_s[1] == '\0')
	{
		return _s[0];
	}
	_s++;
	return LastChar(_s);
}

void MultTableY(int _x, int _y)
{
   if ( _y != 1 )
   {
      MultTableY(_x, _y-1);
   }
   printf("%d ", _x*_y);
}

void MultTable(int _x, int _y)
{
   if ( _x != 1 )
   {
      MultTable(_x-1, _y);
   }
   MultTableY(_x, _y);
   printf("\n");
}

void swap(char* x,char* y)
{
	char temp = *x;
	*x = *y;
	*y = temp;
}
void permute(char* a,int l,int r)
{
	int i;
	if(l == r)
	{
		printf("%s\n",a);
	}
	else
	{
		for(i=l;i<=r;i++)
		{
			swap((a+l),(a+i));
			permute(a,l+1,r);
			swap((a+l),(a+i));
		}
	}
}
double average(int* _arr,int _i,int _n)
{
	if(_i == _n-1)
	{
		return _arr[_i];
	}
	if(_i == 0)
	{
		return ((_arr[_i] + average(_arr,_i+1,_n))/_n);
	}
	return (_arr[_i] + average(_arr,_i+1,_n));
}

int main()
{
	char str[]="ABC";
	int size = strlen(str);
	int arr[]= {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(arr)/sizeof(arr[0]);
	char s[]="String";
	permute(str,0,size-1);
	MultTable(10,10);
	printf("%c\n",LastChar(s));
	printf("%.2f\n",average(arr,0,n));
	/*
	int n = 1;
	char pali1[]="String";
	char pali2[]="strrts";
	char pali3[]="s";
	char pali4[]="strts";
	printf("%c\n",pali1[-2]);
	printf("%s\n",s);
	ReverseString(s,0,strlen(s)-1);
	printf("%s\n",s);
	if(IsPalindrome(pali1,0,strlen(pali1)-1))
	{
		printf("%s\n",pali1);
	}
	if(IsPalindrome(pali2,0,strlen(pali2)-1))
	{
		printf("%s\n",pali2);
	}
	if(IsPalindrome(pali3,0,strlen(pali3)-1))
	{
		printf("%s\n",pali3);
	}
	if(IsPalindrome(pali4,0,strlen(pali4)-1))
	{
		printf("%s\n",pali4);
	}
	Hanoi(n,'A','B','C');
	int num;
	int arr[] = {1,8,4,0};
	num = MaxInArray(arr,4);
	printf("max %d\n",num);
	printf("itfib 10 %ld\n",ItFib(10));
	printf("itfib 30 %ld\n",ItFib(30));
	printf("itfib 5 %ld\n",ItFib(5));
	printf("itfib 50 %ld\n",ItFib(50));
	printf("fib 10 %ld\n",Fib(10));
	printf("fib 5 %ld\n",Fib(5));
	printf("power %d\n",power(3,0)); */
	return 0;
}
