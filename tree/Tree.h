/* Information about this file */

#ifndef _TREE_H
#define _TREE_H

#include "../util/Util.h"
#include "../node/Node.h"
#include "../node/IntlNode.h"
#include "../node/LeafNode.h"
#include "../storage/Storage.h"
#include "../rangevalue/RangeValue.h"

class Tree
{					
private:
	unsigned int height;		//0 indicates an empty tree
	Node* root;
	Node* leaves_head;			//the head of LeafNode-list
	Node* leaves_tail;			//the tail of LeafNode-list
	std::string mode;           //BETTER(to use enum)
	//QUERY(how to extend: new or end-pointer?)
	Storage* TSM;           	//Tree-Storage-Manage
	RangeValue VALUES;			//just for range query
	//always alloc one more byte than length, then user can add a '\0'
	//to get a real string, instead of new and copy
	//other operations will be harmful to search, so store value in
	//transfer temporally, while length adjusted.
	//TODO: in multi-user case, multiple-search will cause problem,
	//so lock is a must. Add lock to transfer is better than to add 
	//lock to every key/value. However, modify requires a lock for a
	//key/value, and multiple search for different keys are ok!!!
	Bstr transfer;				//to transfer value searched
	std::string storepath;
	std::string filename;      	//ok for user to change
	/* some private functions */
	std::string getFilePath();	//in UNIX system
	void CopyToTransfer(const Bstr* _bstr);
	void release(Node* _np) const;
	void prepare(Node* _np) const;
public:
	Tree();				//always need to initial transfer
	Tree(const std::string& _storepath, const std::string& _filename, const char* _mode);
	unsigned int getHeight() const;
	void setHeight(unsigned _h);
	Node* getRoot() const;
	//void setRoot(Node* _root);
	//insert, search, remove, set
	//bool search(unsigned _len1, const char* _str1, unsigned& _len2, const char*& _str2) const;
	bool search(const Bstr* _key1, const Bstr*& _value);
	bool insert(Bstr* _key, Bstr* _value);
	//bool insert(unsigned _len1, const char* _str1, unsigned _len2, const char* _str2);
	bool modify(const Bstr* _key, Bstr* _value);
	//bool modify(unsigned _len1, const char* _str1, unsigned _len2, const char* _str2);
	Node* find(const Bstr* _key, int* store, bool ifmodify) const;
	//Node* find(unsigned _len, const char* _str, int* store) const;
	bool remove(const Bstr* _key);
	//bool remove(unsigned _len, const char* _str);
	const Bstr* getRangeValue();
	bool range_query(const Bstr* _key1, const Bstr* _key2);
	bool save(); 			
	~Tree();
	void print(std::string s);			//DEBUG(print the tree)
};
//NOTICE: need to save tree manually before delete, otherwise will cause problem. 
//(problem range between two extremes: not-modified, totally-modified)
//After saved, it's ok to continue operations on tree!

#endif
