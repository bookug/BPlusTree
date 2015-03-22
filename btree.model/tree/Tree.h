/* Information about this file */

#ifndef _TREE_H
#define _TREE_H

#include "../util/Util.h"
#include "../node/Node.h"
#include "../storage/Storage.h"
#include "../bstr/Bstr.h"

class Storage;
class Node;
class Bstr;

class Tree
{					//each tree is associated with a Storage instance
public:
	static const unsigned DEGREE = 100;	//degree of B+ tree
private:
	unsigned int height;		//0 indicates an empty tree
	Node* root;
	int mode;             		//BETTER(to use enum)
	//QUERY(how to extend: new or end-pointer?)
	Bstr* transfer;         	//instead of new, return value founded
	unsigned int capacity; 		//max fixed-size for transfer, but can be extended dynamicly
	Storage* TSM;           	//Tree-Storage-Manage
	std::string storepath;
	std::string filename;      	//ok for user to change
	/* some private functions */
	std::string getFilePath();	//in UNIX system
public:
	Tree();				//always need to initial transfer
	Tree(const std::string& _storepath, const std::string& _filename, int mode);
	/* TODO(some public functions) */
	const Bstr* getValueTransfer() const;
	unsigned int getHeight() const;
	Node* getRoot() const;
	//bool setRoot(const Node* _root);
	bool readRoot();		//read the tree-root to build tree
	//insert, search, remove, set
	bool search(unsigned _len, const char* _str) const;
	bool search(const Bstr* _key) const;
	bool insert(const Bstr* _key, const Bstr* _value);
	bool insert(unsigned _len1, const char* _str1, unsigned _len2, const char* _str2);
	bool modify(const Bstr* _key, const Bstr* _value);
	bool modify(unsigned _len1, const char* _str1, unsigned _len2, const char* _str2);
	Node* find(const Bstr* _key, int* store) const;
	Node* find(unsigned _len, const char* _str, int* store) const;
	bool remove(const Bstr* _key);
	bool remove(unsigned _len, const char* _str);
	//operations between tree and disk
	//bool flush(); 			//write back the dirty nodes
	bool close(); 			//save the whole tree to disk and delete
	~Tree();
	void print(std::string s);			//DEBUG(print the tree)
};

#endif
