# makefile generic tree

TARGET=genericTree_test.out
CC=gcc
CFLAGS=-ansi -g -pedantic -Wall
OBJS=genericTree_test.o bin_tree.o

run: $(TARGET)
	./$(TARGET)
	
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
genericTree.o: bin_tree.c bin_tree.h
	$(CC) $(CFLAGS) -c bin_tree.c
	
genericTree_test.o: genericTree_test.c
	$(CC) $(CFLAGS) -c genericTree_test.c
	

clean:
	rm -f $(TARGET) $(OBJS)
