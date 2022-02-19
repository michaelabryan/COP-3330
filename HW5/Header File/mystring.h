/*Name: Michael Bryan
 Date : March 8, 2019
 Section : 1
 Assignment : HW #5
 Due Date : March 26, 2019 */

//-------------------------mystring.h--------------------
#include <iostream>
using namespace std;

class MyString
{
    friend ostream& operator<<(ostream& os, const MyString& ms);
    friend istream& operator>>(istream& is, MyString& ms);
    friend istream& getline (istream& is, MyString& ms);
    friend istream& getline(istream& is, MyString& ms, char delim);
    
    friend MyString operator+(const MyString& , const MyString& );
    
    friend bool operator<(const MyString& ms1, const MyString& ms2);
    friend bool operator>(const MyString& ms1, const MyString& ms2);
    friend bool operator<=(const MyString& ms1, const MyString& ms2);
    friend bool operator>=(const MyString& ms1, const MyString& ms2);
    friend bool operator==(const MyString& ms1, const MyString& ms2);
    friend bool operator!=(const MyString& ms1, const MyString& ms2);
    
public:
    MyString();                                // empty string
    MyString(const char* tempString);          // conversion from c-string
    MyString(int x);                           // conversion from int
    ~MyString();                               // destructor
    MyString(const MyString& ms);              // copy constructor
    MyString& operator=(const MyString& ms);   // assignment operator
    MyString& operator+=(const MyString& ms);  // concatenation/assignment
    
    // bracket operators to access char positions
    char& operator[] (unsigned int index);
    const char& operator[] (unsigned int index) const;
    
    // insert s into the string at position "index"
    MyString& insert(unsigned int index, const MyString& s);
    
    // find index of the first occurrence of s inside the string
    //  return the index, or -1 if not found
    int indexOf(const MyString& s) const;
    
    int getLength() const;             // return string length
    const char* getCString() const;    // return c-string equiv
    
    MyString substring(unsigned int , unsigned int ) const;
    MyString substring(unsigned int ) const;
private:
    int Length;
    char * string;
    void GrowShrinkString(int newLength);
};
