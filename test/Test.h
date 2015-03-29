/* Information about this file */

#ifndef _TEST_H
#define _TEST_H

#include "../util/Util.h"

//Fow now, using 126-degree and 2G-buffer
class Test
{
private:
	const char* operations[] = { "BUILD", "OPEN", "SEARCH", "MODIFY", "INSERT",
		"REMOVE", "RANGE", "GET", "SAVE" };
	static const unsigned OPERATIONS = 9;	//total operations num
	FILE* data_fp;
	FILE* log_fp;
public:
	//unsigned buffer;		//maybe long long, vary according to data-size
	//unsigned degree;
	Test();
	Test(unsigned degree, unsigned buffer, unsigned size);
	void operate();
	const Bstr* read();
};

#endif
