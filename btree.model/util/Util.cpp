/* Information about this file */

#include "Util.h"
using namespace std;

FILE* logsfp;            //assigned by Storage

static int
Util::compare(char* _str1, unsigned _len1, char* _str2, unsigned _len2)
{
	return 0;
}

static int
Util::string2int(string s)
{
	return atoi(s.c_str());
}

static string
Util::int2string(int n)
{
	string s;
	stringstream ss;
	ss<<n;
	ss>>s;
	return s;
}

static void
Util::showtime()
{
	time_t now;
	time(&now);
	fputs(ctime(&now), logsfp);
	fputs("\n", logsfp);
}

