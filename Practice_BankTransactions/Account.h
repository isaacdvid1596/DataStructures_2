#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;


class Account
{
public:

	int accountNumber;
	char accountName[50];
	float balance;
	char transactionType = '/0';
	

	Account();
	Account(int accountNumber, char accountName[50],float balance, char transactionType);
	~Account();

	void createAccount();
	void showAccount();
	void modify();
	void Deposit(float);
	void Withdraw(float);
	void report() const;
	int returnAccountNumber();
	float returnBalance() const;
	char returnTransaction();
	
	
};

