#include <iostream>


using namespace std;


int getWhatTheyWant();


int main()
{

	int whatTheyWant;

	whatTheyWant = getWhatTheyWant();

	while (whatTheyWant != 4)
	{
		whatTheyWant = getWhatTheyWant();
	}

}

int getWhatTheyWant()
{
	int choice;

	cout << "1-just plain items" << endl;
	cout << "2-helpful items" << endl;
	cout << "3-harmful items" << endl;
	cout << "4-quit program" << endl;

	cin >> choice;

	return choice;

}