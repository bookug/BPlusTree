/* Information about this file */

#ifndef _BSTR_H
#define _BSTR_H

#include "../util/Util.h"

class Bstr
{
private:
	unsigned length;
	char* str;
public:
	Bstr();
	Bstr(char* _str, unsigned _len);
	bool operator > (const Bstr& _bstr);
	bool operator < (const Bstr& _bstr);
	bool operator == (const Bstr& _bstr);
	/* TODO(more functions: release...) */
	bool setLen(unsigned _len);
	bool setStr(char* _str);		//reuse a Bstr
	bool release();
	~Bstr();
	void print(std::string s);		//DEBUG
};

#endif
