#include <iostream>
#include <fstream>
#include <stdlib.h>

class student
{
private:
	int rollno;
	char name[20];
	char branch[3];
	float marks;
	char grade;

public:
	void getdata();
	void putdata();
	int getrno();



};

void student::getdata()
{
	std::cout << "rollno : ";
	std::cin >> rollno;
	std::cout << " name : ";
	std::cin >> name;
	std::cout << "branch : ";
	std::cin >> branch;
	std::cout << "marks : ";
	std::cin >> marks;

	if (marks >= 75)
	{
		grade = 'A';
	}
	else if (marks >= 60)
	{
		grade = 'B';
	}
	else if (marks >= 50)
	{
		grade = 'C';
	}
	else if (marks >= 40)
	{

	}
	else
		grade = 'F';


}

void student::putdata()
{
	std::cout << name << ", rollno " << rollno << " has " << marks << " % marks and " << grade << " grade." << "\n";
}

int student::getrno()
{
	return rollno;
}



int main()
{

	student stud1;

	std::ofstream fout("marks.dat", std::ios::out);

	char ans = 'y';

	if (!fout)
	{
		std::cout << "cannot open file \n";
	}
	else
	{
		while (ans == 'y' || ans == 'Y')
		{
			stud1.getdata();
			fout.write(reinterpret_cast<char*>(&stud1), sizeof((stud1)));
			std::cout << "record added succesfully\n";
			std::cout << "want to enter more (y/n)";
			std::cin >> ans;
		}
	}


	fout.close();

	int rno;

	char found;

	std::ifstream fin("marks.dat", std::ios::in);

	if (!fin)
	{
		std::cout << "cannot open file \n";
	}
	else
	{
		ans = 'y';
		while (ans == 'y' || ans == 'Y')
		{

			found = 'n';
			std::cout << "enter rollno to search : ";
			std::cin >> rno;

			while (!fin.eof())
			{
				fin.read(reinterpret_cast<char*>(&stud1), sizeof(stud1));
				if (stud1.getrno() == rno)
				{
					stud1.putdata();
					found = 'y';
					break;
				}
			}

			if (found == 'n')
			{
				std::cout << "rollno cannot be found on file \ n";
			}
			std::cout << "want to search more (y/n)";
			std::cin >> ans;

		}

		fin.close();

	}



	




}





