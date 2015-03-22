/* Information about this file */

#include "Tree.h"
using namespace std;

Tree::Tree()
{
}

Tree::Tree(const string& _storepath, const string& _filename, int mode)
{
}

string
Tree::getFilePath()
{
	return storepath+"/"+filename;
}

const Bstr*
Tree::getValueTransfer() const
{
	return NULL;
}

unsigned 
Tree::getHeight() const
{
	return 0;
}

Node*
Tree::getRoot() const
{
	return NULL;
}

bool
Tree::readRoot()
{
	return true;
}

bool
Tree::search(unsigned _len, const char* _str) const
{
	return true;
}

bool
Tree::search(const Bstr* _key) const
{
	return true;
}

bool
Tree::insert(const Bstr* _key, const Bstr* _value)
{
	return true;
}

bool
Tree::insert(unsigned _len1, const char* _str1, unsigned _len2, const char* _str2)
{
	return true;
}

bool
Tree::modify(const Bstr* _key, const Bstr* _value)
{
	return true;
}

bool
Tree::modify(unsigned _len1, const char* _str1, unsigned _len2, const char* _str2)
{
	return true;
}

Node*
Tree::find(const Bstr* _key, int* store) const
{
	return NULL;
}

Node*
Tree::find(unsigned _len, const char* _str, int* store) const
{
	return NULL;
}

bool
Tree::remove(const Bstr* _key)
{
	return true;
}

bool
Tree::remove(unsigned _len, const char* _str)
{
	return true;
}

bool 
Tree::close()
{
	return true;
}

Tree::~Tree()
{
}

void
Tree::print()
{
}

