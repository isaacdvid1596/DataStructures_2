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

	
	//auxfunctions
	void readvirtualdisk();
	void mkdiraux(int parent , char name [30]);
	
};