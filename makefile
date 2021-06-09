# Directories to use for the library creation:
DIRS=genericVector genericHeap genericQueue genericList hashMap executor
# Object files to use for the library creation:
LIB_OBJS=genericVector/genericVector.o genericHeap/genericHeap.o genericQueue/genericQueue.o genericList/genericList.o genericList/listItr.o genericList/listFuncs.o hashMap/hashMap.o executor/executor.o executor/my_time.o executor/task.o
# Path to the target library:
LIB_PATH=lib
LIB=$(LIB_PATH)/libDS.a
LIB2=$(LIB_PATH)/libDS.so

##########################################
.PHONY: clean dirs_make

# Create the static library as archive file:
$(LIB): dirs_make
	mkdir -p $(LIB_PATH)
	ar -rcs $(LIB) $(LIB_OBJS)
	gcc -shared -fPIC -o $(LIB2) $(LIB_OBJS)

# Make all folders by target clean:
clean:
	rm -f $(LIB) $(LIB2)
	$(shell for dir in $(DIRS); do \
		echo "make clean -C $$dir;"; \
	done)

# Make all folders by target lib:
dirs_make:
	$(shell for dir in $(DIRS); do \
		echo "make lib -C $$dir;"; \
	done)


