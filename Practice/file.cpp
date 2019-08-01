#include <iostream>
#include <fstream>
#include <stdlib.h>

class student
{

int rollno;
char name[20];
char branch[3];
float marks;
char grade;

public:
void getdata();
void putdata();
int getrno();


};

void student::getdata()
{
    std::cout<<"Rollno: ";
			std::cin>>rollno;
			std::cout<<"Name: ";
			std::cin>>name;
			std::cout<<"Branch: ";
			std::cin>>branch;
			std::cout<<"Marks: ";
			std::cin>>marks;

			if(marks>=75)
			{
				grade = 'A';
			}
			else if(marks>=60)
			{
				grade = 'B';
			}
			else if(marks>=50)
			{
				grade = 'C';
			}
			else if(marks>=40)
			{
				grade = 'D';
			}
			else
			{
				grade = 'F';
			}
}

void student::putdata()
{
    std::cout<<name<<", rollno "<<rollno<<" has "<<marks<<"% marks and "<<grade<<" grade."<<"\n";
}

int student::getrno()
{
    return rollno;
}


int main()
{

    student stud1;

    std::ofstream fout("marks.dat",std::ios::out);

    char ans = 'y';

    while(ans=='y'||ans=='Y')
    {
        stud1.getdata();
        fout.write(reinterpret_cast<char*>(&stud1),sizeof(stud1));
        std::cout<<"record added to the file \n";
        std::cout<<"\n want to enter more (y/n)";
        std::cin>>ans;

    }

    fout.close();

    int rno;
    char found;
    std::ifstream fin("marks.dat",std::ios::in);

    if(!fin)
    {
        std::cout<<"error in opening file \n";
        std::cout<<"press any key to exit \n";
        
    }

    ans='y';


    while(ans=='y'||ans=='Y')
    {
        found = 'n';
        std::cout<<"enter rollno to be searched for : \n";
        std::cin>>rno;

        while(!fin.eof())
        {

            

            fin.read(reinterpret_cast<char*>(&stud1),sizeof(stud1));
            if(stud1.getrno()==rno)
            {
                stud1.putdata();
                found == 'y';
                break;      
            }


        }


            if(found =='n')
            {
                std::cout<<"rollno not found in the file \n\n";
                std::cout<<"press any key to exit...\n";
            }


            std::cout<<"want to search more? (y/n)";
            std::cin>>ans;

    }

    fin.close();





}
