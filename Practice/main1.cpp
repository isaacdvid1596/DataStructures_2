#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

int main()
{
	char inform[80];
	char fname[20];

	char ch;

	cout << "Enter file name : ";
	cin.get(fname, 20);
	ofstream ofile(fname, ios::out);

	if (!ofile)
	{
		cout << "error in creating file" << endl;
		cout << "press any key to exit" << endl;
	}

	cin.get(ch);

	cout << "Enter a line to store in the file : \n";
	cin.get(inform, 80);
	ofile << inform << endl;

	cout << "entered information successfully stored" << endl;
	ofile.close();
	cout << "press any key to exit" << endl;

}