/* Information about this file */

#ifndef _BSTR_H
#define _BSTR_H

#include "../util/Util.h"

class Bstr
{
private:
	char* str;		//pointers consume 8 byte in 64-bit system
	unsigned length;
public:
	Bstr();
	Bstr(char* _str, unsigned _len);
	//Bstr(Storage* TSM);
	bool operator > (const Bstr& _bstr);
	bool operator < (const Bstr& _bstr);
	bool operator == (const Bstr& _bstr);
	bool operator <= (const Bstr& _bstr);
	bool operator >= (const Bstr& _bstr);
	bool operator != (const Bstr& _bstr);
	unsigned getLen() const;
	void setLen(unsigned _len);
	char* getStr() const;
	void setStr(char* _str);		//reuse a Bstr
	void release();					//release memory
	void clear();					//set str/length to 0
	void copy(const Bstr* _bp);
	~Bstr();
	void print(std::string s) const;		//DEBUG
};

#endif
