#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;


class Person
{
	char name[80];
	int age;
public:
	Person()
	{
		strcpy_s(name, "no name");
		age = 0;
	}
	Person(const char *name, int age)
	{
		strcpy_s(this->name, name);
		this->age = age;
	}

	void whoAreU()
	{
		cout << "i am " << name << " and i am " << age << " years old" << endl;
	}

};



int main()
{
	Person isaac("Dio", 22);
	Person david;

	fstream file("person.dat", ios::binary | ios::in | ios::out | ios::trunc);


	if (!file)
	{
		cout << "Error while opening" << endl;

	}

	else
	{
		file.write((char *)&isaac, sizeof(Person));

		file.seekg(0);

		


		file.read((char*)&david, sizeof(Person));


		char ch;
		while (file.good())
		{
			file.get(ch);
			cout << ch;
		}

	}

	

	

}
