/*************************************************************************
	> File Name: RangeValue.h
	> Author: syzz 
	> Mail: 1181955272@qq.com 
	> Created Time: 2015年03月07日 星期六 13时43分10秒
 ************************************************************************/

#ifndef _RANGE_VALUE_H
#define _RANGE_VALUE_H
#endif

#include "../util/Util.h"
#include "../bstr/Bstr.h"

class RangeValue
{
private:
	FILE* fp;
	Bstr transfer;
public:
	RangeValue();
	void reset();
	bool open();
	bool write(const Bstr* _bp);
	const Bstr* read();
	~RangeValue();
};

