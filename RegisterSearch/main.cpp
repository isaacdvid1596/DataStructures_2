#include <iostream>
#include "FileRegister.h"
#include "CounterClock.h"


using namespace std;

int main()
{

	FileRegister fg;
	CounterClock cc;

	int option;


	do 
	{
		cout << "MENU" << endl;
		cout << "1-Create Register" << endl;
		cout << "2-Linear Search" << endl;
		cout << "3-Binary Search" << endl;
		cout << "4-Exit" << endl;
		cin >> option;

		switch (option)
		{
		case 1:
			fg.createRegister();
			break;
		case 2:
			char name[30];
			cout << "Linear Search" << endl;
			cout << "Name :" << endl;
			cin >> name;
			cc.startCounter();
			fg.SSearch(name);
			cc.endCounter();

			cout << "Elapsed Time : " << cc.printTimeCounter() << endl;
			break;

		case 3:

			char nameB[30];
			cout << "Binary Search" << endl;
			cout << "Name : " << endl;
			cin >> nameB;
			cc.startCounter();
			int flag = fg.BSearch(nameB, 0, 20999);
			cc.endCounter();
			cout << "Elapsed time : " << cc.printTimeCounter() << endl;

			break;
		}


	} while (option != 4);

}
