/* Information about this file */

#ifndef _TEST_H
#define _TEST_H

#include "../util/Util.h"

//Fow now, using 126-degree and 2G-buffer
class Test
{
private:
	static const unsigned SEARCH = 0;
	static const unsigned INSERT = 1;
	static const unsigned REMOVE = 2;
	static const unsigned RANGE  = 3;
public:
	unsigned buffer;		//maybe long long, vary according to data-size
	unsigned degree;
};

#endif
