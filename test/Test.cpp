/* Information about this file */

#include "Test.h"
using namespace std;

Test::Test()
{
	data_fp = NULL;
	log_fp  = NULL;
}

Test::Test(string _data, unsigned _degree, unsigned _buffer, unsigned _size)
{
	if((data_fp = fopen(_data.c_str(), "r")) == NULL)
	{
		printf("open error: data_fp\n");
		exit(1);
	}
	string timelog = "degree_" + Util::int2string(_degree) + "+buffer_" + Util::int2string(_buffer)
		+ "G+size_" + Util::int2string(_size) + "G.log";
	if((log_fp = fopen(timelog.c_str(), "w+")) == NULL)
	{
		printf("open error: log_fp\n");
		exit(1);
	}
}

const Bstr*
Test::read()
{
	return NULL;//TODO
}

void	//select a operation and print information: success? time?
Test::operate()	
{
	const Bstr* bp;
	srand((unsigned)time(NULL));
	unsigned ccase = rand() % OPERATIONS;
	clock_t begin, end;
	begin = clock();
	switch(ccase)
	{
	case 0:
		t = new Tree("logs", "tree.dat", "build");
		break;
	case 1:
		t = new Tree("logs", "tree.dat", "open");
		break;
	case 2:
		t->search(read(), bp);
		break;
	case 3:
		t->modify(read(), read());
		break;
	case 4:
		t->insert(read(), read());
		break;
	case 5:
		t->remove(read());
		break;
	case 6:
		t->range_query(read(), read());
		break;
	case 7:
		bp = t->getRangeValue();
		break;
	case 8:
		t->save();
		break;
	default:
		printf("Unknown Operation\n");
		break;
	}
	end = clock();
	double duration = (double)(end - begin) / CLOCKS_PER_SEC;	
}

