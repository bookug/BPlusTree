/* Information about this file */

#include "util/Util.h"
#include "tree/Tree.h"
#include "test/Test.h"
using namespace std;

#define NUM 10000		//do NUM operations, not exceed data file

int
main(int argc, char* argv[])
{
	Test* test = new Test("logs/key-value.dat", 126, 2, 10);
	unsigned i = 0;
	while(i < NUM)
	{
		test->operate();
	}
	return 0;
}
