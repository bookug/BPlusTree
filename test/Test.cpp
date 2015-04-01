/* Information about this file */

#include "Test.h"
using namespace std;

const char* Test::operations[Test::OPERATIONS] = { "BUILD", "OPEN", "SAVE", "SEARCH", "MODIFY", 
	"INSERT", "REMOVE", "RANGE", "GET" };

unsigned Test::count[Test::OPERATIONS] = {0};

double Test::mean[Test::OPERATIONS] = {0};

double Test::variance[Test::OPERATIONS] = {0};

Test::Test()
{
	data_fp = NULL;
	log_fp  = NULL;
	readyToOpen = false;
	neglect = false;
	t = NULL;
}

Test::Test(const char* _data, unsigned _degree, unsigned _buffer, unsigned _size)
{
	if((data_fp = fopen(_data, "rb")) == NULL)
	{
		printf("open error: data_fp\n");
		exit(1);
	}
	string timelog = "logs/degree_" + Util::int2string(_degree) + "+buffer_" + Util::int2string(_buffer)
		+ "G+size_" + Util::int2string(_size) + "G.log";
	if((log_fp = fopen(timelog.c_str(), "w+")) == NULL)
	{
		printf("open error: log_fp\n");
		exit(1);
	}
	t = NULL;
	readyToOpen = true;
	neglect = true;
	srand((unsigned)time(NULL));
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
	unsigned ccase;
	if(t != NULL)
	{
		ccase = rand() % OPERATIONS;
		if(neglect && ccase < 3)
			return;
	}
	else
		ccase = 1;	//rand() % 2;
	clock_t begin, end;
	p1 = this->read();
	p2 = this->read();
	begin = clock();
	switch(ccase)
	{
	case 0:
		t = new Tree("logs", "tree.dat", "build");
		this->readyToOpen = true;		//NOTICE: root-num is set to 0
		break;
	case 1:
		if(this->readyToOpen)
			t = new Tree("logs", "tree.dat", "open");
		break;
	case 2:
		t->save();
		this->readyToOpen = true;
		break;
	case 3:
		t->search(p1, bp);
		break;
	case 4:
		t->modify(p1, p2);
		this->readyToOpen = false;
		break;
	case 5:
		t->insert(p1, p2);
		this->readyToOpen = false;
		break;
	case 6:
		t->remove(p1);
		this->readyToOpen = false;
		break;
	case 7:
		t->range_query(p1, p2);
		break;
	case 8:
		bp = t->getRangeValue();
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
	printf("operation: %8s        time: %fs\n", operations[ccase], duration);
	fprintf(log_fp, "operation: %8s        time: %fs\n", operations[ccase], duration);
}

Test::~Test()
{
	unsigned i;
	fprintf(log_fp, "\n\n\n\noperation       count           mean                variance\n");	//set align
	for(i = 0; i < this->OPERATIONS; ++i)
	{
		if(count[i] > 0)
		{
			this->mean[i] /= this->count[i];
			this->variance[i] = (this->variance[i] / this->count[i])	//E(x^2)
				- (this->mean[i] * this->mean[i]);						//E2(x)
		}
		fprintf(log_fp, "%-8s        %-8u        %-12.8f        %-12.12f\n", 
				this->operations[i], this->count[i], this->mean[i], this->variance[i]);
	}
	fclose(data_fp);
	fclose(log_fp);
	delete t;
}

