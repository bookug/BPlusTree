/*=============================================================================
# Filename: Bstr.cpp
# Author: syzz
# Mail: 1181955272@qq.com
# Last Modified: 2015-04-26 16:35
# Description: achieve functions in Bstr.h
=============================================================================*/

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
	this->str = _str;
}
/*
   Bstr::Bstr(Storage* TSM)
   {
   TSM->readBstr(this);
   }
   */
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
Bstr::operator <= (const Bstr& _bstr)
{
	int res = Util::compare(this->str, this->length, _bstr.str, _bstr.length);
	if(res <= 0)
		return true;
	else
		return false;
}

bool
Bstr::operator >= (const Bstr& _bstr)
{
	int res = Util::compare(this->str, this->length, _bstr.str, _bstr.length);
	if(res >= 0)
		return true;
	else
		return false;
}

bool
Bstr::operator != (const Bstr& _bstr)
{
	int res = Util::compare(this->str, this->length, _bstr.str, _bstr.length);
	if(res != 0)
		return true;
	else
		return false;
}

unsigned
Bstr::getLen() const
{
	return length;
}

void
Bstr::setLen(unsigned _len)
{
	this->length = _len;
}

char*
Bstr::getStr() const
{
	return str;
}

void 
Bstr::setStr(char* _str)
{
	this->str = _str;
}

void
Bstr::copy(const Bstr* _bp)
{
	this->length = _bp->getLen();
	this->str = (char*)malloc(this->length);
	memcpy(this->str, _bp->getStr(), this->length);
}

void
Bstr::clear()	
{
	this->str = NULL;
	this->length = 0;
}

void
Bstr::release()
{
	free(this->str);	//ok to be null, do nothing
	clear();
}

Bstr::~Bstr()	
{	//avoid mutiple delete
	release();
}

void
Bstr::print(string s) const
{
	Util::showtime();
	fputs("Class Bstr\n", Util::logsfp);
	fputs("Message: ", Util::logsfp);
	fputs(s.c_str(), Util::logsfp);
	fputs("\n", Util::logsfp);
	if(s == "BSTR")
	{	//total information, providing accurate debugging
		fprintf(Util::logsfp, "length: %u\t the string is:\n", this->length);
		unsigned i;
		for(i = 0; i < this->length; ++i)
			fputc(this->str[i], Util::logsfp);
		fputs("\n", Util::logsfp);
	}
	else if(s == "bstr")
	{	//only length information, needed when string is very long
		fprintf(Util::logsfp, "length: %u\n", this->length);
	}
	else;
}

