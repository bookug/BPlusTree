/*************************************************************************
  > File Name: main2.cpp
  > Author: syzz 
  > Mail: 1181955272@qq.com 
  > Created Time: 2015年03月06日 星期五 19时47分27秒
 ************************************************************************/

#include "util/Util.h"
#include "tree/Tree.h"
using namespace std;

#define LEN 10000
#define NUM 1000000

int main(int argc, char** argv)
{
	/* produce big set: key-value */
	/*
	   FILE* fp = fopen("logs/key-value.dat", "w+");
	   srand((unsigned)time(NULL));
	   unsigned cnt = 0, i = 0, j = 0, k = 0;
	   char c;
	   for(cnt = 0; cnt < NUM; ++cnt)
	   {
	   for(k = 0; k < 2; ++k)		//key and value
	   {
	   j = rand()%LEN + 1;		//the string length
	   fwrite(&j, sizeof(unsigned), 1, fp);
	   for(i = 0; i < j; ++i)
	   {
	   if(k == 0)
	   c = rand()%26 + 'A';
	   else
	   c = rand()%26 + 'a';
	   fputc(c, fp);	//the character: 0~255
	   }
	   }
	   }
	   */
	Tree t("logs", "tree.dat", "build");
	Bstr bstr[2];
	const Bstr* bp;
	char* s;
	unsigned i, j, k;
	FILE* fp = fopen("logs/key-value.dat", "rb");
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
		if(t.insert(&bstr[0], &bstr[1]))
			printf("Insert Success\n");
		else
			printf("Insert Fail\n");

		if(t.search(&bstr[0], bp))
			printf("Search Success\n");
		if(i % 9 == 0)
		{
			if(t.remove(&bstr[0]))
				printf("Remove Success\n");
			else
				printf("Remove Fail\n");
		}
		//t.print("TREE");

	}
	bstr[0].clear();
	bstr[1].clear();
	printf("Operation Done, Now to print Tree\n");
	t.print("TREE");
	printf("Tree is Printed, Now to Save\n");
	t.save();
	printf("Tree is Saved, Now to delete\n");
	return 0;
}
