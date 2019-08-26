#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


struct metadata //virtualdisk metadata
{
	char filename[30]; 
	unsigned int  filesize;
	char filecreator[30];
	unsigned int filenumberentries;
	unsigned int bitmapsize;
	unsigned int directblockscount;
};

struct inodeentry 
{
	char name[25];
	char creationdate[10];
	int parent=-1;
	int firstson=-1;
	int rightbrother=-1;
	char type;
	unsigned int size;
	bool occupied = false;
	unsigned int directdatablocks[12];
	unsigned int indirectdatablocks[3];  //15 blocks inode
};

struct directdatablock
{
	char data[4096]; 
};

struct indirectdatablocklvl1
{
	unsigned int pointers[16];
};

struct indirectdatablocklvl2
{
	unsigned int pointers[32];
};

struct indirectdatablocklvl3
{
	unsigned int pointers[64];
};

