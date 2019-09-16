#pragma once
#include <iostream>
#include <string>
#include <ctime>

struct diskdate
{
	//initialize date struct

	int d_day = -1;
	int d_month = -1;
	int d_year = -1;
};



struct metadata
{  
	char diskname[20]; //30
	unsigned int  disksize; //4
	diskdate dd; 
	unsigned int totaldentries;//4
	unsigned int bitmapsize;//4
	unsigned int directblockscount;//4;

	metadata()
	{
		strcpy_s(diskname, "root");
		disksize = 0;
		totaldentries = 0;
		bitmapsize = 0;
		directblockscount = 0;
	}

	

};

struct inodeentry
{
	char name[25];//25bytes

	diskdate id; //8bytes
	int parent; // 4
	int firstson;//4
	int rightbrother;//4
	char type; //1
	int size; //4
	bool occupied; //1
	unsigned int directblocks[12];
	unsigned int indirectblocks[3];
	
	inodeentry()
	{
		strcpy_s(name, "null");
		parent = -1;
		firstson = -1;
		rightbrother = -1;
		type = '\0';
		size = 4096;
		occupied = false;
		for (int i = 0; i < 11; i++)
		{
			directblocks[i] = 0;
		}
		for (int i = 0; i < 2; i++)
		{
			indirectblocks[i] = 0;
		}
	}
};

struct directdatablock
{
	char data[4096];
};

struct indirectdatablocklvl1
{

	//unsigned char  para hacerlo positivo 

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

struct bitmap
{
	char* bitmap;
	char* bitmaplvl1;
	char* bitmaplvl2;
	char* bitmaplvl3;
};
