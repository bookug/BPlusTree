# BPlusTree
use B+tree to deal with key-value operation
This is a simple model for Btree, just to get used to it.
Later, new algorithm and swap strategy can perform here firstly, 
for a test before applying to labatory's project!

Some SELF-MACROs are used in notes: TODO, WARN, DEBUG, 
BETTER, QUERY, NOTICE

each directory with a makefile, all contributed to one

files in logs/ are helpful when debugging, so we should always print information
to them. What's more, consider if necessary to include logs/ in users' side???

# BETTER

1. the Bstr can represent any elements, but you are advised to choose your own type. For example, if your key is just an int type, then using Bstr is wasteful.

2. you had better adjust the parameters according to the real case, for example, the block settings in storage/Storage.h
