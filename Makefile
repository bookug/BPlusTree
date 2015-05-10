CC = g++
CFLAGS = -Wall -Werror -c -g
PROGRAMS = small-demo produce big-demo test-demo clean  
obj = Tree.o Storage.o Node.o IntlNode.o LeafNode.o TBstr.o Util.o Heap.o Hash.o RangeValue.o Test.o
all: $(PROGRAMS)
small-demo: small-demo.cpp $(obj)
	$(CC) -g small-demo.cpp $(obj) -o small-demo
produce: produce.cpp $(obj)
	$(CC) -g produce.cpp $(obj) -o produce
big-demo: big-demo.cpp $(obj)
	$(CC) -g big-demo.cpp $(obj) -o big-demo
test-demo: test-demo.cpp $(obj)
	$(CC) -g test-demo.cpp $(obj) -o test-demo
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
TBstr.o: bstr/TBstr.cpp 
	$(CC) $(CFLAGS) bstr/TBstr.cpp -o TBstr.o
Util.o: util/Util.cpp
	$(CC) $(CFLAGS) util/Util.cpp -o Util.o
Hash.o: hash/Hash.cpp
	$(CC) $(CFLAGS) hash/Hash.cpp -o Hash.o
Heap.o: heap/Heap.cpp 
	$(CC) $(CFLAGS) heap/Heap.cpp -o Heap.o
RangeValue.o: rangevalue/RangeValue.cpp
	$(CC) $(CFLAGS) rangevalue/RangeValue.cpp -o RangeValue.o
Test.o: test/Test.cpp
	$(CC) $(CFLAGS) test/Test.cpp -o Test.o
.PHONY: clean  
clean:
	rm -f $(obj)
tags:
	ctags -R
run1:
	make
	./small-demo
run2:
	make
	./produce
run3: 
	make
	./big-demo
runtest:
	make
	./test-demo
sumlines:
	find . -name "*.[ch]*" | xargs wc -l
tarball:
	tar -czvf btree.tar.gz tree storage node bstr util heap hash rangevalue test Makefile *.cpp
send:
	scp btree.tar.gz root@172.31.19.15:/media/wip/zengli/btree/

