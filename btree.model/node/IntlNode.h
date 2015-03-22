/* Information about this file */

#ifndef _INTL_NODE_H
#define _INTL_NODE_H

#include "../util/Util.h"
#include "Node.h"

class Node;
class Storage;
class Tree;

class IntlNode: public Node
{
private:
	Node* childs[MAX_CHILD_NUM];			//NOTICE(pointer's value may change)
public:
	IntlNode();
	IntlNode(Storage* TSM);
	/* TODO(add functions) */
	Node* getChild(int _index) const;
	bool addChild(Node* _child, int _index);
	bool subChild(int _index);
	void release();				
	~IntlNode();
	void print(std::string s);				//DEBUG
};

#endif
