#include <iostream>

using namespace std;

int main()
{
	char a = 75;
	char b = 8;
	char resultado=0;

	cout << "a : " << int(a) << " b : " << int(b) << endl;

	if (a & b)
		cout << "el cuarto bit es 1" << endl;
	else
		cout << "el cuarto bit es 0" << endl;




}