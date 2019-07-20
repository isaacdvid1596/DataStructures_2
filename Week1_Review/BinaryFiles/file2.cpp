#include <iostream>
#include <string>

using namespace std;

int main()
{
	string data("learning isaac");

	cout << data << endl;

	data.append(" rocks ");

	cout << data << endl;


	cout << data.size() << endl;


	data.insert(0, "The ");
	

	cout << data << endl;

	cout << data.substr(4) << endl;

	data.erase(1,4);
	cout << data << endl;

}