#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;


struct Student
{
	string name;
	int roll_number;
};

int main()
{
	ofstream wf("student.bin",ios::out | ios::binary);

	if (!wf)
	{
		cout << "Cannot open file!" << endl;
		return 1;
	}
	else
	{
		Student wstu[3];
		wstu[0].roll_number = 1;
		wstu[0].name = "Ram";
		wstu[1].roll_number = 2;
		wstu[1].name = "Rem";
		wstu[2].roll_number = 3;
		wstu[2].name = "Subaru";

		for (int i = 0; i < 3; i++)
		{
			wf.write((char *)&wstu[i], sizeof(Student));
		}

		wf.close();

		if (!wf.good())
		{
			cout << "Error occurred at writing time" << endl;
			return 1;
		}

		else
		{
			ifstream rf("student.bin" , ios::in | ios::binary);

			if (!rf)
			{
				cout << "Cannot open file!" << endl;
				return 1;
			}

			Student rstu[3];

			for (int i = 0; i < 3; i++)
			{
				rf.read((char *)&wstu[i], sizeof(Student));
			}
			rf.close();
			if (!rf.good())
			{
				cout<<"Error occurred at reading time"<<endl;
				return 1;
			}

			cout << "Student's Details : " << endl;

			for (int i = 0; i < 3; i++)
			{
				cout << "Roll No : " << wstu[i].roll_number << endl;
				cout << "Name : " << wstu[i].name << endl;
				cout << endl;
			}

		}


	}
}