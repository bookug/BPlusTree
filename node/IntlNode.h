/* Information about this file */

#ifndef _INTL_NODE_H
#define _INTL_NODE_H

#include "../util/Util.h"
#include "Node.h"

#define INTL_SIZE	sizeof(Bstr)*Node::MAX_KEY_NUM

class IntlNode: public Node
{
private:
	Node* childs[MAX_CHILD_NUM+1];	//BETTER: here waste 8-bytes to avoid bugs!
public:
	IntlNode();
	IntlNode(bool isVirtual);
	//IntlNode(Storage* TSM);
	void Virtual();
	void Normal();
	Node* getChild(int _index) const;
	bool setChild(Node* _child, int _index);
	bool addChild(Node* _child, int _index);
	bool subChild(int _index);
	unsigned getSize() const;
	Node* split(Node* _father, int _index);
	Node* coalesce(Node* _father, int _index);
	void release();				
	~IntlNode();
	void print(std::string s);				//DEBUG
	/*non-sense functions: polymorphic
	Node* getPrev() const;
	Node* getNext() const;
	const Bstr* getValue(int _index) const;
	bool setValue(const Bstr* _value, int _index);
	bool addValue(const Bstr* _value, int _index);
	bool subValue(int _index);
	void setPrev(Node* _prev);
	void setNext(Node* _next);
	*/
};

#endif
