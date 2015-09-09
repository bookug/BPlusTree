/*************************************************************************
  > File Name: big-demo.cpp
  > Author: syzz 
  > Mail: 1181955272@qq.com 
  > Create Time: 2015年03月06日 星期五 19时47分27秒
 ************************************************************************/

#include "util/Util.h"
#include "tree/Tree.h"
using namespace std;

#define BUILD 1
#define NUM 100000

int main(int argc, char** argv)
{
#ifdef DEBUG
	printf("debug mode on\n");
#endif
	Tree* t;		//NOTICE:problem if using value!
	if(BUILD)
		t = new Tree("logs", "tree.dat", "build");
	else
		t = new Tree("logs", "tree.dat", "open");
	TBstr bstr[2];
	const TBstr* bp;
	char* s;
	unsigned i, j, k;
	FILE* fp = fopen("logs/key-value.dat", "rb");

	//t.print("TREE");
	for(i = 0; i < NUM; ++i)
	{
		for(k = 0; k < 2; ++k)
		{
			fread(&j, sizeof(unsigned), 1, fp);
			s = (char*)malloc(j);
			fread(s, sizeof(char), j, fp);
			bstr[k].setLen(j);
			bstr[k].setStr(s);
		}
		printf("this is the %d-th pair\n", i);
		if(BUILD)
		{
			if(t->insert(&bstr[0], &bstr[1]))
				printf("Insert Success\n");
			else
				printf("Insert Fail\n");
		}

		if(t->search(&bstr[0], bp))
		{
			printf("Search Success\n");
			if(bstr[1] == *bp)
				printf("Matched Perfectly\n");
			else
				printf("Not Matched\n");
		}
		else
			printf("Search Fail\n");
		if(!BUILD)
		{
			if(i)	//% 2 3 5 7 9 == 0
			{
				if(t->remove(&bstr[0]))
					printf("Remove Success\n");
				else
					printf("Remove Fail\n");
			}
		}
		//t->print("tree");
		bstr[0].release();
		bstr[1].release();
	}
	printf("Operation Done, Now to print Tree\n");
	t->print("tree");
	printf("Tree is Printed, Now to Save\n");
	t->save();
	printf("Tree is Saved, Now to delete\n");

	return 0;
}

