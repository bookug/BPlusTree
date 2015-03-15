/*************************************************************************
	> File Name: main3.cpp
	> Author: syzz 
	> Mail: 1181955272@qq.com 
	> Created Time: 2015年03月12日 星期四 22时13分53秒
 ************************************************************************/

#include "util/Util.h"
using namespace std;

int main(int argc, char** argv)
{
	int ret1 = Util::compare("TBJFINZABY", 10, "PVBBFMDOD", 9);
	int ret2 = Util::compare("PVBBFMDOD", 9, "JMSKUAJWG", 9);
	printf("%d\t%d\n", ret1, ret2);
	printf("%d\n", sizeof(long long));
	return 0;
}
