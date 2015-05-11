/*************************************************************************
  > File Name: produce.cpp
  > Author: syzz 
  > Mail: 1181955272@qq.com 
  > Created Time: 2015年03月12日 星期四 22时13分53秒
 ************************************************************************/

#include "util/Util.h"
using namespace std;

#define LEN 10000
#define NUM 100000

int main(int argc, char** argv)
{
	/*
	   int ret1 = Util::compare("TBJFINZABY", 10, "PVBBFMDOD", 9);
	   int ret2 = Util::compare("PVBBFMDOD", 9, "JMSKUAJWG", 9);
	   printf("%d\t%d\n", ret1, ret2);
	   printf("%d\n", sizeof(long long));
	   */
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
	return 0;
}
