/* Information about this file */

#include "Node.h"
using namespace std;

Node::Node()
{
	store = flag = num = 0;
	memset(keys, sizeof(Bstr) * MAX_KEY_NUM, 0);
}

Node::Node(Storage* TSM)
{
	TSM->read(this, OVER);	
}

bool
Node::isLeaf()
{
	return this->flag & NF_IL;
}

bool
Node::isDirty()
{
	return this->flag & NF_ID;
}

bool 
Node::InMem()
{
	return this->flag & NF_IM;
}

unsigned 
Node::getNum() const
{
	return this->num;
}

unsigned
Node::getStore() const
{
	return this->store;
}

bool
Node::setStore(unsigned _store)
{
	this->store = _store;
	return true;
}

bool
Node::setFlag(unsigned _flag)
{
	this->flag = _flag;
	return true;
}

const Bstr* 
Node::getKey(int _index) const
{
	if(_index < 0 || _index >= num)
	{
		print(string("Invalid index: ") + Util::int2string(_index));    
		return NULL;
	}
	else
		return this->keys + _index;
}

bool
Node::addKey(const Bstr* _bstr, int _index)
{
	if(_index < 0 || _index > this->num)
	{
		print(string("Invalid index: ") + Util::int2string(_index));
		return false;
	}
	int i;
	for(i = this->num - 1; i >= _index; --i)
		keys[i+1] = keys[i];
	keys[_index] = *_bstr;
	return true;
}

bool
Node::subKey(int _index)
{
	if(_index < 0 || _index >= this->num)	
	{
		print(string("Invalid index: ") + Util::int2string(_index));
		return false;
	}
	int i;
	for(i = _index + 1; i < this->num; ++i)
		keys[i] = keys[i+1];
	return true;
}

Node::~Node()
{

}

