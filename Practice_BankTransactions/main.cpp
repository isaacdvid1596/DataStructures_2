#include <iostream>
#include <fstream>

using namespace std;


void operationMenu();


struct BankAccount
{
	char accNumber[10];
	char custName[25];
	float accBalance;
};

int main()
{


	
	BankAccount cust1;
	BankAccount cust2;
	BankAccount cust3;
	

	//need to create an array of customers

	ofstream examplewfile("example.dat", ios::out | ios::binary);

	if (!examplewfile)
	{
		cout << "Cannot open file" << endl;
		return 1;
	}

	strcpy_s(cust1.accNumber, "58988");
	strcpy_s(cust1.custName, "Eren");
	cust1.accBalance = 988.85;


	strcpy_s(cust2.accNumber, "87876");
	strcpy_s(cust2.custName, "Emanuel");
	cust2.accBalance = 500.00;


	strcpy_s(cust3.accNumber, "77787");
	strcpy_s(cust3.custName, "Leah");
	cust3.accBalance = 6000.84;

	for (int i = 0; i < 3; i++)
	{
		examplewfile.write(reinterpret_cast<char*>(&cust1), sizeof(BankAccount));
	}


	examplewfile.close();

	if (!examplewfile.good())
	{
		cout << "Error occurred at writing time" << endl;
		return 1;
	}

	ifstream examplerfile("example.dat", ios::in | ios::binary);

	if (!examplerfile)
	{
		cout << "Cannot open file " << endl;
	}

	for (int i = 0; i < 3; i++)
	{
		examplerfile.read(reinterpret_cast<char*>(&cust1), sizeof(BankAccount));
	}

	cout << "file created succesfully" << endl;
	examplerfile.close();

	if (!examplerfile.good())
	{
		cout << "Error occurred at reading time" << endl;
		return 1;
	}

	for (int i = 0; i < 3; i++)
	{
		cout << "Account Number : " << cust1.accNumber << endl;
		cout << "Name : " << cust1.custName << endl;
		cout << "Balance : " << cust1.accBalance << endl;
	}





	//registering account

	/*
		cout << "Enter account number / name / balance " << endl;

		cin.getline(cust1.accNumber, 5);
		cin.getline(cust1.custName, 25);
		cin >> cust1.accBalance;

	
	

	cout << "printing all info on screen" << endl;

	
		cout <<"Account Number : "<< cust1.accNumber << endl;
		cout <<"Name : "<<cust1.custName << endl;
		cout <<"Balance : "<< cust1.accBalance << endl;
	*/
	
	
}

/*
void operationMenu()
{
	int operation;


	cout << "---MENU---" << endl;
	cout << "Select Operation Type" << endl;
	cout << "1-Deposit" << endl;
	cout << "2-Withdraw" << endl;
	cout << "3-Exit" << endl;

	cin >> operation;

	switch (operation)
	{
	case 1:
		cout<<"Enter account number"
			
		break;

	case 2:
		break;

	case 3:
		break;


	}

}
*/