#include <iostream>
#include <fstream>

struct item
{
	int code;
	char names[30];
	char lastnames[30];
	char city[50];
};

void createRegister()
{
	std::fstream fio;

	item element;

	fio.open("Register.dat", std::ios::out | std::ios::in | std::ios::app);

	std::cout << "Enter code : ";
	std::cin >> element.code;

	std::cin.get();

	std::cout << "Enter first name : ";
	std::cin.getline(element.names, 30);

	std::cout << "Enter last name : ";
	std::cin.getline(element.lastnames, 30);

	std::cout << "enter city : ";
	std::cin.getline(element.city, 50);

	if (!fio)
	{
		std::cout << "file not found /n";
	}
	else
	{
		fio.write(reinterpret_cast<char*>(&element), sizeof(item));

		fio.close();
	}


}

void sequentialsearch()
{

	std::ifstream fin("Register.dat", std::ios::in);

	if (!fin)
	{
		std::cout << "file not found \n";
	}
	
	else
	{

		item element;

		int searchcode;
		long pos;
		char found = 'f';


		std::cout << "enter the item code you want to look up ";
		std::cin >> searchcode;

		while (!fin.eof())
		{
			pos = fin.tellg();
			
			fin.read(reinterpret_cast<char*>(&element), sizeof(item));


		}

		if (element.code == searchcode)
		{
			std::cout << "element found \n";

		}
		else
			std::cout << "element not found \n";


	}

	

}

void binarysearch()
{

}


int main()
{
	
	//int option;




	//std::cout << "---menu--- \n";
	//std::cout<<""
	


	createRegister();

	sequentialsearch();

}