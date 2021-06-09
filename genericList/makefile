# makefile List

CC= gcc
IT_TARGET= listItrTest.out
LIST_TARGET= listTest.out
FUNCS_TARGET= listFuncsTest.out
CFLAGS= -ansi -pedantic -Wall -g3 -Wconversion -c
CFLAGS+= -fPIC
CFLAGS+=-I ./listIterator
LIST_OBJS=genericList.o listTest.o
LIST_IT_OBJS=listItr.o listItrTest.o genericList.o
LIST_FUNCS_OBJS= listFuncs.o listFuncsTest.o genericList.o listItr.o



LIB_OBJS=genericList.o listItr.o listFuncs.o
LIB_DIR=../lib
LDFLAGS=-L$(LIB_DIR) -lDS
LDFLAGS+=-Wl,-rpath=$(CURDIR)/../lib/

SRCS=$(OBJS:.o=.c)

lib: $(LIB_OBJS)

$(LIST_TARGET): listTest.o
	$(CC) -o $(LIST_TARGET) listTest.o $(LDFLAGS)

$(IT_TARGET): listItrTest.o
	$(CC) -o $(IT_TARGET) listItrTest.o $(LDFLAGS)
	
$(FUNCS_TARGET): listFuncsTest.o
	$(CC) -o $(FUNCS_TARGET) listFuncsTest.o $(LDFLAGS)

listTest.o: listTest.c genericList.h
	$(CC) $(CFLAGS) -c listTest.c

genericList.o: genericList.c genericList.h listStructs.h
	$(CC) $(CFLAGS) -c genericList.c				

listItrTest.o: listIterator/listItrTest.c listIterator/list_itr.h genericList.h
	$(CC) $(CFLAGS) listIterator/listItrTest.c

listItr.o: listIterator/listItr.c listIterator/list_itr.h genericList.h listStructs.h
	$(CC) $(CFLAGS) listIterator/listItr.c
	
listFuncs.o: listFuncs.c listIterator/list_itr.h list_functions.h genericList.h
	$(CC) $(CFLAGS) listFuncs.c
	
listFuncsTest.o: listFuncsTest.c list_functions.h listIterator/list_itr.h listStructs.h
	$(CC) $(CFLAGS) listFuncsTest.c
				
list: $(LIST_TARGET)
	./$(LIST_TARGET)
	
iterator: $(IT_TARGET)
	./$(IT_TARGET)
	
funcs: $(FUNCS_TARGET)
	./$(FUNCS_TARGET)
	
valgrind: $(FUNCS_TARGET) $(IT_TARGET) $(LIST_TARGET)
	valgrind --leak-check=full ./$(FUNCS_TARGET)
	valgrind --leak-check=full ./$(IT_TARGET)
	valgrind --leak-check=full ./$(LIST_TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.o depends
	
depends: 
	$(CC) -MM -I./ $(SRCS) > depends
		
include depends
