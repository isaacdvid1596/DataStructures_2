#include "FileRegister.h"



FileRegister::FileRegister()
{
	
}


FileRegister::~FileRegister()
{

}

void FileRegister::createRegister()
{
	char option = '\0';
	
	
	Item element;


	ofstream ofile("Register.dat", ios::out | ios::binary | ios::app);

	do
	{

		if (!ofile)
		{
			cout << "file not found" << endl;
		}
		else
		{
			cout << "Enter the following information : " << endl;

			cout << "Code :" << endl;
			cin >> element.code;

			cin.get();

			cout << "First Name : " << endl;
			cin.getline(element.fname, 30);

			cout << "Last Name : " << endl;
			cin.getline(element.lname, 30);

			cout << "City : " << endl;
			cin.getline(element.city, 30);

			ofile.write(reinterpret_cast<char*>(&element), sizeof(Item));
		}

		cout << "Add more elements ? (y/n) " << endl;
		cin >> option;


	} while (option == 'y' || option == 'Y');


	cout << "CODE : " << element.code << endl;
	cout << "FIRST NAME : " << element.fname << endl;
	cout << "LAST NAME : " << element.lname << endl;
	cout << "CITY : " << element.city << endl;


}

void FileRegister::SSearch(const char * searchname)
{

	Item element;


	string name = searchname;

	ifstream ifile("Register.dat", ios::binary | ios::in);

	if (!ifile)
	{
		cout << "cannot open file" << endl;
	}
	else
	{
		ifile.read(reinterpret_cast<char*>(&element), sizeof(Item));

		while (!ifile.eof())
		{
			if (element.fname == searchname)
			{
				cout << "CODE : " << element.code<< endl;
				cout << "FIRST NAME : " << element.fname << endl;
				cout << "LAST NAME : " << element.lname << endl;
				cout << "CITY : " << element.city << endl;
			}
			ifile.read(reinterpret_cast<char*>(&element), sizeof(Item));

		}

		ifile.close();



	}



	/*
	Item element;

	ifstream ifile("Register.dat", ios::in);

	int currentposition=0;
	
	int res;




	if (!ifile)
	{
		cout << "file not found" << endl;
	}
	else
	{
		while (!ifile.eof())
		{

			ifile.read(reinterpret_cast<char*>(&element), sizeof(Item));
			ifile.seekg(currentposition - sizeof(Item),ios::curs);


			res = strcmp(searchname, element.fname);
			cout << endl;
			cout << res;

			bool flag = false;


			

			if (res == 0)
			{

				currentposition = ifile.tellg();
				//ifile.seekg(currentposition - sizeof(Item),ios::beg);
				//ifile.read(reinterpret_cast<char*>(&element), sizeof(element));

				cout << "CODE : " << element.code << endl;
				cout << "FIRST NAME : " << element.fname << endl;
				cout << "LAST NAME : " << element.lname << endl;
				cout << "CITY : " << element.city << endl;
				break;
			}
			else
			{
				cout << "Element cannot be Found" << endl;
				break;
			}
		}
	}

	ifile.close();
	*/

}

int FileRegister::BSearch(const char *searchname , int left, int right)
{

	ifstream ifile("Register.dat", ios::binary | ios::in);

	Item element;
	int flag, middle;
	if (right >= left)
	{
		middle = left + (right - left) / 2;
		cout << "Left : " << left << " Middle: " << middle << " Right: " << right << endl;

		element = checkPosition(middle);
		flag = strcmp(searchname, element.fname);
		if (dec == 0)
		{
			cout << "Item found : "<<endl;
			cout << "Code : " <<element.code<<endl;
			cout << "First Name : " <<element.fname<<endl;
			cout << "Last Name : " <<element.lname<<endl;
			cout << " City : " << element.city << endl;

			return middle;
		}

		if (dec < 0)
		{
			right = middle - 1;
			BSearch(searchname, left, right);
		}
		if (dec > 0)
		{
			left = middle + 1;
			BSearch(searchname, left, right);
		}



	}

	else
	{
		cout << "Name does not exist" << endl;
	}

	ifile.close();

}