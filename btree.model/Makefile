CC = g++
CFLAGS = -Wall -Werror -c -g
PROGRAMS = main clean
obj = Tree.o Storage.o Node.o IntlNode.o LeafNode.o Bstr.o Util.o Heap.o
all: $(PROGRAMS)
main: driver.o $(obj)
	$(CC) driver.o $(obj) -o main
driver.o: driver.cpp tree/Tree.h storage/Storage.h util/Util.h
	$(CC) $(CFLAGS) driver.cpp -o driver.o
Tree.o: tree/Tree.cpp 
	$(CC) $(CFLAGS) tree/Tree.cpp -o Tree.o
Storage.o: storage/Storage.cpp
	$(CC) $(CFLAGS) storage/Storage.cpp -o Storage.o
Node.o: node/Node.cpp 
	$(CC) $(CFLAGS) node/Node.cpp -o Node.o
IntlNode.o: node/IntlNode.cpp 
	$(CC) $(CFLAGS) node/IntlNode.cpp -o IntlNode.o
LeafNode.o: node/LeafNode.cpp 
	$(CC) $(CFLAGS) node/LeafNode.cpp -o LeafNode.o
Bstr.o: bstr/Bstr.cpp 
	$(CC) $(CFLAGS) bstr/Bstr.cpp -o Bstr.o
Util.o: util/Util.cpp
	$(CC) $(CFLAGS) util/Util.cpp -o Util.o
Heap.o: heap/Heap.cpp node/Node.h
	$(CC) $(CFLAGS) heap/Heap.cpp -o Heap.o
.PHONY: clean
clean:
	rm -f driver.o $(obj)
