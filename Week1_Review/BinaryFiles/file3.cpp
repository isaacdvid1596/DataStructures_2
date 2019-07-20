#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{

	fstream file;

	file.open("anil.txt", ios::in|ios::out |ios::trunc);

	if (!file.is_open())
	{
		cout << "Error while opening file" << endl;
	}
	else
	{
		file.close();
	}


}