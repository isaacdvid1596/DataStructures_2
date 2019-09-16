#pragma once
#pragma warning(disable:4996)
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
	fstream diskfile("disk.bin",ios::out| ios::app| ios::binary);

	if (!diskfile)
	{
		cout << "file cannot be found" << endl;
	}
	else
	{
		//disk metadata

		metadata mdata;
		inodeentry inode;

		time_t now = time(0);
		tm* lcltm = localtime(&now);

		int diskspace;
		diskspace = (dentries*33308) * 4096; //kb
		diskspace = diskspace/1024/1024; //gb
		strcpy_s(mdata.diskname, diskname); //disk name
		mdata.disksize = diskspace; //total size of disk
		mdata.dd; //date when file is created
		mdata.totaldentries = dentries; //number of total dentries
		mdata.bitmapsize = 0; //bitmap total size
		mdata.directblockscount = 0; //number of direct blocks

		diskfile.write(reinterpret_cast<char*>(&mdata), sizeof(metadata));

		//bitmap



		//inodeEntry

		diskfile.seekp(0, ios::beg);
		int size = sizeof(metadata);
		diskfile.seekp(size);


		//root creations

		inodeentry root;
		strcpy_s(root.name, "root");
		root.id.d_day = lcltm->tm_mday;
		root.id.d_month = lcltm->tm_mon + 1;
		root.id.d_year = lcltm->tm_year + 1900;
		root.firstson = -1;
		root.rightbrother = -1;
		root.type = 'D';
		root.parent = -1;
		root.size = 0;
		root.occupied = true;
		root.lastchild = -1; //rm ref

		diskfile.write(reinterpret_cast<char*>(&root), sizeof(inodeentry));
		


		for (int i = 0; i < dentries-1; i++)
		{
			diskfile.write(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
		}

		//datablocks
		directdatablock directdb;
		indirectdatablocklvl1 dblvl1;
		indirectdatablocklvl2 dblvl2;
		indirectdatablocklvl3 dblvl3;
		

		//number of directory entries * number of direct blocks
		//12 direct blocks + 16 indirect lvl1 indirect


		
		for (int i = 0; i < dentries * (33308); i++)
		{
			diskfile.write(reinterpret_cast<char*>(&directdb), sizeof(directdatablock));
		}
		
		


		//1 indirect lvl per entry

		for (int i = 0; i < dentries;i++)
		{
			diskfile.write(reinterpret_cast<char*>(&dblvl1),sizeof(indirectdatablocklvl1));
		}
				
		for (int i = 0; i < dentries; i++)
		{
			diskfile.write(reinterpret_cast<char*>(&dblvl2), sizeof(indirectdatablocklvl2));
		}

		for (int i = 0; i < dentries; i++)
		{
			diskfile.write(reinterpret_cast<char*>(&dblvl3), sizeof(indirectdatablocklvl3));
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
	cout << "Disk Size : " << mdata.disksize <<" MB "<< endl;
	cout << "Disk Creation Date : " << mdata.dd.d_day << "/" << mdata.dd.d_month << "/" << mdata.dd.d_year << endl;
	cout << "Disk total Directory Entries : " << mdata.totaldentries << endl;
	cout << "Bitmap Size : " << mdata.bitmapsize << endl;
	cout << "Direct Block Count : " << mdata.directblockscount << endl;

	cout << endl;
	cout << endl;

	int metasize = sizeof(metadata);


	idiskfile.seekg(metasize);

	idiskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
	cout << mdata.totaldentries << endl;

	
	for(int i=0;i<mdata.totaldentries;i++)
	{
		cout << "inode name : " << inode.name << endl;
		cout << "inode creation date : " << inode.id.d_day << "/" << inode.id.d_month << "/" << inode.id.d_year << endl;
		cout << "inode parent : "<<inode.parent<< endl;
		cout << "inode first son : " << inode.firstson << endl;
		cout << "inode right brother : " << inode.rightbrother << endl;
		cout << "inode type : " << inode.type << endl;
		cout << "inode size : " << inode.size << endl;
		cout << "inode occupied : " << inode.occupied << endl;
		cout << "inode last child ref : " << inode.lastchild << endl;
		cout << endl;
		cout << endl;

		idiskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
		//break;
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

		time_t now = time(0);
		tm* lcltm = localtime(&now);

		inodeentry inode;

		inode.occupied = true;

		

		int readpointer = size + (sizeof(inodeentry) * isempty);
		diskfile.seekg(readpointer);  
		diskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
		strcpy_s(inode.name, name);
		inode.parent = parent;
		inode.occupied = true;
		inode.id.d_day = lcltm->tm_mday;
		inode.id.d_month = lcltm->tm_mon + 1;
		inode.id.d_year = lcltm->tm_year + 1900;
		inode.type = 'D';
		diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp()));
		diskfile.write(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
		diskfile.seekg(readpointer);
		diskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
		

		if (isfirstchild == true)
		{
			inodeentry inode1; //parent 

			diskfile.seekg(sizeof(metadata) + (sizeof(inodeentry) * parent));
			diskfile.read(reinterpret_cast<char*>(&inode1), sizeof(inodeentry));
			cout << "parent is " << inode1.name << endl;
			diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp()));
			inode1.firstson = isempty;
			cout << isempty << endl;
			diskfile.write(reinterpret_cast<char*>(&inode1), sizeof(inodeentry));
		}
		else
		{
			inodeentry inode1;
			diskfile.seekg(sizeof(metadata) + sizeof(inodeentry)*parent);
			diskfile.read(reinterpret_cast<char*>(&inode1), sizeof(inodeentry));
			cout << "parent is : " << inode1.name << endl;
			diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp()));
			int x = inode1.lastchild;
			inode1.lastchild = isempty;
			cout << inode1.lastchild << endl;
			diskfile.write(reinterpret_cast<const char*>(&inode1), sizeof(inodeentry));



			//change of number to brother

			inodeentry inode2;
			diskfile.seekg(sizeof(metadata) + sizeof(inodeentry)*x);
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
		cout << "currently in root :" << endl;
		return 0;
	}

}

void virtualfilesystem::ls(int parent)
{
	bool flag = true;


	ifstream idiskfile("disk.bin", ios::in | ios::binary);

	metadata meta;

	//create instance of metadata and read struct

	idiskfile.read(reinterpret_cast<char*>(&meta), sizeof(metadata));


	int totalofdentries = meta.totaldentries;

	inodeentry inode;
	idiskfile.seekg(sizeof(metadata) + sizeof(inodeentry) * parent);
	idiskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
	
	if (!idiskfile)
	{
		cout << "cannot open file" << endl;
	}
	else
	{
		inodeentry inode1;
		int size = sizeof(metadata);
		idiskfile.seekg(size);
		idiskfile.read(reinterpret_cast<char*>(&inode1), sizeof(inodeentry));	

		for (int i = 0; i < totalofdentries; i++)
		{
			idiskfile.seekg(size + (sizeof(inodeentry)*i));
			idiskfile.read(reinterpret_cast<char*>(&inode1), sizeof(inodeentry));

			if (inode1.parent == parent)
			{
				cout << "name : " << inode1.name << endl;
				cout << "size : " <<inode1.size<< endl;
				cout << "type : " << inode1.type << endl;
				cout << "-------" << endl;
				flag = false;
			}

			if (flag == true)
			{
				cout << "no entries found on this directory" << endl;
			}

		}



	}
}



void virtualfilesystem::rm(int pos)
{
	bool flag = true;
	inodeentry actualinode, inode1;

	fstream diskfile("disk.bin", ios::in | ios::out | ios::binary);

	int size = sizeof(metadata);
	diskfile.seekg(size + (sizeof(inodeentry) * pos));
	diskfile.read(reinterpret_cast<char*>(&actualinode), sizeof(inodeentry));

	if (actualinode.firstson == -1 && actualinode.rightbrother == -1)
	{
		diskfile.seekg(size + (sizeof(inodeentry) * pos));
		diskfile.read(reinterpret_cast<char*>(&actualinode), sizeof(inodeentry));
		diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp()));
		diskfile.write(reinterpret_cast<char*>(&inode1), sizeof(inodeentry));
	}
	else if (actualinode.firstson != 1)
	{
		rmaux(actualinode.firstson);
		diskfile.seekg(size + (sizeof(inodeentry) * pos));
		diskfile.read(reinterpret_cast<char*>(&actualinode), sizeof(inodeentry));
		diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp()));
		diskfile.write(reinterpret_cast<char*>(&inode1), sizeof(inodeentry));
		flag = false;
	}
	else if (actualinode.rightbrother != -1)
	{
		rm(actualinode.rightbrother);
		diskfile.seekg(size + (sizeof(inodeentry) * pos));
		diskfile.read(reinterpret_cast<char*>(&actualinode), sizeof(inodeentry));
		diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp()));
		diskfile.write(reinterpret_cast<char*>(&inode1), sizeof(inodeentry));
		flag = false;

	}
	


	/*
	fstream diskfile("disk.bin", ios::in | ios::out | ios::binary);

	if (!diskfile)
	{
		cout << "cannot open file" << endl;
	}
	else
	{


		diskfile.seekg(0, ios::beg); //set read pointer 

		
		metadata meta;

		diskfile.read(reinterpret_cast<char*>(&meta), sizeof(metadata));//read metada to get dentries

		inodeentry inode;
		int size=sizeof(metadata);
		diskfile.seekg(size); //set read pointer to beg of inode struct
		diskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));

		int totaldentries = meta.totaldentries;
		inodeentry in;
		diskfile.seekg(size + (sizeof(inodeentry) * parent));
		diskfile.read(reinterpret_cast<char*>(&inode), sizeof(inodeentry));
		diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp())); //rewrite structure by giving it negtive offset 
		diskfile.write(reinterpret_cast<char*>(&in), sizeof(inodeentry));


		diskfile.close();
	}
	*/
}


void virtualfilesystem::rmaux(int pos)
{
	inodeentry actualinode, p;
	
	fstream diskfile("disk.bin", ios::in | ios::out | ios::binary);

	int size = sizeof(metadata);
	diskfile.seekg(size + (sizeof(inodeentry) * pos));
	diskfile.read(reinterpret_cast<char*>(&actualinode), sizeof(inodeentry));

	if (actualinode.firstson != -1)
	{
		rm(actualinode.firstson);
		diskfile.seekg(size + (sizeof(inodeentry) * pos));
		diskfile.read(reinterpret_cast<char*>(&actualinode), sizeof(inodeentry));
		diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp()));
		diskfile.write(reinterpret_cast<char*>(&p), sizeof(inodeentry));
	}
	else
	{
		diskfile.seekg(size + (sizeof(inodeentry) * pos));
		diskfile.read(reinterpret_cast<char*>(&actualinode), sizeof(inodeentry));
		diskfile.seekp(-(sizeof(inodeentry) - diskfile.tellp()));
		diskfile.write(reinterpret_cast<char*>(&p), sizeof(inodeentry));
	}

}




//bitmap

char* virtualfilesystem::initializebitmap(int n)
{
	char* bitmap;

	bitmap = new char[n/8];
	for (int i = 0; i < n / 8; i++)
	{
		bitmap[i] = 0;
	}

	return bitmap;
}

void printbitmap(char* bitmap, int ndblocks)
{
	const int shift = 8 * sizeof(char) - 1;
	const char mask = 1 >> shift;

	for (int i = 0; i < ndblocks/8; i++)
	{
		char value;
		value = bitmap[i];
		for (int j = 1; j <= shift + 1; j++)
		{
			cout << (value & mask ? '1' : '0');
			value << 1;

			if (j % 8 == 0)
			{
				cout << ' ';
			}

		}
	}
	cout << endl; 
}

char* virtualfilesystem::bitmapon(char* bitmap, int ndblocks)
{
	int bytepos = ndblocks / 8;
	int initialpos = (ndblocks / 8) * 8;

	for (int i = initialpos, x = 7; i < (bytepos * 8); i++, x--)
	{
		if (i == ndblocks)
		{
			bitmap[bytepos] |= 1 << x;
			break;
		}
	}

	return bitmap;
}

char* virtualfilesystem::bitmapoff(char* bitmap, int ndblocks)
{
	int bytepos = ndblocks / 8;
	int initialpos = (ndblocks / 8) * 8;

	for (int i = initialpos, x = 7; i < (bytepos * 8); i++, x--)
	{
		if (i == ndblocks)
		{
			bitmap[bytepos] &= ~(1 << x);
			break;
		}
	}

	return bitmap;
}
