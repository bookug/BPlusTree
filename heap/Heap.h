/* Information about this file */

#ifndef _HEAP_H
#define _HEAP_H

#include "../util/Util.h"
#include "../node/Node.h"

/* add, sub, modify: all can be done within O(logn) using adjust-function */
//QUERY: when modified, finding right position consumes O(n). How about keeping smallest?
//(add O(1), sub O(2n), modify O(n)

class Heap
{
private:
	Node** heap;			//dynamic array
	unsigned length;			//valid elements num
	unsigned size;			//max-size of heap
public:
	Heap();
	Heap(unsigned _size);
	Node* getTop() const;			//return the top element
	unsigned getLen() const;
	unsigned getSize() const;
	bool isEmpty() const;
	bool insert(Node* _np);	//insert and adjust
	bool remove();			//remove top and adjust
	bool modify(Node* _np, bool _flag);			//searech modified element and adjust
	~Heap();
	void print(std::string s);			//DEBUG
};

#endif
