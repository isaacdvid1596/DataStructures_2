#pragma once
#include "structsfile.h"
#include "virtualfilesystem.h"
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

//aux functions



//virtualdisk

void virtualfilesystem::virtualDiskSim(char diskname[20],int dentries)
{
	fstream diskfile("disk.bin",ios::out| ios::binary);

	if (!diskfile)
	{
		cout << "file cannot be found" << endl;
	}
	else
	{
		//disk metadata

		metadata mdata;
		inodeentry inode;

		int diskspace;
		diskspace = (dentries*33308) * 4096; //kb
		diskspace = diskspace/1024/1024/1024; //gb
		strcpy_s(mdata.diskname, diskname); //disk name
		mdata.disksize = diskspace; //total size of disk
		mdata.dd; //date when file is created
		mdata.totaldentries = dentries; //number of total dentries
		mdata.bitmapsize = 0; //bitmap total size
		mdata.directblockscount = 0; //number of direct blocks

		diskfile.write(reinterpret_cast<char*>(&mdata), sizeof(metadata));

		//bitmap

		//inodeEntry

		for (int i = 0; i < dentries; i++)
		{
			diskfile.write(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
		}

		
		

	}
	diskfile.close();
}


void virtualfilesystem::readvirtualdisk()
{


	cout << "reading file now" << endl;

	ifstream idiskfile("disk.bin", ios::in);

	metadata mdata;
	inodeentry inode;

	if (!idiskfile)
	{
		cout << "file cannot be found" << endl;
	}

	idiskfile.read(reinterpret_cast<char*>(&mdata), sizeof(metadata));

	cout << "Disk Name : " << mdata.diskname << endl;
	cout << "Disk Size : " << mdata.disksize << endl;
	cout << "Disk Creation Date : " << mdata.dd.d_day << "/" << mdata.dd.d_month << "/" << mdata.dd.d_year << endl;
	cout << "Disk total Directory Entries : " << mdata.totaldentries << endl;
	cout << "Bitmap Size : " << mdata.bitmapsize << endl;
	cout << "Direct Block Count : " << mdata.directblockscount << endl;

	cout << endl;
	cout << endl;

	int metasize = sizeof(metadata);


	idiskfile.seekg(metasize);

	idiskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));


	
	while (!idiskfile.eof())
	{
		cout << "inode name : " << inode.name << endl;
		cout << "inode creation date : " << inode.id.d_day << "/" << inode.id.d_month << "/" << inode.id.d_year << endl;
		cout << "inode parent : "<<inode.parent<< endl;
		cout << "inode first son : " << inode.firstson << endl;
		cout << "inode right brother : " << inode.rightbrother << endl;
		cout << "inode type : " << inode.type << endl;
		cout << "inode size : " << inode.size << endl;
		cout << "inode occupied : " << inode.occupied << endl;
		cout << endl;
		cout << endl;

		idiskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
	}

	idiskfile.close();

}

void virtualfilesystem::mkdiraux(int parent, char name[25])
{
	ifstream idiskfile("disk.bin", ios::in | ios::binary);
	//open file


	if (!idiskfile)
	{
		cout << "file cannot be found" << endl;
	}
	else
	{
		idiskfile.seekg(0, ios::beg); //set readpointer to very beginning 
		int isempty = -1; // null isempty variable
		
		

		bool isfirstchild = false; //bool that verifies if inode is fc
		
		//create instances of structs
		metadata meta;
		inodeentry inode;


		//read  metadata struct
		idiskfile.read(reinterpret_cast<char*>(&meta), sizeof(metadata));
		int size = sizeof(metadata);//size that contains sizeof whole metadata struct 
		idiskfile.seekg(size);//set readpointer to end of metadata , end of inode
		idiskfile.read(reinterpret_cast<char*>(&inode),sizeof(inodeentry));
		//read the inode struct from the very beginning 

		int totaldentries = meta.totaldentries;//total directory entries 



		//for cycle goes from 0 to number of total directory entries 
		for (int i = 0; i < totaldentries; i++)
		{
			idiskfile.seekg(size + (sizeof(inodeentry) * i)); 
			//set readpointer currently on end of metada to beg of inode +sizeof(inode) * every iteration
			idiskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));


			//if index equal to parent pos parameter and inode type is directory
			if (i == parent && (inode.type == 'D'))
			{

				

				if (inode.firstson == -1)
				{
					isfirstchild = true; // if first son info on inode is -1 then true
				}

				if (inode.firstson != -1)
				{
					isfirstchild = false;
				}
			}


			//if inode is not occupied and isempty is null;
			if (inode.occupied == false && isempty == -1)
			{
				isempty = i; //assign index to isempty
			}

			


		}

		idiskfile.close();

		if (isempty != -1)
		{
			mkdir(isempty, parent, isfirstchild, name);
		}
		else
		{
			cout << "virtual disk is full" << endl;
		}


	}




//virtualdisksystem commands 
}
void virtualfilesystem::mkdir(int isempty, int parent, bool isfirstchild, char name[25])
{
	fstream diskfile("disk.bin", ios::out | ios::in | ios::binary);



	int size = sizeof(metadata);

	if (!diskfile)
	{
		cout << "cannot open file" << endl;
	}
	else
	{

		inodeentry inode;

		inode.occupied = true;

		

		int readpointer = size + (sizeof(inodeentry) * isempty);
		diskfile.seekg(readpointer);  
		diskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
		strcpy_s(inode.name, name);
		inode.parent = parent;
		inode.occupied = true;
		diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp()));
		inode.type = 'D';
		diskfile.write(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
		diskfile.seekg(readpointer);
		diskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
		

		if (isfirstchild == true)
		{
			inodeentry inode1;

			diskfile.seekg(sizeof(metadata) + (sizeof(inodeentry) * parent));
			diskfile.read(reinterpret_cast<char*>(&inode1), sizeof(inodeentry));
			cout << "parent is " << inode1.name << endl;
			diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp()));
			inode1.firstson = isempty;
			diskfile.write(reinterpret_cast<char*>(&inode1), sizeof(inodeentry));
		}
		else
		{
			
			//change of number to brother

			inodeentry inode2;
			diskfile.seekg(sizeof(metadata) + sizeof(inodeentry));
			diskfile.read(reinterpret_cast<char*>(&inode2), sizeof(inodeentry));
			inode2.rightbrother = isempty;
			diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp()));
				
			diskfile.write(reinterpret_cast<const char*>(&inode2), sizeof(inodeentry));
		}


	}
	diskfile.close();

}


int virtualfilesystem::cd(char name[25],int parent) //cd function
{
	ifstream idiskfile("disk.bin", ios::in | ios::binary);

	if (!idiskfile)
	{
		cout << "file cannot be found" << endl;
	}
	else
	{
		idiskfile.seekg(0, ios::beg); //set read pointer to beginning

		metadata meta; //intance metadata

		idiskfile.read(reinterpret_cast<char*>(&meta), sizeof(metadata));

		int totaldentries = meta.totaldentries;

		inodeentry inode;

		int size = sizeof(metadata); //size equal to end of metadata , beg of inodeentry

		idiskfile.seekg(size); //place read pointer in beg of inodeentry struct

		idiskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));

		for (int i = 0; i < totaldentries; i++)
		{
			idiskfile.seekg(size + (sizeof(inodeentry)*i));

			idiskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));

			if (strcmp(inode.name, name) == 0 && inode.parent == parent)
			{
				cout << "name : " << inode.name << endl;
				return i;
			}
		}

		if (strcmp(inode.name, name) !=0)
		{
			cout << "directory cannot be found" << endl;
		}


	}
}


//sin probar 
int virtualfilesystem::cdback(int parentpos) //cd.. function  , receives parent position 
{
	inodeentry inode;

	ifstream idiskfile("disk.bin", ios::in | ios::out | ios::binary);

	int size = sizeof(metadata);
	idiskfile.seekg(size + (sizeof(inodeentry) * parentpos));
	idiskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));


	if (inode.parent!=-1)
	{
		return inode.parent;
	}
	else
	{
		cout << "currently in main directory" << endl;
		return 0;
	}

}

//bitmap
