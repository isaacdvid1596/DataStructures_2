#include "Account.h"



Account::Account()
{
	strcpy_s(accountName, "name");
	accountNumber = 0;
	balance = 0.00;
	
}

Account::Account(int accountNumber, char accountName[50], float balance)
{
	strcpy_s(this->accountName, accountName);
	this->accountNumber = accountNumber;
	this->balance = balance;
	
}


Account::~Account()
{

}

void Account::createAccount()
{
	cout << "Enter the Account Number" << endl;
	cin >> accountNumber;
	cout << "Enter the name of the Account Holder" << endl;
	cin.ignore();
	cin.getline(accountName, 50);
	cout << "Enter the current Balance on the account" << endl;
	cin >> balance;

	cout << "Account succesfully created" << endl;
}

void Account::showAccount()
{
	cout << "Account Number : " << accountNumber << endl;
	cout << "Account Holder Name : " << accountName << endl;
	cout << "Balance Amount : " << balance << endl;
}

void Account::modify()
{
	cout << "Modify the fields" << endl;

	cout << "Modify Account Number : " << endl;
	cin.ignore();
	cin.getline(accountName, 50);
	cout << "Modify Account Balance" << endl;
	cin >> balance;
}


void Account::Deposit(float depositAmount)
{
	balance = balance + depositAmount;
}

void Account::Withdraw(float withdrawAmount)
{
	balance = balance - withdrawAmount;
}

void Account::report() const
{
	cout << accountNumber << setw(10) << " " << accountName << " " << setw(10) << balance << endl;
}

int Account::returnAccountNumber()
{
	return accountNumber;

}

int Account::returnBalance() const
{
	return balance;
}

