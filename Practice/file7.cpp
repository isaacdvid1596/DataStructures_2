#include <iostream>
#include <fstream>
#include <stdlib.h>

class student
{
	char name[20];
	char grade;
	float marks;

public:
	void getdata();
	void display();

};

void student::getdata()
{
	char ch;
	std::cin.get(ch);
	std::cout << "enter name : ";
	std::cin.get(name, 20);
	std::cout << "enter grade :";
	std::cin >> grade;
	std::cout << "enter marks : ";
	std::cin >> marks;
	std::cout << "\n";
}

void student::display()
{
	std::cout << "name : " << name << "\t grade: " << grade << " \t marks : " << marks << "\n";
}





int main()
{
	char fname[20];
	student cse[3];
	


	std::cout << "enter file name :";
	std::cin.get(fname, 20);

	std::fstream  fio(fname, std::ios::in || std::ios::out);

	if (!fio)
	{
		std::cout << "error opening file \n";
	}

	else
	{
		std::cout << "enter details for the 3 students \n";
		for (int i = 0; i < 3; i++)
		{
			cse[i].getdata();
			fio.write(reinterpret_cast<char*>(&cse[i]), sizeof(cse[i]));
		}
	}

	fio.seekg(0); //resets file to start to access file from beginning

	std::cout << "the content of " << fname << " are shown below : \n";
	
	for (int i = 0; i < 3; i++)
	{
		fio.read(reinterpret_cast<char*>(&cse[i]), sizeof(cse[i]));
		cse[i].display();
	}

	fio.close();



}