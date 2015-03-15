/*************************************************************************
	> File Name: RangeValue.cpp
	> Author: syzz 
	> Mail: 1181955272@qq.com 
	> Created Time: 2015年03月07日 星期六 13时44分42秒
 ************************************************************************/

#include "RangeValue.h"
using namespace std;

RangeValue::RangeValue()
{
	this->fp = NULL;
}

void
RangeValue::reset()
{
	fseek(this->fp, 0, SEEK_SET);
}

bool
RangeValue::open()
{
	if(this->fp != NULL)
		fclose(this->fp);
	if((this->fp = fopen("logs/answer.dat", "w+b")) == NULL)
		return false;
	else
		return true;
}

bool
RangeValue::write(const Bstr* _bp)
{
	if(this->fp == NULL)
		return false;
	unsigned len = _bp->getLen();
	fwrite(&len, sizeof(unsigned), 1, this->fp);
	fwrite(_bp->getStr(), sizeof(char), len, this->fp);
	return true;
}

const Bstr* 
RangeValue::read()
{
	if(this->fp == NULL)
		return NULL;
	unsigned len = 0;
	fread(&len, sizeof(unsigned), 1, this->fp);
	if(feof(this->fp))
		return NULL;		//indicate the end
	if(len > transfer.getLen())
	{
		transfer.release();
		transfer.setLen(len);
		transfer.setStr((char*)malloc(len+1));
	}
	fread(transfer.getStr(), sizeof(char), len, this->fp);
	return &transfer;
}

RangeValue::~RangeValue()
{
	if(this->fp != NULL)
		fclose(this->fp);
	//transfer wiil de deleted as Bstr
}

