#pragma once
#include "structsfile.h"
#include <fstream>
#include <iostream>

using namespace std;

class virtualfilesystem
{

private:

public:
	//filesystem functions
	void virtualDiskSim(char name[20], int dentries);
	void mkdir(int,int, bool,char name[25]);
	int cd(char name[25],int parent);
	int cdback(int);
	void ls(int parent);
	void rm(int pos);
	//void import();
	//void export();
	
	//auxfunctions
	void readvirtualdisk();
	void mkdiraux(int parent , char name [30]);
	bool isfile(int parent);
	//void rmaux(int pos);

	char* initializebitmap(int n);
	void printbitmap(char* bitmap, int ndblocks);
	char* bitmapon(char* bitmap, int ndblocks);
	char* bitmapoff(char* bitmap, int ndblocks);
	
};