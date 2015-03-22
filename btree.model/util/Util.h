/* Information about this file */

#ifndef _UTIL_H
#define _UTIL_H
/* basic macros and types are defined here, including common headers */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <string>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
//add more when needed

/* some data types WARN(maybe have to change)*/
typedef unsigned int Blockaddr_t;	
typedef unsigned int tstrlen_t;		
typedef unsigned int Memorybuf_t;	
typedef unsigned int Heaplen_t;

#define MIN(_a, _b)						\
({								\
	typeof(_a) __a = (_a);					\
	typeof(_b) __b = (_b);					\
	__a <= __b ? __a : __b;					\
})
#define MAX(_a, _b)						\
({								\
	typeof(_a) __a = (_a);					\
	typeof(_b) __b = (_b);					\
	__a >= __b ? __a : __b;					\
})

#define ROUNDDOWN(a, n)						\
({								\
	unsigned __a = (unsigned) (a);				\
	(typeof(a)) (__a - __a % (n));				\
})
#define ROUNDUP(a, n)						\
({								\
	unsigned __n = (unsigned) (n);				\
	(typeof(a)) (ROUNDDOWN((unsigned) (a) + __n - 1, __n));	\
})

// Return the offset of 'member' relative to the beginning of a struct type
#define offsetof(type, member)  ((unsigned) (&((type*)0)->member))

/******** all static&universal constants and fucntions ********/
class Util	
{
public:
	/******** this are for debugging ********/
	//to build logs-system, each class: print() in time 
	static FILE* logsfp;				//file: executing logs

public:
	static int compare(char* _str1, unsigned _len1, char* _str2, unsigned _len2); //QUERY(how to use default args)
	static int string2int(std::string s);
	static std::string int2string(int n);
	//string2str: s.c_str()
	//str2string: string(str)
	static void showtime();
};

#endif 
