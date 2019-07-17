#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>


using namespace std;

struct itemList
{
	int item_number;
	string name;
	double price;
};

int main()
{
	ofstream wfile("info.bin", ios::out | ios::binary);

	if (!wfile)
	{
		cout << "Cannot open file" << endl;
		return 1;
	}

	itemList wlists[3];

	wlists[0].item_number = 1;
	wlists[0].name = "Book";
	wlists[0].price = 150.50;

	wlists[1].item_number = 2;
	wlists[1].name = "Pen";
	wlists[1].price = 15.53;

	wlists[2].item_number = 3;
	wlists[2].name = "Pencil";
	wlists[2].price = 10.53;

	for (int i = 0; i < 3; i++)
	{
		wfile.write((char*)&wlists[i], sizeof(itemList));
	}

	wfile.close();

	if (!wfile.good())
	{
		cout << "Error occurred at writing time" << endl;
		return 1;
	}

	ifstream rfile("info.bin", ios::in | ios::binary);

	if (!rfile)
	{
		cout << "Cannot open file" << endl;
		return 1;
	}

	itemList rlists[3];

	for (int i = 0; i < 3; i++)
	{
		rfile.read((char*)&rlists[i], sizeof(itemList));
	}

	rfile.close();

	if (!rfile.good())
	{
		cout << "Error ocurred at reading time" << endl;
		return 1;
	}


	for (int i = 0; i < 3; i++)
	{
		cout << "Item No. :" <<rlists[i].item_number<< endl;
		cout << "Name :" <<rlists[i].name<< endl;
		cout << "Price :" <<rlists[i].price<< endl;
		cout << endl;
	}



}