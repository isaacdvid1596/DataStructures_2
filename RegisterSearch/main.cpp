#include <iostream>
#include <fstream>
#include "CounterClock.h"
#include "FileRegister.h"

using namespace std;

int main()
{
	FileRegister fr;
	char name[30];
	

	//fr.createRegister();
	
	//cin.get();

	cout << "name you are searching for" << endl;


	cin.getline(name, 30);

	//cout << endl;

	//cout << name;


	fr.SSearch(name);

}