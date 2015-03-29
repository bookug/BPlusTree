/* Information about this file */

#ifndef _TEST_H
#define _TEST_H

#include "../util/Util.h"
#include "../tree/Tree.h"

//Fow now, using 126-degree and 2G-buffer
class Test
{
private:	
	static const unsigned OPERATIONS = 9;	//total operations num
	static const char* operations[OPERATIONS];
	FILE* data_fp;
	FILE* log_fp;
	Tree* t;
	bool ready;				//if ready to open tree
public:
	//unsigned buffer;		//maybe long long, vary according to data-size
	//unsigned degree;
	Test();
	Test(const char* _data, unsigned _degree, unsigned _buffer, unsigned _size);
	void operate();
	Bstr* read();
};

#endif
