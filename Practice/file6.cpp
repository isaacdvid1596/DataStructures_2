#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

struct customer
{
	char name[20];
	float balance;

	void showaccount();

};

void customer::showaccount()
{
	
	std::cout << "account Holder Name : " << name << "\n";
	std::cout << "balance Amount : " << balance << "\n";
}

int main()
{
	customer savac;
	std::cout << "enter your name\n";
	std::cin.get(savac.name, 20);
	std::cout << "enter balance\n";
	std::cin >> savac.balance;

	std::ofstream fout("saving.dat", std::ios::out | std::ios::binary);

	if (!fout)
	{
		std::cout << "file cannot be opened \n";
		std::cout << "press any key to exit\n";
	
	}

	fout.write(reinterpret_cast<char*>(&savac), sizeof(customer));
	fout.close();

	
	
	std::ifstream fin("saving.data", std::ios::in | std::ios::binary);


	while (!fin.eof())
	{
		fin.read(reinterpret_cast<char*>(&savac), sizeof(customer));
		savac.showaccount();
		break;
	}
	fin.close();
	
	

	//std::cout << savac.name;
	//std::cout << "has the balance amount of Rs. " << savac.balance << "\n";







}
