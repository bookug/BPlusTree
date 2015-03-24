/*************************************************************************
  > File Name: big-demo.cpp
  > Author: syzz 
  > Mail: 1181955272@qq.com 
  > Created Time: 2015年03月06日 星期五 19时47分27秒
 ************************************************************************/

#include "util/Util.h"
#include "tree/Tree.h"
using namespace std;

#define NUM 1000000

int main(int argc, char** argv)
{
	//Tree t("logs", "tree.dat", "build");
	Tree t("logs", "tree.dat", "open");
	Bstr bstr[2];
	const Bstr* bp;
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
	/*	 build part
		if(t.insert(&bstr[0], &bstr[1]))
			printf("Insert Success\n");
		else
			printf("Insert Fail\n");
*/
		if(t.search(&bstr[0], bp))
			printf("Search Success\n");
		else
			printf("Search Fail\n");
		/*
		if(i % 9 == 0)
		{
			if(t.remove(&bstr[0]))
				printf("Remove Success\n");
			else
				printf("Remove Fail\n");
		}
		
		t.print("TREE");
		 open part 
		if(t.remove(&bstr[0]))
			printf("Remove Success\n");
		else
			printf("Remove Fail\n");
			*/
		bstr[0].release();
		bstr[1].release();
	}
	printf("Operation Done, Now to print Tree\n");
	t.print("tree");
	printf("Tree is Printed, Now to Save\n");
	t.save();
	printf("Tree is Saved, Now to delete\n");
	
	return 0;
}
