#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{

	fstream file("isaac2.txt", ios::in | ios::out | ios::app);

	if (!file)
	{
		cout << "Error while opening the file" << endl;
	}
	else
	{
		cout << "file opened succesfully" << endl;

		cout << "Writing to the file" << endl;

		file << "isaac rocks" << endl;

		file.seekg(0);

		cout << "reading from the file" << endl;

		string line;

		while (file.good())
		{
			getline(file, line);
			cout << line << endl;
		}

	}


	/*

	ifstream file;

	file.open("isaac.txt");

	if (!file)
	{
		cout << "Error while opening the file" << endl;
	}
	else
	{
		cout << "Reading from the file , contents are : " << endl;
		string line;
		while (file.good())
		{
			getline(file, line);
			cout << line << endl;
		}
		
	}
	*/


	/*
	ofstream file ("isaac.txt");

	if (!file)
	{
		cout << "unable to open file" << endl;
	}
	else
	{
		file << "Isaac rocks" << endl;
		file << "We have cookies...";
		file.close();
		cout << "Succesfully written to the file , open and check" << endl;
	}

	*/


}