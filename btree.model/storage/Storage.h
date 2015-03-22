/* information about this file */
//to swap between memory and disk, achieving system-like method

#ifndef _MEM_SWAP_H
#define _MEM_SWAP_H

#include "../util/Util.h"
#include "../node/Node.h"
#include "../heap/Heap.h"
#include "file.h"

class Node;
//class IntlNode;
//class LeafNode;
class Heap;

//It controls read, write, translate, swap, and should be others' friend
//There should be two Storage instance in a tree, one for nodes and the other for values
class Storage
{                    
public:
	static const unsigned BLOCK_SIZE;	//fixed size of disk-block
	static const Memorybuf_t MAX_BUFFER_SIZE;		//max buffer size
	static const Blockaddr_t MAX_BLOCK_NUM;		//max block-num
	enum ReadType { OVER = 0, EXPAND, NORMAL };
	static const std::string OpenMode[];
private:
	std::string filepath;
	struct BlockInfo *freelist;
	FILE* treefp;				//file: tree nodes
	Heap* minheap;				//heap of Nodes's pointer, sorted in NF_RK
	Memorybuf_t freemem;  			//free memory to use, non-negative
	unsigned long long time; 		//QUERY(achieving an old-swap startegy?)
	/* TODO(some private functions) */

public:
	Storage();
	Storage(std::string& _filepath, std::string& _mode);//create a fixed-size file or open an existence
	bool read(Node* _np, ReadType _type);	//read in specific type
	bool create(Node*& _np);		//use fp to create a new node
	//NOTICE(if children and child not exist, build children's Nodes)
	bool write(Node* _np);
	/* TODO(functions to deal with the buffer(clock, height(leaf?), size, dirty, inmem, virtual)) */
	void* request(Memorybuf_t _needmem);	//deal with memory request
	bool handler(Memorybuf_t _needmem);	//swap some nodes out
	Node* select();                         //select a node to release
	//bool update();				//update InMem Node's rank, with clock
	~Storage();	
	void print(std::string s);				//DEBUG
};

#endif
