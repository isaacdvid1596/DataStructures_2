#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
	char a = 105;

	char resultado = 0;

	cout<<"a:" << int(a) << endl;

	resultado = a << 1;



	cout << "resultado : "<< unsigned int (resultado) << endl;

	printf("resultado =  %d", a);


	resultado = a << 2;

	cout << "resultado : " << (resultado) << endl;

}