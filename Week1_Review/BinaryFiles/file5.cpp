#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	fstream file("isaac3.txt", ios::out | ios::in);

	if (!file)
	{
		cout << "Error";
	}

	else
	{
		cout << file.tellg() << endl;
		cout << file.tellg() << endl;
		file.seekp(2);
		cout << file.tellg() << endl;
		cout << file.tellg() << endl;
	}


	/*
	ofstream file("isaac3.txt", ios::out);

	if (!file)
	{
		cout << "Error" << endl;
	}
	else
	{
		cout << file.tellp() << endl;
		file << "isaac is jojo";
		cout << file.tellp() << endl;
		file.seekp(5);
		file << " and dio" << endl;
		cout << file.tellp() << endl;
	}
	*/



	/*
	ifstream file("isaac.txt", ios::in);

	if (!file)
	{
		cout << "Error" << endl;
	}

	else
	{
		cout << file.tellg() << endl;

		string line;

		file.seekg(2);

		getline(file, line);

		cout << line;

	}

	*/

}
