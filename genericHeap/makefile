# makefile generic heap

TARGET= heapTest.out
CC= gcc
CFLAGS= -ansi -g -pedantic -Wall -c
CFLAGS+= -fPIC
CFLAGS+=-I../genericVector
OBJS=test_heap.o genericHeap.o
LIB_OBJS=genericHeap.o
LIB_DIR=../lib
LDFLAGS=-L$(LIB_DIR) -lDS
LDFLAGS+=-Wl,-rpath=$(CURDIR)/../lib/

SRCS=$(OBJS:.o=.c)

lib: $(LIB_OBJS)

$(TARGET): test_heap.o
	$(CC) -o $(TARGET) test_heap.o $(LDFLAGS)

#genericHeap.o: genericHeap.c genericHeap.h ../genericVector/genericVector.h
#	$(CC) $(CFLAGS) genericHeap.c
#	
#test_heap.o: test_heap.c genericHeap.h ../genericVector/genericVector.h
#	$(CC) $(CFLAGS) test_heap.c
	
run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.o depends
	
depends: 
	$(CC) -MM -I./ $(SRCS) > depends
		
include depends
