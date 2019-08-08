#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


struct Item
{
	int code;
	char fname[30];
	char lname[30];
	char city[30];
};



class FileRegister
{
public:
	void createRegister();
	void SSearch(const char *);
	int BSearch(const char *,int,int);
	 FileRegister();
	~FileRegister();
};

