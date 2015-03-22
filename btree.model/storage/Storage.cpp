/* Information about this file */

#include "Storage.h"
using namespace std;

/* declare variables here */
const string Storage::OpenMode[] = { "r", "rb", "r+", "r+b", "w", "wb", "w+", "w+b", "a", "ab", "a+", "a+b" }; //BETTER(macros, READ=0)
const unsigned Storage::BLOCK_SIZE = 1 << 16;
const unsigned Storage::MAX_BUFFER_SIZE = 1 << 30;
const unsigned Storage::MAX_BLOCK_NUM = 1 << 24;

Storage::Storage()
{
}

Storage::Storage(string& _filepath, string& _mode)
{
}

bool
Storage::read(Node* _np, ReadType _type)
{
	return true;
}

bool 
Storage::create(Node*& _np)
{
	return true;
}

bool
Storage::write(Node* _np)
{
	return true;
}

void* 
Storage::request(Memorybuf_t _needmem)
{
	return NULL;
}

bool
Storage::handler(Memorybuf_t _needmem)
{
	return true;
}

Node*
Storage::select()
{
	return NULL;
}

Storage::~Storage()
{
}

void
Storage::print()
{
}

