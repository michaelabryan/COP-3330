/*Name: Michael Bryan
 Date : April 4, 2019
 Section : 1
 Assignment : HW #6
 Due Date : April 10, 2019 */

//-------------------------studentlist.cpp--------------------
#include "studentlist.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

StudentList::StudentList()
{
    list = nullptr;
    currentListSize = 0;
}

StudentList::~StudentList()
{
        delete [] list;
}

bool StudentList::ImportFile(const char* filename)
{
    ifstream fileIn;
    fileIn.open(filename);
    if(!fileIn)
        return false;
    else
    {
        int studentsonFile;
        fileIn >> studentsonFile;
        
        string fName, lName, course;
        currentListSize += studentsonFile;
        this->GrowArray(currentListSize);
        for(int i = currentListSize-studentsonFile; i < currentListSize; i++)
        {
            fileIn.ignore(1,'\n');
            getline(fileIn, lName, ',');
            fileIn.ignore(1,' ');
            getline(fileIn, fName, '\n');
            fileIn >> course;
            if(course == "English")
            {
                int atten, proj, midterm, finalexam;
                fileIn >> atten >> proj >> midterm >> finalexam;
                list[i] = new EnglishStud(fName,lName, 0, atten, proj, midterm, finalexam);
            }
            else if(course == "History")
            {
                int termpap, midterm, finalexam;
                fileIn >> termpap >> midterm >> finalexam;
                list[i] = new HistoryStud(fName,lName, 1, termpap,midterm,finalexam);
            }
            else if (course == "Math")
            {
                int q1, q2, q3, q4, q5, test1, test2, finalexam;
                fileIn >> q1 >> q2 >> q3 >> q4 >> q5 >> test1 >> test2 >> finalexam;
                list[i] = new MathStud(fName,lName,2,q1,q2,q3,q4,q5,test1,test2,finalexam);
            }
        }
        return true;
    }
}

bool StudentList::CreateReportFile(const char* filename)
{
    ofstream fileOut;
    int Acount, Bcount, Ccount, Dcount, Fcount;
    Acount = Bcount = Ccount = Dcount = Fcount = 0;
    
    fileOut.open(filename);
    if(!fileOut)
        return false;
    else
    {
        fileOut << "Student Grade Summary\n";
        fileOut << "---------------------\n\n";
        
        //English grade printout
        fileOut << "English Class\n\n";
        stuHeader(fileOut);
        printStuInfo(fileOut, list, 0);
        
        //History grade printout
        fileOut << "History Class\n\n";
        stuHeader(fileOut);
        printStuInfo(fileOut, list, 1);
        
        //Math grade printout
        fileOut << "Math Class\n\n";
        stuHeader(fileOut);
        printStuInfo(fileOut, list, 2);
        
        //Stores number of A's, B's, C's, D's, and F's
        for(int i = 0; i < currentListSize; i++)
        {
            if(list[i]->getfinalAvg() >= 90)
                Acount += 1;
            if(list[i]->getfinalAvg() <= 89.99 && list[i]->getfinalAvg() >= 80)
                Bcount += 1;
            if(list[i]->getfinalAvg() <= 79.99 && list[i]->getfinalAvg() >= 70)
                Ccount += 1;
            if(list[i]->getfinalAvg() <= 69.99 && list[i]->getfinalAvg() >= 60)
                Dcount += 1;
            if(list[i]->getfinalAvg() <= 59.99)
                Fcount += 1;
        }
        
        //Prints count of A's, B's, C's, D's, and F's
        fileOut << "OVERALL GRADE DISTRIBUTION\n\nA:\t" << Acount << '\n';
        fileOut << "B:\t" << Bcount << '\n';
        fileOut << "C:\t" << Ccount << '\n';
        fileOut << "D:\t" << Dcount << '\n';
        fileOut << "F:\t" << Fcount << '\n';
        
        return true;
    }
}

void StudentList::ShowList() const
{
    cout.setf(ios::left);
    cout.width(20);
    cout << "Last Name";
    cout.width(20);
    cout << "First Name";
    cout.width(7);
    cout << "Course\n";
    cout.width(47);
    cout << "-----------------------------------------------\n";
    
    for(int i = 0; i<currentListSize; i++)
    {
        cout.width(20);
        cout << list[i]->getlName();
        cout.width(20);
        cout << list[i]->getfName();
        cout.width(7);
        if(list[i]->getCourse() == 0)
            cout << "English" << endl;
        if(list[i]->getCourse() == 1)
            cout << "History" << endl;
        if(list[i]->getCourse() == 2)
            cout << "Math" << endl;
        if(i == currentListSize-1)
            cout << endl;
    }
}

void StudentList::GrowArray(int sizetoGrow)
{
    if(list == nullptr)
    {
        list = new Student*[sizetoGrow];
        currentListSize = sizetoGrow;
    }
    else
    {
        Student ** temp = new Student*[currentListSize+sizetoGrow];
        for(int i = 0; i < currentListSize+sizetoGrow; i++)
            temp[i] = list[i];
        delete [] list;
        list = temp;
    }
        
}

ofstream& StudentList::stuHeader(ofstream& out) const
{
    out.setf(ios::left);
    out << setw(40) << "Student";
    out << setw(6) << "Final";
    out << setw(8) << "Final";
    out << setw(6) << "Letter\n";
    out << setw(40) << "Name";
    out << setw(6) << "Exam";
    out << setw(8) << "Avg";
    out << setw(6) << "Grade\n";
    out << "----------------------------------------------------------------------\n";
    return out;
}

ofstream& StudentList::printStuInfo(ofstream& out, Student ** array, int courseNum) const
{
    string namesTogether;
    out.setf(ios::left);
    for(int i = 0; i < currentListSize; i++)
    {
        if(list[i]->getCourse() == courseNum)
        {
            namesTogether = list[i]->getfName() + ' ' + list[i]->getlName();
            
            out << setw(40) << namesTogether << setw(6) << list[i]->getfinalExam();
            out.setf(ios::fixed);
            out << setprecision(2) << setw(8) << list[i]->getfinalAvg();
            
            if(list[i]->getfinalAvg() >= 90)
                out << setw(6) << "A" << endl;
            if(list[i]->getfinalAvg() <= 89.99 && list[i]->getfinalAvg() >= 80)
                out << setw(6) << "B" << endl;
            if(list[i]->getfinalAvg() <= 79.99 && list[i]->getfinalAvg() >= 70)
                out << setw(6) << "C" << endl;
            if(list[i]->getfinalAvg() <= 69.99 && list[i]->getfinalAvg() >= 60)
                out << setw(6) << "D" << endl;
            if(list[i]->getfinalAvg() <= 59.99)
                out << setw(6) << "F" << endl;
        }
        if(i == currentListSize-1)
            out << '\n';
    }
    return out;
}
