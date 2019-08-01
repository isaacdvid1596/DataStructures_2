#include <iostream>
#include <fstream>
#include <string.h>

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
    void modify();

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
    std::cout<<"Rollno: "<<rollno<<"\t Name : "<<name<<"\n";
    std::cout<<"Marks : "<<marks<<" \tGrade : "<<grade<<"\n";
}

int student::getrno()
{
    return rollno;
}


void student::modify()
{
    std::cout<<"rollno: "<<rollno<<"\n";
    std::cout<<"name: "<<name<<" /t Branch: "<<branch<<" \t Marks : "<<marks<<" /n";
    std::cout<<"enter new details \n";
    
    char nam[20]=" ",br[3]=" ";
    float mks;
    std::cout<<"new name : (Enter '.' to retain old one): ";
    std::cin>>nam;
    std::cout<<"new branch :(Press '.' to retain old one): ";
    std::cin>>br;
    std::cout<<"new marks : (Press -1 to retain old one : ";
    std::cin>>mks;

    if(strcmp(nam,".")!=0)
    {
        strcpy(name,nam);
    }
    if(strcmp(br, ".")!=0)
    {
        strcpy(branch,br);
    }

    if(mks != -1)
    {
        marks = mks;
        if(marks >=75)
        {
            grade ='A';
        }
        else if(marks>=60)
        {
            grade ='B';
        }
        else if(marks>=50)
        {
            grade = 'C';
        }
        else if(marks>=40)
        {
            grade ='D';
        }
        else
        {
            grade = 'F';
        }
        
    }


    int main()
    {

        
        student stud1 , stud;

        std::fstream fio("marks.dat",std::ios::in|std::ios::out);
        char ans='y';

        while(ans=='y'||ans=='Y')
        {
            stud1.getdata();
            fio.write(reinterpret_cast<char*>(&stud1),sizeof(stud1));
            std::cout<<"record added to the file \n";
            std::cout<<"want to enter more (y/n)";
            std::cin>>ans;
        }

        int rno;
        long pos;
        char found ='f';

        std::cout<<"enter rollno of student whose record is to be modified : ";
        std::cin>>rno;

        fio.seekg(0);
        
        while(!fio.eof())
        {
            pos = fio.tellg(); //give pos the current reading pointer position
            fio.read(reinterpret_cast<char*>(&stud1),sizeof(stud1));

            if(stud1.getrno()==rno)
            {
                stud1.modify();
                fio.seekg(pos);
                fio.write(reinterpret_cast<char*>(&stud1),sizeof(stud1));
                found ='t';
                break;
            }
        }

        if(found=='f')
        {
            std::cout<<"record not found in the file \n";
            std::cout<<"press any key to exit \n";
        }

        fio.seekg(0);
        std::cout<<"now the file contains : \n";
        while(!fio.eof())
        {
            fio.read(reinterpret_cast<char*>(&stud),sizeof(stud));
            stud.putdata();
        }

        fio.close();







    }













}

int main()
{

student stud1,stud;
    

std::cout<<"rollno: "<<stud1.


}