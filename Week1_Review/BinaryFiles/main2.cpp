#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{

	int a[] = { 1,2,3 };
	int b[3];

	fstream f;

	f.open("dog.bin", ios::out | ios::binary);

	if (f)
	{

		f.write(reinterpret_cast<char*>(a), 3 * sizeof(int));


		f.close();
	}
	else
	{
		cout << "error opening file for writing" << endl;
		exit(1);
	}


	//write contents of file dog.bin to array b


	f.open("dog.bin", ios::in | ios::binary);

	if (f)
	{
		f.read(reinterpret_cast<char*>(b), 3 * sizeof(int));
	}
	else
	{
		cout << "error opening file for reading" << endl;
		exit(2);
	}


	for (int i = 0; i < 3; i++)
	{
		cout << b[i] << endl;
	}

}