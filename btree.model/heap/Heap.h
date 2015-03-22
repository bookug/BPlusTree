/* Information about this file */

#ifndef _HEAP_H
#define _HEAP_H

#include "../util/Util.h"
#include "../node/Node.h"

class Node;

class Heap
{
private:
	Node** heap;			//dynamic array
	Heaplen_t len;			//valid elements num
	Heaplen_t size;			//max-size of heap
public:
	Heap();
	Heap(Heaplen_t _size);
	/* BETTER(use a function tomanage dynamic-alloc,
	 * ensuring that most of memory are used!(realloc)
	 */
	Node* getTop() const;			//return the top element
	Heaplen_t getLen() const;
	Heaplen_t getSize() const;
	bool isEmpty() const;
	bool insert(Node* _np);	//insert and adjust
	bool remove();			//remove top and adjust
	~Heap();
	void print(std::string s);			//DEBUG
};

#endif
