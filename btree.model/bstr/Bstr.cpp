/* Information about this file */

#include "Bstr.h"
using namespace std;

Bstr::Bstr()
{
	this->length = 0;
	this->str = NULL;
}

Bstr::Bstr(char* _str, unsigned _len)
{
	this->length = _len;
	thsi->str = _str;
}

bool 
Bstr::operator > (const Bstr& _bstr)
{
	int res = Util::compare(this->str, this->length, _bstr.str, _bstr.length);
	if(res == 1)
		return true;
	else
		return false;
}

bool 
Bstr::operator < (const Bstr& _bstr)
{
	int res = Util::compare(this->str, this->length, _bstr.str, _bstr.length);
	if(res == -1)
		return true;
	else
		return false;
}

bool
Bstr::operator == (const Bstr& _bstr)
{
	int res = Util::compare(this->str, this->length, _bstr.str, _bstr.length);
	if(res == 0)
		return true;
	else
		return false;
}

bool
setlen(unsigned _len)
{
	this->length = _len;
	return true;
}

bool 
setStr(char* _str)
{
	this->str = _str;
	return true;
}

bool
Bstr::release()
{
	free(this->str);
	this->str = NULL;
	thsi->length = 0;
	return true;
}

Bstr::~Bstr()
{
	release();
}

void
Bstr::print(string s)
{
}

