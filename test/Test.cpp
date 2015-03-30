/* Information about this file */

#include "Test.h"
using namespace std;

const char* Test::operations[Test::OPERATIONS] = { "BUILD", "OPEN", "SEARCH", "MODIFY", 
	"INSERT", "REMOVE", "RANGE", "GET", "SAVE" };

unsigned Test::count[Test::OPERATIONS] = {0};

double Test::mean[Test::OPERATIONS] = {0};

double Test::variance[Test::OPERATIONS] = {0};

Test::Test()
{
	data_fp = NULL;
	log_fp  = NULL;
	ready = false;
}

Test::Test(const char* _data, unsigned _degree, unsigned _buffer, unsigned _size)
{
	if((data_fp = fopen(_data, "rb")) == NULL)
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
	ready = true;
}

Bstr*
Test::read()
{
	unsigned len;
	fread(&len, sizeof(unsigned), 1, data_fp);
	char* s = (char*)malloc(len);
	fread(s, sizeof(char), len, data_fp);
	return new Bstr(s, len);
}

void	//select a operation and print information: success? time?
Test::operate()	
{
	const Bstr *bp;
	Bstr *p1, *p2;
	srand((unsigned)time(NULL));
	unsigned ccase = rand() % OPERATIONS;
	clock_t begin, end;
	p1 = this->read();
	p2 = this->read();
	begin = clock();
	switch(ccase)
	{
	case 0:
		t = new Tree("logs", "tree.dat", "build");
		this->ready = false;
		break;
	case 1:
		if(this->ready)
			t = new Tree("logs", "tree.dat", "open");
		break;
	case 2:
		t->search(p1, bp);
		break;
	case 3:
		t->modify(p1, p2);
		this->ready = false;
		break;
	case 4:
		t->insert(p1, p2);
		this->ready = false;
		break;
	case 5:
		t->remove(p1);
		this->ready = false;
		break;
	case 6:
		t->range_query(p1, p2);
		break;
	case 7:
		bp = t->getRangeValue();
		break;
	case 8:
		t->save();
		this->ready = true;
		break;
	default:
		printf("Unknown Operation\n");
		break;
	}
	end = clock();
	this->count[ccase]++;				//compute the specific operation num
	p1->release();
	p2->release();
	double duration = (double)(end - begin) / CLOCKS_PER_SEC;	
	this->mean[ccase] += duration;		//compute the total time first
	this->variance[ccase] += (duration * duration);	//compute sum of x^2 first
	fprintf(log_fp, "operation: %s\ttime: %fs\n", operations[ccase], duration);
}

Test::~Test()
{
	unsigned i;
	for(i = 0; i < this->OPERATIONS; ++i)
	{
		this->mean[i] /= this->count[i];
		this->variance[i] = (this->variance[i] / this->count[i])	//E(x^2)
			- (this->mean[i] * this->mean[i]);						//E2(x)
	}
}

