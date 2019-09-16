#include <iostream>
#include <fstream>
#include "structsfile.h"
#include "virtualfilesystem.h"

using namespace std;



int main()
{

	virtualfilesystem vfs;

	/*
	virtualfilesystem vfs;

	
	
	char diskname[20];
	int dentries;

	cout << "Enter virtual disk name" << endl;
	cin.getline(diskname, 20);
	cout << "Enter number of directory entries" << endl;
	cin >> dentries;
	vfs.virtualDiskSim(diskname,dentries);

	vfs.readvirtualdisk();

	

	cout << "exiting program" << endl;
	*/

	int pos = 0; //position we send as parameter
	bool flag = true;
	//bool create = true;
	char name[20];
	int dentries;
	char path[30];
	
	
	cout << "---FILE SYSTEM TERMINAL---" << endl;
	
	do
	{

		char command[30];
		cout << "usr@virtualdisk:~$ : ";
		cin >> command;
		int x=0;

	
	


		if (x=strcmp(command, "vfs")==0)
		{
			cout << x << endl;
			cout << command << endl;
			//create == true;
			cout << "disk name :" << endl;
			cin >> name;
			cout << "everything is chill" << endl;
			cout << "number of directory entries : ";
			cin >> dentries;
			cout << "still chilling" << endl;
			
			vfs.virtualDiskSim(name, dentries);
			vfs.readvirtualdisk();
		}
		
		if (x = strcmp(command, "mkdir") == 0)
		{
			cout << "mkdir : ";
			cin>>name;
			vfs.mkdiraux(pos,name);

			vfs.readvirtualdisk();
		}

		if (strcmp(command, "cd") == 0) 
		{

			cout << "cd:";
			cin >> name;
			pos = vfs.cd(name, pos);
			

		}

		if (strcmp(command, "cd..") == 0)
		{
			cout << "cd.. : ";
			pos = vfs.cdback(pos);
		}


		if(strcmp(command, "ls")==0)
		{
			vfs.ls(pos);
		}

		if (strcmp(command, "rm") == 0)
		{
			
			int pos1 = pos;
			pos = vfs.cdback(pos);
			vfs.rm(pos1);
			cout << pos1 << endl;
			vfs.readvirtualdisk();
			
			/*
			int pos1 = pos;
			pos = vfs.cdback(pos);
			vfs.rmaux(pos1);
			vfs.readvirtualdisk();
			*/
		}


		//import
		//export


	} while (flag == true);



}