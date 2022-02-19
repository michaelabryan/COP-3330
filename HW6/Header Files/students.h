/*Name: Michael Bryan
 Date : April 4, 2019
 Section : 1
 Assignment : HW #6
 Due Date : April 10, 2019 */

//-------------------------students.h--------------------
#include <string>
#pragma once
using namespace std;

class Student
{
public:
    //Numerical representation of course
    static const int ENGLISH = 0;
    static const int HISTORY = 1;
    static const int MATH = 2;
    
    //Constructors to initialize data
    Student(string fName, string lName, int courseNum);
    Student(const Student& stu);
    Student& operator=(const Student& stu);
    
    //Mutators
    void setfName(string fName);
    void setlName(string lName);
    
    //Accessors
    string getfName();
    string getlName();
    int getCourse();
    
    //Pure virtual functions since there is not enough data to get grades
    virtual double computefinalGrade()=0;
    virtual double getfinalAvg()=0;
    virtual int getfinalExam()=0;
    
protected:
    string firstName;
    string lastName;
    const int course;
    
private:
    
};

class EnglishStud : public Student
{
public:
    EnglishStud(string fName, string lName, int courseN, int aGrade, int pGrade, int mtGrade, int feGrade);
    double computefinalGrade();
    double getfinalAvg() const;
    int getfinalExam() const;
    
private:
    double finalAvg; //Determined in the "computefinalGrade" function
    
    //Initialized data from input files
    int attendanceGrade;
    int projectGrade;
    int midtermGrade;
    int finalexamGrade;
    
};

class HistoryStud : public Student
{
public:
    HistoryStud(string fName, string lName, int courseN, int tpGrade, int mtGrade, int feGrade);
    double computefinalGrade();
    double getfinalAvg() const;
    int getfinalExam() const;
    
private:
    double finalAvg; //Determined in the "computefinalGrade" function
    
    //Initialized data from input file
    int termpaperGrade;
    int midtermGrade;
    int finalexamGrade;
};

class MathStud : public Student
{
public:
    MathStud(string fName, string lName, int courseN, int q1, int q2, int q3, int q4, int q5, int t1, int t2, int feGrade);
    double computefinalGrade();
    double getfinalAvg() const;
    int getfinalExam() const;
    
private:
    double finalAvg; //Determined in the "computefinalGrade" function
    
    //Initialized data from input file
    int quiz1, quiz2, quiz3, quiz4, quiz5;
    double quizAvg;
    int test1, test2;
    int finalexamGrade;
};
