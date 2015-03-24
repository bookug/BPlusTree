/* Information about this file */

#ifndef _HASH_H
#define _HASH_H

#include "../util/Util.h"
#include "../node/Node.h"

class Hash
{
private:
	Node* np;
	unsigned position;
	unsigned next;
	unsigned size;
public:
	Hash();
	Hash(unsigned _size);
};

#endif
