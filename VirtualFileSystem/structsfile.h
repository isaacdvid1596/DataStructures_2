#pragma once


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
	int parent;
	int firstson;
	int rightbrother;
	char type;
	int size;
	bool occupied;

};