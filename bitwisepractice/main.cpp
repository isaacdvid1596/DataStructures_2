#include <iostream>


using namespace std;

int main()
{
	char a = 23;
	char b = 90;
	char resultado;
	char resultado2;

	cout << "a : " << int(a) << " b: " << int(b) << endl;

	resultado = a & b;

	cout << resultado;


	cout << endl;

	cout << int(resultado) << endl;
	cout << int(a) << endl;
	cout << int(b) << endl;


	cout << "operacion or " << endl;

	resultado2 = a ^ b;

	cout << int(resultado2) << endl;




}