#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

struct avlnode
{
	int key;
	int height;
	int position;
	avlnode* left;
	avlnode* right;
	avlnode* root;

	avlnode()
	{
		key = 0;
		height = 0;
		position = 0;
		left = NULL;
		right = NULL;
		root = NULL;
	}
};

struct avlnodefile
{
	int leftson;
	int rightson;
	int key;
};

avlnode* root = NULL;


void menu();
avlnode* createNode(int key);
void insertNode(avlnode*&, int key);
int height(avlnode*&);
void updateheight(avlnode*&);
void balance(avlnode*&);
void simplerotation(avlnode*&, bool);
void doublerotation(avlnode*&, bool);
bool search(avlnode*&, int);

avlnode* returnleft(avlnode*); //returns left subtree
avlnode* returnright(avlnode*);//returns right subtree

//deletion
int findgreatest(avlnode*&);
int findsmallest(avlnode*&);
void deletion(avlnode*&, int);

//file
void saveTree(avlnode*&);
int pos(avlnode*&);
void updateindex(avlnode*&);
void displayfile();


//print
void preorder(avlnode*&);
void inorder(avlnode*&);
void postorder(avlnode*&);


int main()
{

	menu();


}


void menu()
{
	int option = 0;
	int value = 0, value1 = 0, data = 0, counter = 0, valuex = 0;
	int a = 0, x = 0;

	do
	{

		cout << "Menu" << endl;
		cout << "1-Insert Node" << endl;
		cout << "2-Delete Node" << endl;
		cout << "3-Search Node" << endl;
		cout << "4-Print Tree" << endl;
		cout << "5-Display File" << endl;
		cout << "6-Exit" << endl;
		cin >> option;


		switch (option)
		{
		case 1:
			cout << "Enter node to be inserted" << endl;
			cin >> value;
			insertNode(root, value);
			cout << "node inserted" << endl;
			break;
			 
		case 2:
			cout << "Enter node to be deleted" << endl;
			cin >> x;
			deletion(root, x);
			break;

		case 3:
			cout << "Enter number to be found" << endl;
			cin >> data;
			if (search(root, data) == true)
			{
				cout << "element " << data << " found" << endl;
			}
			else
				cout << "cannot be found" << endl;
			break;
			
		case 4:
			cout << "Printing options" << endl;
			cout << "1-Preorder" << endl;
			cout << "2-InOrder" << endl;
			cout << "3-Postorder" << endl;
			cin >> value1;

			switch (value1)
			{
			case 1:
				cout << "printing in preorder" << endl;
				preorder(root);
				cout << endl;
				break;
			case 2:
				cout << "printing inorder" << endl;
				inorder(root);
				cout << endl;
				break;
			case 3:
				cout << "printing postorder" << endl;
				postorder(root);
				cout << endl;
				break;
			}
			break;

		case 5:
			cout << endl;
			displayfile();
			cout << endl;
			break;

		case 6:
			cout << "exiting program" << endl;
			break;

		default:
			cout << "incorrect option" << endl;
			break;
		}



	} while (option != 6);



}

avlnode* createNode(int key)
{
	avlnode* newnode = new avlnode();

	newnode->key = key;
	newnode->right = NULL;
	newnode->left = NULL;
	newnode->height = 0;

	saveTree(newnode);
	return newnode;
}

void insertNode(avlnode*& node, int key)
{
	if (node == NULL)
	{
		avlnode* newnode = createNode(key);
		node = newnode;
		updateheight(node);
		saveTree(node);
	}
	else
	{
		int rookey = node->key;

		if (key < rookey)
		{
			insertNode(node->left, key);
		}
		else
		{
			insertNode(node->right, key);
		}

		updateheight(node);
		balance(node);

	}
}

int height(avlnode*&node)
{
	if (node == NULL) //if node points to null then return -1
	{
		return -1;
	}
	else
	{
		return node->height; //return node height;
	}
}

void updateheight(avlnode*&node)
{
	if (!node==NULL)
	{
		node->height = std::max(height((node)->left), height((node->right))+1);
	}
}

void balance(avlnode*&node)
{
	if (!node == NULL)
	{

		int heightn = height(node->left) - height(node->right);

		if (heightn == 2)
		{
			if (height((node)->left->left) >= height((node)->left->right))
			{
				simplerotation(node, true);
			}
			else
			{
				doublerotation(node, true);
			}
		}
		else if (heightn == -2)
		{
			if (height((node)->right->right) >= height((node)->right->left))
			{
				simplerotation(node, false);
			}
			else
			{
				doublerotation(node, false);
			}
		}

		//int heightn = height(node->left) - height(node->right);
	}
}

void simplerotation(avlnode*&node,bool left)
{
	avlnode* temp;
	if (left) //rotacion a derecha   //rotacion izq
	{
		temp = returnleft(node);
		node->left = returnright(temp);
		temp->right = node;
	}
	else //rotacion a izq  //rotacion der
	{
		temp = returnright (node);
		node->right = returnleft(temp);
		temp->left = node;
	}
}

void doublerotation(avlnode*&node, bool left)
{
	if (left)
	{
		simplerotation((node)->left, false);  
		simplerotation(node, true);
	}
	else
	{
		simplerotation((node)->right, true);
		simplerotation(node, false);
	}
}

bool search(avlnode*&node,int key)
{
	if (node == NULL)
	{
		return false;
	}
	else if (node->key == key)
	{
		return true;
	}
	else if (key < node->key)
	{
		return search(node->left, key);
	}
	else
	{
		return search(node->right, key);
	}
}

avlnode* returnleft(avlnode*node)
{
	if (node == NULL)
	{
		return nullptr;
	}
	else
	{
		return node->left;
	}
}

avlnode* returnright(avlnode*node)
{
	if (node == NULL)
	{
		return nullptr;
	}
	else
	{
		return node->right;
	}
}

//deletion
int findgreatest(avlnode*&node)
{
	int key;

	if (node->right == NULL)
	{
		key = node->key;
		node = node->left;
		return key;
	}
	else
	{
		key = findgreatest(node->right);
		return key;
	}

}

int findsmallest(avlnode*&node)
{
	int key;
	if (node->left == NULL)
	{
		key = node->key;
		node = node->right;
		return key;
	}
	else
	{
		key = findsmallest(node->left);
		return key;
	}
}

void deletion(avlnode*&node, int key)
{
	avlnode* temp;

	if (node == NULL)
	{
		cout << "item not found" << endl;
	}
	else if (key < node->key)
	{
		deletion(node->left, key);
	}
	else if (key > node->key)
	{
		deletion(node->right, key);
	}
	else if ((node->left == NULL) && (node->right == NULL))
	{
		temp = node;
		free(temp);
		node == NULL;
		cout << "successfully deleted" << endl;
	}
	else if (node->left == NULL)
	{
		temp = node;
		free(temp);
		node = node->right;
		cout << "successfully  deleted" << endl;
	}
	else if (node->right== NULL)
	{
		temp = node;
		node = node->left;
		free(temp);
		cout << "successfully deleted" << endl;
	}
	else
	{
		int x = 0;
		bool active = true;

		do
		{

			cout << "which method do you want to delete this node with ?" << endl;
			cout << "1-Succesor" << endl;
			cout << "2-Predecessor" << endl;
			cin >> x;
			switch (x)
			{
			case 1:
				//succesor
				node->key = findsmallest(node->right);
				active = false;
				break;
			case 2:
				//predecessor
				node->key = findgreatest(node->left);
				active = false;
				break;
			default:
				cout << "invalid option" << endl;
				active = false;
				break;
			}


		} while (active);

	}

}


//print
void preorder(avlnode*&node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		cout << node->key << endl;
		preorder(node->left);
		preorder(node->right);
	}
}

void inorder(avlnode*&node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		inorder(node->left);
		cout << node->key << endl;
		inorder(node->right);
	}
}

void postorder(avlnode*&node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
		postorder(node->left);
		postorder(node->right);  
		cout << node->key << endl;
	}
}

void saveTree(avlnode*&node)
{
	ofstream avlfile("avlfile.dat", ios::in | ios::app | ios::binary);

	if (!avlfile)
	{
		cout << "cannot open file" << endl;
		return;
	}

	avlnodefile newavl;

	avlfile.seekp(0, ios::end);

	newavl.rightson= -1;
	newavl.leftson= -1;
	newavl.key = node->key;
	node->position = pos(node);
	avlfile.write(reinterpret_cast<char*>(&newavl), sizeof(avlnodefile));
	avlfile.close();
}

int pos(avlnode*& node)
{
	int num = -1;
	avlnodefile newavl;

	ifstream avlfile("avlfile.dat", ios::in | ios::binary);

	if (!avlfile)
	{
		cout << "cannot open file" << endl;
		return -1;
	}

	do
	{

		avlfile.read(reinterpret_cast<char*>(&newavl), sizeof(avlnodefile));
		num++;

	} while (!avlfile.eof());


	return num;
}

void displayfile()
{
	avlnodefile read;


	ifstream iavlfile("avlfile.dat", ios::in | ios::binary);

	if (!iavlfile)
	{
		cout << "cannot open file" << endl;
	}

	do
	{
		iavlfile.read(reinterpret_cast<char*>(&read), sizeof(avlnodefile));

		cout << "value : " << read.key << endl;
		cout << "left son : " << read.leftson << endl;
		cout << "right son : " << read.rightson << endl;


	} while (!iavlfile.eof());
}


void updateindex(avlnode*&node)
{
	if (node != NULL)
	{
		avlnodefile newavl, saveavl;

		fstream avlfile("avlfile.dat", ios::in | ios::out | ios::app | ios::binary);

		if (!avlfile)
		{
			cout << "cannot open file" << endl;
		}

		avlfile.seekg(0);

		do
		{

			avlfile.read(reinterpret_cast<char*>(&newavl), sizeof(avlnodefile));

			if (newavl.key == node->key)
			{
				if (node->right != NULL && node->left != NULL)
				{
					saveavl.rightson = node->right->position;
					saveavl.leftson = node->left->position;
					saveavl.key = node->key;
					avlfile.seekp(node->position * sizeof(avlnodefile));
					avlfile.write(reinterpret_cast<char*>(&saveavl), sizeof(avlnodefile));
					updateindex(node->left);
					updateindex(node->right);
					avlfile.close();
				}
				else if (node->right == NULL && node->left != NULL)
				{
					saveavl.rightson = -1;
					saveavl.leftson = node->left->position;
					saveavl.key = node->key;
					avlfile.seekp(node->position * sizeof(avlnodefile));
					avlfile.write(reinterpret_cast<char*>(&saveavl), sizeof(avlnodefile));
					updateindex(node->left);
					updateindex(node->right);
					avlfile.close();
				}
				else if (node->right != NULL && node->left == NULL)
				{
					saveavl.rightson = node->right->position;
					saveavl.leftson = -1;
					saveavl.key = node->key;
					avlfile.seekp(node->position * sizeof(avlnodefile));
					avlfile.write(reinterpret_cast<char*>(&saveavl), sizeof(avlnodefile));
					updateindex(node->left);
					updateindex(node->right);
					avlfile.close();
				}
				else if (node->right == NULL && node->left == NULL)
				{
					saveavl.rightson = -1;
					saveavl.leftson = -1;
					saveavl.key = node->key;
					avlfile.seekp(node->position * sizeof(avlnodefile));
					avlfile.write(reinterpret_cast<char*>(&saveavl), sizeof(avlnodefile));
					updateindex(node->left);
					updateindex(node->right);
					avlfile.close();
				}
			}


		} while (!avlfile.eof());



	}
}