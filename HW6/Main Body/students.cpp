/*Name: Michael Bryan
 Date : April 4, 2019
 Section : 1
 Assignment : HW #6
 Due Date : April 10, 2019 */

//-------------------------students.cpp--------------------
#include "students.h"

Student::Student(string fName, string lName, int courseNum) : course(courseNum)
{
    firstName = fName;
    lastName = lName;
}

Student::Student(const Student& stu) : course(stu.course)
{
    firstName = stu.firstName;
    lastName = stu.lastName;
}

Student& Student::operator=(const Student& stu)
{
    firstName = stu.firstName;
    lastName = stu.lastName;
    
    return *this;
}

void Student::setfName(string fName)
{
    firstName = fName;
}

void Student::setlName(string lName)
{
    lastName = lName;
}

string Student::getfName()
{
    return firstName;
}

string Student::getlName()
{
    return lastName;
}

int Student::getCourse()
{
    return course;
}

EnglishStud::EnglishStud(string fName, string lName, int courseN, int aGrade, int pGrade, int mtGrade, int feGrade) : Student(fName, lName, courseN)
{
    attendanceGrade = aGrade;
    projectGrade = pGrade;
    midtermGrade = mtGrade;
    finalexamGrade = feGrade;
    this->computefinalGrade();
}
double EnglishStud::computefinalGrade()
{
    finalAvg = ((attendanceGrade*.1)+(projectGrade*.3)+(midtermGrade*.3)+(finalexamGrade*.3));
    return finalAvg;
}

double EnglishStud::getfinalAvg() const
{
    return finalAvg;
}

int EnglishStud::getfinalExam() const
{
    return finalexamGrade;
}

HistoryStud::HistoryStud(string fName, string lName, int courseN, int tpGrade, int mtGrade, int feGrade) : Student(fName, lName, courseN)
{
    termpaperGrade = tpGrade;
    midtermGrade = mtGrade;
    finalexamGrade = feGrade;
    this->computefinalGrade();
}
double HistoryStud::computefinalGrade()
{
    finalAvg = ((termpaperGrade*.25)+(midtermGrade*.35)+(finalexamGrade*.4));
    return finalAvg;
}

double HistoryStud::getfinalAvg() const
{
    return finalAvg;
}

int HistoryStud::getfinalExam() const
{
    return finalexamGrade;
}

MathStud::MathStud(string fName, string lName, int courseN, int q1, int q2, int q3, int q4, int q5, int t1, int t2, int feGrade) : Student(fName, lName, courseN)
{
    quiz1 = q1;
    quiz2 = q2;
    quiz3 = q3;
    quiz4 = q4;
    quiz5 = q5;
    test1 = t1;
    test2 = t2;
    finalexamGrade = feGrade;
    this->computefinalGrade();
}

double MathStud::computefinalGrade()
{
    quizAvg = (quiz1+quiz2+quiz3+quiz4+quiz5)/5;
    finalAvg = ((quizAvg*.15)+(test1*.25)+(test2*.25)+(finalexamGrade*.35));
    return finalAvg;
}

double MathStud::getfinalAvg() const
{
    return finalAvg;
}

int MathStud::getfinalExam() const
{
    return finalexamGrade;
}
