/*Name: Michael Bryan
 Date : February 5, 2019
 Section : 1
 Assignment : HW #2
 Due Date : February 7, 2019 */

//-------------------------date.cpp--------------------
#include "date.h"
#include <iostream>
using namespace std;

Date::Date()
{
    Set(1, 1, 2000);
}

Date::Date(int m, int d, int y)
{
   if(Set(m, d, y) == true)
   {
       Set(m,d,y);
   }
   else
   {
       Set(1,1,2000);
   }
}

string MonthNamer(int m) //Returns Month name
{
    if (m==1)
        return "Jan";
    if (m==2)
        return "Feb";
    if (m==3)
        return "Mar";
    if (m==4)
        return "Apr";
    if (m==5)
        return "May";
    if (m==6)
        return "June";
    if (m==7)
        return "July";
    if (m==8)
        return "Aug";
    if (m==9)
        return "Sept";
    if (m==10)
        return "Oct";
    if (m==11)
        return "Nov";
    if (m==12)
        return "Dec";
    return 0;
}

int Date::Compare (const Date& d) const
{
    if(GetYear() > d.GetYear())
        return 1;
    else if(GetYear() < d.GetYear())
        return -1;
    else
    {
        if(GetMonth() > d.GetMonth())
        {
	    return 1;
        }
        else if(GetMonth() < d.GetMonth())
            return -1;
	else
	{
            if(GetDay() > d.GetDay())
                return 1;
            else if(GetDay() < d.GetDay())
                return -1;
            else
                return 0;	    
	}
    }
    
    return 0;
}

int Date::GetDay() const
{
    return day;
}

int Date::GetMonth() const
{
    return month;
}

int Date::GetYear() const
{
    return year;
}

void Date::Input()
{
    
    bool Flag;
    
    
    do
    {
        Flag = false;
        char divSign;
        cout << "Please enter a date (Month/Day/Year): ";
        cin >> month >> divSign >> day >> divSign >> year;
        if (month < 1 || month > 12 || month%1 != 0) //Will cause flag to be true if month does not enter a month 1-12 or whole integer.
        {
            cout << "Invalid month entered. Try Again.\n";
            Flag = true;
            if (properDay(month, day, year) == false)
            {
                if (month > 12 || month < 1 || month%1 != 0)
                {
                    cout << "Cannot verify proper Day entered. Try Again.\n";
                    Flag = true;
                }
                else
                    cout << "Invalid day entered. Try Again.\n";
            }
            if (year < 0 || year %1 != 0)
                cout << "Invalid year entered. Try Again.\n";
        }
        else if(properDay(month, day, year) == false)
        {
            cout << "Invalid day entered. Try Again.\n";
            if (year < 0 || year %1 != 0)
                cout << "Invalid year entered. Try Again.\n";
            Flag = true;
        }
        else if(year < 0 || year %1 != 0)
        {
            cout << "Invalid year entered. Try Again.\n";
            Flag = true;
        }
        else
        {
            Set(month, day, year);
            Flag = false;
        }
    }while(Flag == true);
        
}

void Date::Show() const
{
    if(formatChar == 'D')
    {
        cout << GetMonth() << "/" << GetDay() << "/" << GetYear() << '\n';
    }
    if(formatChar == 'T') //Two-Digit char, accounts for all years > 0
    {
        if(month < 10)
            cout << '0';
        cout << month << "/";
        if (day < 10)
            cout << '0';
        cout << day << "/";
        if (year < 10)
            cout << '0' << year%100 << '\n';
        if(year >= 10)
        {
            if(year%100 <=10)
                cout << '0';
            cout << year%100 << '\n';
        }
    }
    if(formatChar == 'L')
    {
        cout << MonthNamer(month) << ' ' << GetDay() << ", " << GetYear() << '\n';
    }
    if(formatChar == 'J')
    {
        if (year < 10)
        {
            cout << '0' << year << '-';
            if (JulianDate(*this) < 100)
            {
                if (JulianDate(*this) < 10)
                    cout << '0';
                cout << '0' << JulianDate(*this) << '\n';
            }
            else
                cout << JulianDate(*this) << '\n';
        }
        if(year >= 10)
        {
            if(year%100 <=10)
                cout << '0';
            cout << year%100 << '-';
            if (JulianDate(*this) < 100)
            {
                if (JulianDate(*this) < 10)
                    cout << '0';
                cout << '0' << JulianDate(*this) << '\n';
            }
            else
                cout << JulianDate(*this) << '\n';
        }
    }
}

void Date::Increment(int numDays)
{
    DayLimitSetter(month, year, *this);
    for(int i = 0; i < numDays; i++)
    {
	day +=1;
	if (day > dayLIMIT)
	{
	    day = 1;
	    month +=1;
	    if (month > MONTHLIMIT)
	    {
            	month = 1;
            	year +=1;
	    }
	    DayLimitSetter(month, year, *this);
	}
    }
}

bool Date::Set(int m, int d, int y)
{
    if (m > 12 || m < 1 || m % 1 !=0)
        return false;
    else if (properDay(m, d, y) == false)
        return false;
    else if (y < 0 || y % 1 != 0)
        return false;
    else
    {
        month = m;
        day = d;
        year = y;
        return true;
    }
    return false;
}

char Date::formatChar = 'D';
bool Date::SetFormat(char f)
{
    if (f == 'D') // Default format : month/day/year
    {
        formatChar = 'D';
        return true;
    }
    else if (f == 'T') // Two-digit format : mm/dd/yy
    {
        formatChar = 'T';
        return true;
    }
    else if (f == 'L') // Long format : Mon dd, yyyy
    {
        formatChar = 'L';
        return true;
    }
    else if (f == 'J')
    {
        formatChar = 'J';
        return true;
    }
    else
    {
        return false;
    }
}
    
//
//
//
//

int Date::dayLIMIT = 31;
int DayLimitSetter (int m, int y, Date& d)
{
    if (m >= 1 && m <= 12)
    {
        if (m == 2) //Specifically checks if user input is for the month Febuary.
        {
            if ((y % 100 == 0 && y % 400 == 00) || (y % 100 != 0 && y % 4 == 0)) //An 'if statement to check leap year status.
            {
                d.dayLIMIT = 29;
                return d.dayLIMIT;
            }
            else
            {
                d.dayLIMIT = 28;
                return d.dayLIMIT;
            }
        }
        else//The code for this 'else' falls under correct inputs and finds number of days based on the pattern of 31 days for odd months before/at 7 and even months at/after 8.
        {
            if (m <= 7 && m % 2 != 0)
            {
                d.dayLIMIT = 31;
                return d.dayLIMIT;
            }
            else if (m >= 8 && m % 2 == 0)
            {
                d.dayLIMIT = 31;
                return d.dayLIMIT;
            }
            else
            {
                d.dayLIMIT = 30;
                return d.dayLIMIT;
            }
        }
    }
    else if (m > 12 || m < 1)
    {
        d.dayLIMIT = 0;
        return d.dayLIMIT;
    }
    return 0;
}

bool Date::properDay (int m, int d, int y) //Function to check if day is within proper bounds
{
    if (d > 31 || d < 1 || d % 1 != 0)
    {
        return false;
    }
    if (DayLimitSetter(m, y, *this) < d || DayLimitSetter(m, y, *this) == 0)
    {
        return false;
    }
    
    return true;
}

int JulianDate(const Date& d)
{
    int JD = 0;
    
    if(d.GetMonth() == 1)
        JD = d.GetDay();
    if(d.GetMonth() == 2)
        JD = d.GetDay() + 31;
    if((d.GetYear() % 100 == 0 && d.GetYear() % 400 == 00) || (d.GetYear() % 100 != 0 && d.GetYear() % 4 == 0))
    {
        if(d.GetMonth() == 3)
            JD = d.GetDay() + 60;
        if(d.GetMonth() == 4)
            JD = d.GetDay() + 91;
        if(d.GetMonth() == 5)
            JD = d.GetDay() + 121;
        if(d.GetMonth() == 6)
            JD = d.GetDay() + 152;
        if(d.GetMonth() == 7)
            JD = d.GetDay() + 182;
        if(d.GetMonth() == 8)
            JD = d.GetDay() + 213;
        if(d.GetMonth() == 9)
            JD = d.GetDay() + 244;
        if(d.GetMonth() == 10)
            JD = d.GetDay() + 274;
        if(d.GetMonth() == 11)
            JD = d.GetDay() + 305;
        if(d.GetMonth() == 12)
            JD = d.GetDay() + 335;
    }
    else
    {
        if(d.GetMonth() == 3)
            JD = d.GetDay() + 59;
        if(d.GetMonth() == 4)
            JD = d.GetDay() + 90;
        if(d.GetMonth() == 5)
            JD = d.GetDay() + 120;
        if(d.GetMonth() == 6)
            JD = d.GetDay() + 151;
        if(d.GetMonth() == 7)
            JD = d.GetDay() + 181;
        if(d.GetMonth() == 8)
            JD = d.GetDay() + 212;
        if(d.GetMonth() == 9)
            JD = d.GetDay() + 243;
        if(d.GetMonth() == 10)
            JD = d.GetDay() + 273;
        if(d.GetMonth() == 11)
            JD = d.GetDay() + 304;
        if(d.GetMonth() == 12)
            JD = d.GetDay() + 334;
    }
    return JD;
}
    
    
    
    
    
    
    
    
    
    
    
    
