#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>

int main()
{
	
	char ch;
	int line = 0;
	



	std::ofstream fout("Aschars", std::ios::out);

	if (!fout)
	{
		std::cout << "cannot open file \n";
	}

	for (int i = 33; i < 128; i++)
	{
		fout.put((char)(i));
	}

	fout.close();

	std::ifstream fin("Aschars", std::ios::in);




	fin.seekg(0);

	for (int i = 33; i < 128; i++)
	{
		fin.get(ch);
		std::cout<<i<< " = ";
		std::cout.put((char)(i));
		std::cout << "\t";
		if (!(i % 8))
		{
			std::cout << "\n";
			line++;
		}
		if(line>22)
		{
			system("pause");
			line = 0;
		}
	}

	




}