/* Information about this file */

#include "LeafNode.h"
using namespace std;

LeafNode::LeafNode()
{
}

LeafNode::LeafNode(Storage* TSM)
{
}


LeafNode*
getPrev() const
{
	return NULL; //TODO
}

LeafNode*
getNext() const
{
	return NULL; //TODO
}

const Bstr* 
getValue(int _index) const
{
	return NULL; //TODO
}

bool 
addValue(const Bstr* _value, int _index)
{
	return true; //TODO
}

bool
subValue(int _index)
{
	return true; //TODO
}

bool 
setPrev(LeafNode* _prev)
{
	return true; //TODO
}

bool
setNext(LeafNode* _next)
{
	return true; //TODO
}

void
LeafNode::release()
{
}

void
LeafNode::print()
{
}

LeafNode::~LeafNode()
{
}
