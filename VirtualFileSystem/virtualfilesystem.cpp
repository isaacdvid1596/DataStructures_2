#pragma once

#include "structsfile.h"
#include "virtualfilesystem.h"

void virtualfilesystem::createVirtualDisk(char name[20])
{
	fstream file("virtualdisk.bin", ios::out | ios::app | ios::binary);

	if (!file)
	{
		cout << "cannot open file" << endl;
	}
	else
	{

	}

}