#include <iostream>
#include <iomanip>

using namespace std;

int main()
{

	
	cout << "hi" << endl;

	cout << hex << 100 << endl;

	cout << setw(10) << setfill('0') << "anil" << endl;


	/*
	cout.precision(4);

	cout << 123.456 << endl;

	cout << 123456 << endl;
	*/


	/*
	bool boolvalue;

	//cin.setf(ios::boolalpha);
	//cout.setf(ios::boolalpha);


	cin >>boolalpha>> boolvalue;
	cout<<boolalpha<< boolvalue;
	*/






	/*
	cout.setf(ios::showpos | ios::showpoint);
	cout.unsetf(ios::showpos);
	auto flag= ios::showbase | ios::showpos | ios::showpoint;
	cout.flags(flag);
	cout << 100.2 << endl;
	cout << -65.3 << endl;
	cout <<89.8 << endl;
	*/
}