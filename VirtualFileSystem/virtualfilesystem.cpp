#pragma once

#include "structsfile.h"
#include "virtualfilesystem.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>
#pragma warning(disable:4996)

using namespace std;

string return_current_time_and_date() //function to return  current date and time
{
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
	return ss.str();
}



void virtualfilesystem::createVirtualDisk(char fname[20])
{
	fstream file("virtualdisk.bin", ios::out | ios::app | ios::binary);

	if (!file)
	{
		cout << "cannot open file" << endl;
	}
	else

		
	{
		//here goes the metadata               

		int filenum; //filenumberentries
		int fsize;

		cout << "number of directories to create : " << endl;
		cin >> filenum;
		fsize = filenum * 4096; //dejar en kb?

		metadata meta;
		strcpy_s(meta.filename, fname);
		meta.filesize = fsize;
		meta.filenumberentries = filenum;
		//meta.filecreator ?inode
		//sa.filecreationdate = return_current_time_and_date(); ocupamos creation date?
		//meta.bitmapsize=0 ?? que size

		file.write(reinterpret_cast<char*>(&meta), sizeof(metadata));

		//inodeentry

		inodeentry inode;

		strcpy_s(inode.name, "/");
		inode.parent = -1;
		strcpy(inode.creationdate, return_current_time_and_date().c_str); //? creationdate
		inode.size = 4096; //?
		inode.firstson = -1;
		inode.rightbrother = -1;
		inode.type = 'D';
		inode.occupied = true;
		//inode.directdatablocks
		//inode.indeirectdatablocks
		
		file.write(reinterpret_cast<char*>(&inode), sizeof(inodeentry));

		for (int i = 0; i < filenum - 1; i++)
		{
			inodeentry newinode;
			file.write(reinterpret_cast<char*>(&newinode), sizeof(inodeentry));
		}

		//datablocks 

		directdatablock temp;
		indirectdatablocklvl1  temp1;
		indirectdatablocklvl2 temp2;
		indirectdatablocklvl3 temp3;

		for (int i = 0; i < filenum; i++)
		{
			file.write(reinterpret_cast<char*>(&temp), sizeof(directdatablock));
		}

		for (int i = 0; i < filenum; i++)
		{
			file.write(reinterpret_cast<char*>(&temp1), sizeof(indirectdatablocklvl1));
		}

		for (int i = 0; i < filenum; i++)
		{
			file.write(reinterpret_cast<char*>(&temp2), sizeof(indirectdatablocklvl2));
		}

		for (int i = 0; i < filenum; i++)
		{
			file.write(reinterpret_cast<char*>(&temp3), sizeof(indirectdatablocklvl3));
		}



		file.close();

	}

}