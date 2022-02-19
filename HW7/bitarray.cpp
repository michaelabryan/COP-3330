/*Name: Michael Bryan
 Date : April 14, 2019
 Section : 1
 Assignment : HW #7
 Due Date : April 18, 2019 */

//-------------------------bitarray.cpp--------------------

#include "bitarray.h"
#include <math.h>

BitArray::BitArray(unsigned int n)
{
    double tempSizeof = (n*1.0) / (sizeofChar);
    if(fmod(tempSizeof,1)!=0) //This line does modulus on the double tempSizeof
        arraySize = n/sizeofChar + 1;
    else
        arraySize = n/sizeofChar;
    barray = new unsigned char [arraySize];
    for(int i = 0; i < arraySize; i++)
        barray[i] = 0;
    
}

BitArray::BitArray(const BitArray& ba)
{
    arraySize = ba.arraySize;
    barray = new unsigned char [arraySize];
    for(int i = 0; i < arraySize; i++)
        barray[i] = ba.barray[i];
}

BitArray::~BitArray()
{
    delete [] barray;
}

BitArray& BitArray::operator= (const BitArray& a)
{
    arraySize = a.arraySize;
    barray = new unsigned char [arraySize];
    for(int i = 0; i < arraySize; i++)
        barray[i] = a.barray[i];
    return *this;
}

unsigned int BitArray::Length() const
{
    return arraySize*8;
}

void BitArray::Set   (unsigned int index)
{
    int numtoMove = 0;
    int arraySlot = index/sizeofChar;
    if(index%8 == 0)
        this->barray[arraySlot] = this->barray[arraySlot] | 1;
    else
        numtoMove = index % sizeofChar;
    this->barray[arraySlot] = this->barray[arraySlot] | Mask(numtoMove);
}

void BitArray::Unset (unsigned int index)
{
    int arraySlot = index/sizeofChar;
    int numtoMove = index % sizeofChar;
    this->barray[arraySlot] = this->barray[arraySlot] & ~Mask(numtoMove);
}

void BitArray::Flip  (unsigned int index)
{
    int arraySlot = index/sizeofChar;
    int numtoMove = index % sizeofChar;
    this->barray[arraySlot] = this->barray[arraySlot] ^ Mask(numtoMove);
}

bool BitArray::Query (unsigned int index) const
{
    int arraySlot = index/sizeofChar;
    int numtoMove = index % sizeofChar;
    if(this->barray[arraySlot] & Mask(numtoMove))
        return true;
    else
        return false;
}

//Friend functions
ostream& operator<< (ostream& os, const BitArray& a)
{
    os << '(';
    
    for(int i = 0; i < a.Length(); i++)
    {
        if (a.Query(i) == true)
            os << '1';
        else
            os << '0';
    }
    
    os << ')';
    
    return os;
}

bool operator== (const BitArray& ba1, const BitArray& ba2)
{
    for(int i = 0; i < ba1.Length(); i++)
    {
        if(ba1.barray[i] != ba2.barray[i])
            return false;
    }
    return true;
}

bool operator!= (const BitArray& ba1, const BitArray& ba2)
{
    if(ba1 == ba2)
        return false;
    else
        return true;
}

int BitArray::Mask(int num) const //Used to modulate bits
{
    return (1 << num);
}
