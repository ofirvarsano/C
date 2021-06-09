# makefile generic queue

TARGET= qtest.out
CC= gcc
CFLAGS= -ansi -pedantic -Wall -g3 -Wconversion -Werror -c
CFLAGS+= -shared -fPIC
OBJS=$(LIB_OBJS) genericQueueTest.o
LIB_OBJS=genericQueue.o
LDFLAGS=-L$(LIB_DIR) -lDS
LDFLAGS+=-Wl,-rpath=$(CURDIR)/../lib/

SRCS=$(OBJS:.o=.c)

lib: $(LIB_OBJS)

$(TARGET): genericQueueTest.o
	$(CC) -o $(TARGET) genericQueueTest.o $(LDFLAGS)

#genericQueueTest.o: genericQueueTest.c
#	$(CC) $(CFLAGS) genericQueueTest.c
#	
#genericQueue.o: genericQueue.c genericQueue.h
#	$(CC) $(CFLAGS) genericQueue.c
	
run: $(TARGET)
	./$(TARGET)
	
valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.o depends
	
depends: 
	$(CC) -MM -I./ $(SRCS) > depends
		
include depends
