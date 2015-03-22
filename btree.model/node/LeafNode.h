/* Information about this file */

#ifndef _LEAF_NODE_H
#define _LEAF_NODE_H

#include "../util/Util.h"
#include "Node.h"
#include "../bstr/Bstr.h"

class Node;
class Bstr;
class Storage;
class Tree;

class LeafNode: public Node    
{
private:
	LeafNode* prev;
	LeafNode* next;
	Bstr values[MAX_KEY_NUM];
public:
	LeafNode();
	LeafNode(Storage* TSM);
	/* TODO(add functions) */	
	LeafNode* getPrev() const;
	LeafNode* getNext() const;
	const Bstr* getValue(int _index) const;	
	bool addValue(const Bstr* _value, int _index);
	bool subValue(int _index);
	bool setPrev(LeafNode* _prev);
	bool setNext(LeafNode* _next);
	void release();			
	~LeafNode();
	void print(std::string s);			//DEBUG
};

#endif
