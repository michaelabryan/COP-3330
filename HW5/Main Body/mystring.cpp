/*Name: Michael Bryan
 Date : March 8, 2019
 Section : 1
 Assignment : HW #5
 Due Date : March 26, 2019 */

//-------------------------mystring.cpp--------------------

#include "mystring.h"
#include <cstring>
#include <cstdio>


MyString::MyString()
{
    Length = 0;
    string = NULL;
}

MyString::MyString(const char* tempString)
{
    Length = strlen(tempString);
    string = new char[Length];
    for(int i = 0; i < Length; i++)
    {
        string[i] = tempString[i];
        if(i == Length - 1)
            string[i+1] = '\0';
    }
}

MyString::MyString(int x)
{
    int temp = x;
    for(Length = 1; temp > 0; Length++)
        temp /= 10;
    string = new char[Length];
    sprintf(string,"%d",x);
    string[Length-1] = '\0';
}

MyString::~MyString()
{
    if(string != NULL)
        delete [] string;
}

MyString::MyString(const MyString& ms)
{
    if((*this).string != NULL)
        delete [] this->string;
    (*this).Length = strlen(ms.getCString());
    this->string = new char[this->Length];
    
    for(int i = 0; i < (*this).Length; i++)
        this->string[i] = ms.string[i];
    
}

MyString& MyString::operator=(const MyString& ms)
{
//    if(this->string != NULL)
//        delete [] this->string;
    this->Length = strlen(ms.string);
    (*this) = new char[this->Length];
    
    for(int i = 0; i < strlen(ms.string); i++)
        this->string[i] = ms.string[i];
    
    return *this;
}

MyString& MyString::operator+=(const MyString& ms)
{
    int beginningLength = strlen(this->string);
    int finalLength = strlen(ms.string)+beginningLength; //Used to find end of C-string
    this->GrowShrinkString(finalLength);
    for(int i = beginningLength; i < finalLength; i++)
        this->string[i] = ms.string[i-beginningLength];
    
    return *this;
}

char& MyString::operator[] (unsigned int index)
{
    int tempLength = this->Length;
    
    if(index > this->Length)
    {
        this->GrowShrinkString(index);
        for(int i = tempLength; i < this->Length; i++)
            this->string[i] = ' ';
        return this->string[index];
    }
    else
        return this->string[index];
}

const char& MyString::operator[] (unsigned int index) const
{
    if(index > Length)
        return 0;
    else
        return this->string[index];
}

MyString& MyString::insert(unsigned int index, const MyString& s)
{
    char * temp = new char[this->Length - index]; //Used to store char after the index pos.
    for(int i = index; i < this->Length; i++)
        temp[i-index] = this->string[i]; //Stores end of string in temp
    this->Length += strlen(s.getCString()); //Length is expanded
    for(int i = 0; i < this->Length; i++)
    {
        if(i >= index && i <= index+strlen(s.getCString()))
            this->string[i] = s.string[i-index];
        if(i > index+strlen(s.getCString()))
            this->string[i] = temp[i-index];
    }
    
    delete [] temp;
    
    return *this;
}

int MyString::indexOf(const MyString& s) const
{
    char * temp = strstr(this->string, s.string);
    
    if(temp == NULL)
        return -1;
    else
        return temp[0];
}

int MyString::getLength() const
{
    return Length;
}

const char* MyString::getCString() const
{
    return string;
}

MyString MyString::substring(unsigned int begin, unsigned int length) const
{
    MyString sub;
    
    for(int i = begin; i < length+begin; i++)
    {
        sub[i] = this->string[i];
        if(i == this->Length)
            return sub;
    }
    return sub;
}

MyString MyString::substring(unsigned int start) const
{
    MyString sub;
    
    for(int i = start; i < this->Length; i++)
        sub[i] = this->string[i];
    
    return sub;
}

ostream& operator<<(ostream& os, const MyString& ms)
{
    if(ms.string == NULL)
        os << "\0";
    else
        os << ms.getCString();
    
    return os;
}

istream& operator>>(istream& is, MyString& ms)
{
    char temp[30];

    is >> temp;
    ms.GrowShrinkString(strlen(temp));
    for(int i = 0; i < ms.Length; i++)
        ms.string[i] = temp[i];
    
    return is;
}

istream& getline(istream& is, MyString& ms)
{
    char temp[500];
    
    is >> temp;
    ms.GrowShrinkString(strlen(temp));
    for(int i = 0; i < ms.Length; i++)
    {
        if(temp[i] == '\n')
            return is;
        else
            ms.string[i] = temp[i];
    }
    return is;
}

istream& getline(istream& is, MyString& ms, char delim)
{
    char temp[500];
    
    is >> temp;
    ms.GrowShrinkString(strlen(temp));
    for(int i = 0; i < ms.Length; i++)
    {
        if(temp[i] == delim)
        {
            ms.Length -= 1;
            return is;
        }
        else
            ms.string[i] = temp[i];
    }
    return is;
}

MyString operator+(const MyString& ms1, const MyString& ms2)
{
    //This set of code finds the length for our for loop and sets up a MyString object
    MyString temp;
    int ms1Length = strlen(ms1.string);
    int ms2Length = strlen(ms2.string);
    int totalLength = ms1Length+ms2Length;
    temp.GrowShrinkString(totalLength);
    
    for(int i = 0; i < totalLength; i++)
    {
        if(i <= ms1Length)
            temp.string[i] = ms1.string[i];
        if(i > ms1Length)
            temp.string[i] = ms2.string[i-ms1Length];
    }
    
    return temp;
}

bool operator<(const MyString& ms1, const MyString& ms2)
{
    if(strcmp(ms1.getCString(),ms2.getCString()) < 0)
        return true;
    if(strcmp(ms1.getCString(),ms2.getCString()) == 0)
        return false;
    if(strcmp(ms1.getCString(),ms2.getCString()) > 0)
        return false;
    
    return false;
}

bool operator>(const MyString& ms1, const MyString& ms2)
{
    if(strcmp(ms1.getCString(),ms2.getCString()) < 0)
        return false;
    if(strcmp(ms1.getCString(),ms2.getCString()) == 0)
        return false;
    if(strcmp(ms1.getCString(),ms2.getCString()) > 0)
        return true;

    return false;
}

bool operator<=(const MyString& ms1, const MyString& ms2)
{
    if(ms2 < ms1)
        return false;
    else
        return true;
}

bool operator>=(const MyString& ms1, const MyString& ms2)
{
    if(ms2>ms1)
        return false;
    else
        return true;
}

bool operator==(const MyString& ms1, const MyString& ms2)
{
    if(strcmp(ms1.getCString(), ms2.getCString()) == 0)
        return true;
    else
        return false;
}

bool operator!=(const MyString& ms1, const MyString& ms2)
{
    if(ms1 == ms2)
        return false;
    else
        return true;
}

//Helper Function
void MyString::GrowShrinkString(int newLength) //Grows/Shrinks c-string as needed
{
    char * temp = new char[newLength];
    
    if(newLength > this->Length)
    {
        for(int i = 0; i < this->Length; i++)
            temp[i] = this->string[i];
    }
    else if(newLength < this->Length)
    {
        for(int i = 0; i < newLength-1; i++)
            temp[i] = this->string[i];
    }
    
    delete [] this->string;
    Length = newLength;
    this->string = temp;
    temp = NULL;
    
}
