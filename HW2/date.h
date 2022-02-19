/*Name: Michael Bryan
 Date : Febuary 5, 2019
 Section : 1
 Assignment : HW #2
 Due Date : Febuary 7, 2019 */

//-------------------------date.h--------------------
#include <string>

class Date
{
    friend int DayLimitSetter (int m, int y, Date& d);
    friend std::string MonthNamer(int m);
    friend int JulianDate(const Date& d);
    
public:

    //Construtors
    Date();
    Date(int m, int d, int y);    

    //Accessors
    int Compare (const Date& d) const;
    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;
    void Show() const;
    void Increment(int numDays = 1);

    //Mutators
    bool Set(int m, int d, int y);
    bool SetFormat(char f);
    void Input();
    
private:
    int year;
    int month;
    int day;
    static char formatChar;
    static int dayLIMIT;
    const static int MONTHLIMIT = 12;
    
    
    //Helper functions
    bool properDay (int m, int d, int y);    
};
