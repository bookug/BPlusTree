CC = g++
CFLAGS = -Wall -Werror -c -g
PROGRAMS = demo1 demo2 demo3 clean tags 
obj = Tree.o Storage.o Node.o IntlNode.o LeafNode.o Bstr.o Util.o Heap.o RangeValue.o
all: $(PROGRAMS)
demo1: main1.cpp $(obj)
	$(CC) -g main1.cpp $(obj) -o demo1	
demo2: main2.cpp $(obj)
	$(CC) -g main2.cpp $(obj) -o demo2
demo3: main3.cpp $(obj)
	$(CC) -g main3.cpp $(obj) -o demo3
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
Heap.o: heap/Heap.cpp 
	$(CC) $(CFLAGS) heap/Heap.cpp -o Heap.o
RangeValue.o: rangevalue/RangeValue.cpp
	$(CC) $(CFLAGS) rangevalue/RangeValue.cpp -o RangeValue.o
.PHONY: clean  
clean:
	rm -f $(obj)
tags:
	ctags -R
run1:
	make
	./demo1
run2: 
	make
	./demo2
run3:
	make
	./demo3
newlog:
	rm -f logs/default.log
sumlines:
	find . -name "*.[ch]*" | xargs wc -l
tarball:
	tar -czvf btree.tar.gz tree storage node bstr util heap rangevalue Makefile main*.cpp
send:
	scp btree.tar.gz root@59.108.48.36:/home/zengli/btree/
