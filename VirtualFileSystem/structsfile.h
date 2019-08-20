#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct metadata
{
	char filename[30]; 
	unsigned int  filesize; 
	char filecreationdate[8];
	char filecreator[30];
	unsigned int filenumberentries;
	unsigned int bitmapsize;
	unsigned int directblockscount;
};

struct inodeentry
{
	char name[25];
	char creationdate[8];
	int parent=-1;
	int firstson=-1;
	int rightbrother=-1;
	char type;
	int size;
	bool occupied = false;
	
};

struct directdatablock
{
	char data[4096]; 
};

struct indirectdatablocklvl1
{
	int pointers[16];
};

struct indirectdatablocklvl2
{
	int pointers[32];
};

struct indirectdatablocklvl3
{
	int pointers[64];
};

