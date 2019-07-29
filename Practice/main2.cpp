#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

int main()
{
	ofstream ofile;
	ifstream ifile;

	char fname[20];
	char rec[80], ch;

	cout << "enter file name" << endl;
	cin.get(fname, 20);

	ofile.open(fname, ios::out);

	if (!ofile)
	{
		cout << "error in opening the file" << endl;
		
		exit(1);
	}

	cin.get(ch);

	cout << "enter a line to store in the file : \n ";
	cin.get(rec, 80);
	ofile << rec << endl;
	cout << "the entered line stored in the file" << endl;
	cout << "press any key to see" << endl;
	ofile.close();

	ifile.open(fname, ios::in);

	if (!ifile)
	{
		cout << "error in opening the file" <<fname<< endl;
		cout << "press any key to exit" << endl;
		exit(2);
	}
	cin.get(ch);
	ifile.get(rec, 80);
	cout << "the file contains" << endl;
	cout << rec;
	cout << "press any key to exit" << endl;
	ifile.close();



}