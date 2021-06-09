# makefile generic vector

TARGET= vectorTest.out
CC= gcc
CFLAGS=-ansi -pedantic -Wall -g3 -Wconversion -Werror -c
CFLAGS+= -fPIC
OBJS=$(LIB_OBJS) genericVectorTest.o

SRCS=$(OBJS:.o=.c)

LIB_OBJS=genericVector.o
LIB_DIR=../lib
LDFLAGS=-L$(LIB_DIR) -lDS
LDFLAGS+=-Wl,-rpath=$(CURDIR)/../lib/

lib:$(LIB_OBJS)

$(TARGET): genericVectorTest.o
	$(CC) -o $(TARGET) genericVectorTest.o $(LDFLAGS)
	
#genericVector.o: genericVector.c genericVector.h
#	$(CC) $(CFLAGS) -c genericVector.c
#	
#genericVectorTest.o: genericVectorTest.c
#	$(CC) $(CFLAGS) -c genericVectorTest.c
	
run: $(TARGET)
	./$(TARGET)
	
valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.o depends
	
depends: 
	$(CC) -MM -I./ $(SRCS) > depends
		
include depends
