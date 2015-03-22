/* Information about this file */

#ifndef _NODE_H
#define _NODE_H

#include "../util/Util.h"
#include "../bstr/Bstr.h"
#include "../storage/Storage.h"
#include "../tree/Tree.h"

class Bstr;
class Storage;
class Tree;

class Node       				//abstract basic class 
{
public:
	static const unsigned MAX_KEY_NUM = 2 * 100 - 1;	//max key-num
	static const unsigned MAX_CHILD_NUM = MAX_KEY_NUM + 1;	//max child-num
	/* diffrent flags for tree-nodes, 32-bit */
	static const unsigned NF_IL = 0x00000001;	//is leaf
	static const unsigned NF_ID = 0x00000002;	//is dirty
	static const unsigned NF_IM = 0x00000004;	//in memory
	static const unsigned NF_IV = 0x00000008;	//is virtual
	static const unsigned NF_RK = 0xffffff00;	//select-rank, in Storage
private:
	unsigned store;			//store address, the BLock index
	unsigned flag;			//NF_RK, NF_IL,NF_ID, NF_IV, propety
	unsigned num; 			//totle keys num
	Bstr keys[MAX_KEY_NUM]; //DEBUG(compile error!!!)
public:
	Node();				
	Node(Storage* TSM);			//create(this) in Storage
	/* TODO(add functions) */
	bool isLeaf();
	bool isDirty();
	bool InMem();
	unsigned getNum() const;
	unsigned getStore() const;
	bool setStore(unsigned _store);
	bool setFlag(unsigned _flag);
	const Bstr* getKey(int _index) const;	//need to check the index
	bool addKey(const Bstr* _bstr, int _index);
	bool subKey(int _index);
	//TODO(split and collapse, the abandoned node when collapsing must be written back at once!)
	virtual void release() = 0;		//release the node, only remain necessary information
	~Node();
	virtual void print(std::string s) = 0;		//DEBUG(print the Node)
};

/*NOTICE(operations in release()) 
 *To save memory, we can only remain store and flag(childs added for Leaf).
 *However, in this way childs'pointers is ok to change, use Node** or Node*& is also nonsense
 *because the pointer variable may die. 
 *Another way is only to release dynamic memory, and store thw whole, read the Bstr only to 
 *build. In this way nodes'pointer doesn't change, and operation is simplified, while memory
 *is consumed a bit more. Because Bstrs consume the most memory, and memory-disk swapping is
 *the most time-consuming thing, it seems to be a better way.
 *WARN:when a node is in memory and not deleted, its basic content is always being! If nodes are 
 *really too many, this will cause disaster because we can't swap them out until tree is closed!
 *To solve this problem, there should be two types of release-function: one to release Bstr, one 
 *to release the whole(pointer is invalid and rebuild problem)
 */

#endif
