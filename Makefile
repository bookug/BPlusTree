CC = g++
CFLAGS = -Wall -Werror -c -g
PROGRAMS = small-demo produce big-demo clean  
obj = Tree.o Storage.o Node.o IntlNode.o LeafNode.o Bstr.o Util.o Heap.o RangeValue.o
all: $(PROGRAMS)
small-demo: small-demo.cpp $(obj)
	$(CC) -g small-demo.cpp $(obj) -o small-demo
big-demo: big-demo.cpp $(obj)
	$(CC) -g big-demo.cpp $(obj) -o big-demo
produce: produce.cpp $(obj)
	$(CC) -g produce.cpp $(obj) -o produce
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
	./small-demo
run3: 
	make
	./big-demo
run2:
	make
	./produce
sumlines:
	find . -name "*.[ch]*" | xargs wc -l
tarball:
	tar -czvf btree.tar.gz tree storage node bstr util heap rangevalue Makefile main*.cpp
send:
	scp btree.tar.gz root@59.108.48.36:/home/zengli/btree/
