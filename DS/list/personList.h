#ifndef _PERSONLIST_H_
#define _PERSONLIST_H_
#define SIZE 128	
typedef struct Person Person;
struct Person
{
	int m_id; /* Primary Key */
	char m_name[SIZE];
	int m_age;
	Person* m_next;
};

Person* ListInsertHead(Person* _head ,Person* _p);
Person* ListRemoveHead(Person* _head, Person** _item);
Person* ListInsertByKey(Person* _head, int _key, Person* _p);
Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p);
Person* ListRemoveByKey(Person* _head, int _key, Person* *_p);
Person* ListRemoveByKeyRec(Person* _head, int _key, Person**_p);
void PrintList(Person* _head);

#endif
