#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>


int main()
{

	char fname[20], ch;
	char ans = 'y';
	int rollno;
	float marks;

	
	

	std::cout << "enter file name \n";
	std::cin.get(fname, 20);
	std::cin.get(ch);

	std::ofstream fout(fname, std::ios::app);


	if (!fout)
	{
		std::cout << "cannot open file\n";

	}
	else
	{
		while (ans == 'y' | ans == 'Y')
		{
			std::cout << "Enter roll no: ";
			std::cin >> rollno;
			std::cout << "Enter marks: ";
			std::cin >> marks;
			fout << rollno << " \n" << marks << "\n";
			std::cout << "want to enter more? (y/n)";
			std::cin >> ans;
		}
	}

	fout.close();

}
