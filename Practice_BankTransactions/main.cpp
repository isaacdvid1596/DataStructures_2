#include <iostream>
#include <fstream>
#include "Account.h"

using namespace std;

void writeAccount();
void displayAccount(int);
void deleteAccount(int);
void modifyAccount(int);
void displayAll();
void Deposit_Withdraw(int,int);
void TransactionHistory();

void menu()
{

	int num=0;
	int option;

	do
	{
		cout << "===MENU===" << endl;
		cout << "1-Create Account" << endl;
		cout << "2-Deposit" << endl;
		cout << "3-Withdraw" << endl;
		cout << "4-Balance Enquiry" << endl;
		cout << "5-All Accounts" << endl;
		cout << "6-Close Account" << endl;
		cout << "7-Modify Account" << endl;
		cout << "8-Transaction History" << endl;
		cout << "9-Exit" << endl;

		cin >> option;

		switch (option)
		{
		case 1:
			writeAccount();
			break;

		case 2:
			cout << "Enter the Account Number" << endl;
			cin >> num;
			Deposit_Withdraw(num, 1);
			break;

		case 3:


			cout << "Enter the Account Number" << endl;
			cin >> num;
			Deposit_Withdraw(num, 2);
			break;

		case 4:
			cout << "Enter Account Number" << endl;
			cin >> num;
			displayAccount(num);
			break;

		case 5:
			displayAll();
			break;

		case 6:
			cout << "Enter Account Number" << endl;
			cin >> num;
			deleteAccount(num);
			break;

		case 7:
			cout << "Enter Account Number" << endl;
			cin >> num;
			modifyAccount(num);
			break;

		case 8:
			cout << "Transactions History" << endl;
			break;

		case 9:
			cout << "Exiting Program" << endl;
			break;

		default:
			cout << "Enter a valid option" << endl;
			break;
		}


	} while (option != 9);

	
}


int main()
{

	menu();


	/*
	
	int num,option;
	
	do
	{

		

		cout << "---Main Menu---" << endl;
		cout << "1-Create Account" << endl;
		cout << "2-Deposit" << endl;
		cout << "3-Withdraw" << endl;
		cout << "4-Balance Enquiry" << endl;
		cout << "5-All Accounts" << endl;
		cout << "6-Close Account" << endl;
		cout << "7-Modify Account" << endl;
		cout << "8-Exit" << endl;

		cin >> option;

		switch (option)
		{
		case 1:
			writeAccount();
			break;

		case 2:
			cout << "Enter the Account Number" << endl;
			Deposit_Withdraw(num, 1);
			break;

		case 3:
			cout << "Enter the Account Number" << endl;
			Deposit_Withdraw(num, 2);
			break;

		case 4:
			cout << "Enter Account Number" << endl;
			cin >> num;
			displayAccount(num);
			break;

		case 5:
			displayAll();
			break;

		case 6:
			cout << "Enter Account Number"<<endl;
			cin >> num;
			deleteAccount(num);
			break;

		case 7:
			cout << "Enter Account Number" << endl;
			cin >> num;
			modifyAccount(num);
			break;

		case 8:
			cout << "Exiting Program" << endl;
			break;

		default:
			cout << "Enter a valid option" << endl;
			break;
		}


	} while (option!=8);
	*/

}


void writeAccount()
{

	Account ac;
	ofstream ofile;
	ofile.open("account.dat", ios::binary | ios::app);
	cout << "hello" << endl;
	ac.createAccount();
	cout << "hello" << endl;
	ofile.write(reinterpret_cast<char*>(&ac), sizeof(Account));
	ofile.close();


}

void displayAccount(int number)
{
	Account account;

	bool accExists= false;

	ifstream ifile;

	ifile.open("account.dat", ios::binary);

	if (!ifile)
	{
		cout << "File could not be open" << endl;
	}

	else
	{

		cout << "Balance Details" << endl;

		while (ifile.read(reinterpret_cast<char *> (&account), sizeof(Account)))
		{
			if (account.returnAccountNumber() == number)
			{
				account.showAccount();
				accExists = true;
			}
		}

		ifile.close();

		if (accExists == false)
			cout << "Account does not exist" << endl;


	}

}

void deleteAccount(int number)
{
	Account account;

	ifstream ifile;

	ofstream ofile;

	ifile.open("account.dat", ios::binary);

	if (!ifile)
	{
		cout << "File could not be open" << endl; 
		return;
	}
	ofile.open("temp.dat", ios::binary);
	ifile.seekg(0, ios::beg);
	while (ifile.read(reinterpret_cast<char*> (&account), sizeof(Account)))
	{
		if (account.returnAccountNumber() != number)
		{
			ofile.write(reinterpret_cast<char*> (&account), sizeof(Account));
		}
	}

	ifile.close();
	ofile.close();
	remove("account.dat");
	rename("temp.data", "account.dat");
	cout << "Record Deleted" << endl;

}

void modifyAccount(int number)
{
	bool  found = false;

	Account account;

	fstream file;

	file.open("account.dat", ios::binary | ios::in | ios::out);

	if (!file)
	{
		cout << "File could not be open" << endl;
		return;
	}
	while (!file.eof() && found == false)
	{
		file.read(reinterpret_cast<char*>(&account), sizeof(Account));
		if (account.returnAccountNumber() == number)
		{
			account.showAccount();
			cout << "Enter the new details" << endl;
			account.modify();
			int pos = (-1)*static_cast<int>(sizeof(Account));
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char*>(&account), sizeof(Account));
			cout << "Record updated" << endl;
			found = true;
		}
	}

	file.close();
	if (found == false)
		cout << "record not found" << endl;


}

void displayAll()
{
	Account account;

	ifstream ifile;

	ifile.open("account.dat", ios::binary);
	if (!ifile)
	{
		cout << "file could not be read" << endl;
		return;
	}
	else
	{
	

	

		cout << " \n\n\t\tACCOUNT HOLDER LIST \n\n";
		cout << "==============================================\n";
		cout << "ACCOUNT NUMBER          NAME         BALANCE\n";
		cout << "==============================================\n";

		

		while (ifile.read(reinterpret_cast<char*>(&account), sizeof(Account)))
		{
			cin.get();
			account.report();
			cin.get();
		}
		
	}
	ifile.close();
}

void Deposit_Withdraw(int number, int transactionoption)
{
	float amt;

	bool found = false;

	Account act;

	fstream file;

	file.open("account.dat", ios::binary | ios::in | ios::out);
	if (!file)
	{
		cout << "file could not be open" << endl;
		return;
	}

	while (!file.eof() && found == false)
	{
		file.read(reinterpret_cast<char*>(&act), sizeof(Account));
		if (act.returnAccountNumber() == number)
		{
			act.showAccount();
			if (transactionoption == 1)
			{
				cout << "Enter the amount to be deposited" << endl;
				cin >> amt;
				act.Deposit(amt);
				act.transactionType = 'D';
			}


			if (transactionoption== 2)
			{
				cout << "Enter amount to withdraw" << endl;
				cin >> amt;
				float balance = (act.returnBalance() - amt);
				if (act.returnBalance() < amt)
					cout << "Insufficient Balance" << endl;
				else
					act.Withdraw(amt);
				act.transactionType = 'W';
			}

			int pos = (-1)*static_cast<int>(sizeof(Account));
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char*>(&act), sizeof(Account));
			cout << "Record Updated" << endl;
			found = true;
		}
	}

	file.close();
	if (found == false)
		cout << "Record not Found" << endl;

}

void WriteTransactionHistory()
{

}

void DisplayTransactionHistory()
{

}