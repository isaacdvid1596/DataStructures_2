#include <iostream>
#include <fstream>
#include <conio.h>


int main()
{


	std::ofstream fout("marks.dat", std::ios::out);

	char ans = 'y';

	int rollno;

	float marks;

	if(!fout)
	{
		std::cout << "cannot open file \n";

	}
	else
	{
		while (ans == 'y' || ans == 'Y')
		{
			std::cout << "enter rollno. :";
			std::cin >> rollno;
			std::cout << "enter marks : ";
			std::cin >> marks;
			fout << rollno << '\n' << marks << '\n';
			std::cout << "want to enter more (y/n) \n";
			std::cin >> ans;
		}
	}
	

	fout.close();





}
