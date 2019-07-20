#include <iostream>
#include <fstream>
#include <cstring>

using  namespace std;

int main()
{
	char input[100];
	strcpy_s(input, "isaac rocks");

	fstream file("isaac.bin", ios::binary | ios::in | ios::out | ios::trunc);

	if (!file)
	{
		cout << "Error when opening file" << endl;
	}
	else
	{
		int length = strlen(input);

		for (int i = 0; i <= length; i++)
		{
			file.put(input[i]);
		}

		file.seekg(0);
		char ch;
		while (file.good())
		{
			file.get(ch);
			cout << ch;
		}
		

	}



}
