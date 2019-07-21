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
	

	Account();
	Account(int accountNumber, char accountName[50],float balance);
	~Account();

	void createAccount();
	void showAccount();
	void modify();
	void Deposit(float);
	void Withdraw(float);
	void report() const;
	int returnAccountNumber();
	float returnBalance() const;
	
};

