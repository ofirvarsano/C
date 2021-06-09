#include <stdio.h>
#include <stdlib.h>
#include <string.h>


size_t StrlenItr(const char* _s)
{
	size_t count = 0;
	
	while (*_s++)
	{
		++count;
	}
	return count;
}

size_t StrlenRec(const char* _str)
{
	if (!*_str)
	{
		return 0;
	}
	return 1 + StrlenRec(_str + 1);
}

size_t Strlen2(const char* const _str)
{
	/* for complexity reasons strlen does not check input for NULL */
	const char* iterator = _str;
	
	while (*iterator)
	{
		++iterator;
	}
	return (size_t)(iterator - _str);
}

char* Strcpy(char* _dest, const char* const _str)
{
	char* s = _dest;
	const char* s2 = _str;
	while((*s++ = *s2++))
	{
	}
	return _dest;
}

char* Strcpy2(char* _dest, const char* const _str)
{
	int i = 0;
	while(_str[i] != '\0')
	{
		_dest[i] = _str[i];
		++i;
	}
	_dest[i] = '\0';
	return _dest;
}

char* StrcpyRec(char* _destination, const char* _source)
{
	*_destination = *_source;
	
	if(!*_source)
	{
		StrcpyRec(_destination + 1, _source + 1);
	}
	return _destination;
}

char* StrncpyItr(char* _destination, const char* _source, size_t _num)
{
	char* original = _destination;
	while(_num-- && (*(_destination++) = (*_source++)))
	{
	}
	return original;
}

char* StrncpyRec(char* _destination, const char* _source, size_t _num)
{
	if(_num == 0)
	{
		return _destination;
	}
	*_destination = *_source;
	if(!*_source)
	{
		StrncpyRec(_destination + 1, _source + 1, _num - 1);
	}
	return _destination;
}

int StrcmpItr(const char* _str1, const char* _str2)
{
	while(*_str2 && (*_str1 == *_str2))
	{
		++_str1;
		++_str2;
	}
	return *_str1 - *_str2;
}

int StrcmpRec(const char* _str1, const char* _str2)
{ 
	return (!*_str1 || *_str2 != *_str1) ? *_str1 - *_str2 : StrcmpRec(_str1 + 1, _str2 + 1);
}

int compare(const char* s1,const char* s2)
{
	while(*s1 && *s2)
	{
		if(*s1 != *s2)
		{
			return 0;
		}
		s1++;
		s2++;
	}
	return (*s2 == '\0');
}

char* MyStrstr(const char* _str, const char* _substr)
{
	while(*_str != '\0')
	{
		if((*_str == *_substr) && compare(_str,_substr))
		{
			return (char*)_str;
		}
		++_str;
	}
	return NULL;
}

char* MyStrcat(char* _destination, const char* _source)
{
	char* original = _destination;
	while(*_destination)
	{
		++_destination;
	}
	while(*_source)
	{
		*_destination = *_source;
		++_destination;
		++_source;
	}
	*_destination = '\0';
	return original;
}

int main()
{
	char str[50] = "adef";
	char str2[50] = "abcdefg";
	char str3[50] = "abcdefg";
	char str4[40];
	char* result;
	/*StrcpyRec(str2,str);
	printf("%s\n", str2);*/
	result = StrncpyItr(str3,str,2);
	printf("%s\n", result);
	printf("%s\n", str3);
	printf("cmp: %d\n", StrcmpRec(str2,str2));
	printf("cmp: %d\n", StrcmpRec(str,str2));
	printf("cmp rec: %d\n", StrcmpRec(str2,str2));
	result = MyStrcat(str,str2);
	printf("%s\n", result);
	
	result = MyStrstr(str,str2);
	printf("%s\n", result);
	printf("%ld\n",StrlenRec(str2));
	/*
	printf("%ld\n",Strlen2(str));
	printf("%ld\n",Strlen2(str2));
	printf("%ld\n",Strlen2(str3));
	
	printf("%s\n", str3);
	Strcpy2(str2,str3);
	printf("%s\n", str2);
	printf("%s\n", str3); */
	StrncpyRec(str3,str2,3);
	/*StrNcpyItr(str3,str2,3);*/
	printf("%s\n", str3);
	
	
	return 0;
}






