/* this program is used for test! */
//we can do lots of tests with debug-system

#include "tree/Tree.h"
#include "storage/Storage.h"
#include "util/Util.h"
#include "node/IntlNode.h"
#include "node/LeafNode.h"
using namespace std;

#define BUILD 0

int 
main(int argc, char** argv)
{
	//freopen("logs/default.log", "a", stdout);
	//print basic information of tree
	printf("This is a B+ tree!\n");
	printf("size of TBstr: %lu\n", sizeof(TBstr));	
	printf("size of Node: %lu\n", sizeof(Node));
	printf("size of IntlNode: %lu\n", sizeof(IntlNode));
	printf("size of LeafNode: %lu\n", sizeof(LeafNode));
	printf("size of Tree: %lu\n", sizeof(Tree));
	printf("size of Heap: %lu\n", sizeof(Heap));
	printf("size of Storage: %lu\n", sizeof(Storage));
	printf("DEGREE: %d\n", Node::DEGREE);		
	printf("HEAPSIZE: %d\n", Storage::HEAP_SIZE);

	Tree* t;
	if(BUILD)
		t = new Tree("logs", "tree.dat", "build");
	else
		t = new Tree("logs", "tree.dat", "open");

	TBstr* bp1 = new TBstr(NULL, 0);
	TBstr* bp2 = new TBstr(NULL, 0);
	int i;
	char* s;
	const TBstr* bp3;
	if(BUILD)
	{
		for(i = 0; i < 10; ++i)
		{
			bp1->setLen(1);
			bp2->setLen(1);
			s = new char[1];
			s[0] = 'A' + i;
			bp1->setStr(s);
			s = new char[1];
			s[0] = 'a' + i;
			bp2->setStr(s);
			printf("this is the %dth loop\n", i);
			if(BUILD)
				t->insert(bp1, bp2);
			//printf("the height is %d\n", t.getHeight());
			bp1->release();
			bp2->release();
		}	

		for(i = 0; i < 7; ++i)
		{
			bp1->setLen(1);
			s = new char[1];
			s[0] = 'A' + i;
			bp1->setStr(s);
			if(t->search(bp1, bp3))
				bp3->print("bstr");
			bp2->setLen(1);
			s = new char[1];
			s[0] = 'b' + i;
			bp2->setStr(s);
			if(!t->modify(bp1, bp2))
				printf("error in modify!\n");
			else 
				printf("modify successfully!\n");
			bp3->print("BSTR");		//can reserve after modify
			bp1->release();
			bp2->release();
		}
	}
	else
	{
		printf("tree is in open mode\n");
		bp1->setLen(1);
		bp2->setLen(1);
		s = new char[1];
		s[0] = 'B';
		bp1->setStr(s);
		s = new char[1];
		s[0] = 'G';
		bp2->setStr(s);
		t->range_query(bp1, bp2);
		while((bp3=t->getRangeValue()) != NULL)
		{
			bp3->print("BSTR");
		}
		bp1->release();
		bp2->release();

		for(i = 0; i < 7; ++i)
		{
			bp1->setLen(1);
			s = new char[1];
			s[0] = 'A' + i;
			bp1->setStr(s);
			t->remove(bp1);
			bp1->release();
		}
	}
	t->print("TREE");//NOTICE: read when needed, not sum memory 
	t->save();	

	return 0;
}
