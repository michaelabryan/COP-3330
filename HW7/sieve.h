/*Name: Michael Bryan
 Date : April 14, 2019
 Section : 1
 Assignment : HW #7
 Due Date : April 18, 2019 */

//-------------------------sieve.h--------------------
#include "bitarray.h"
#include <cmath>
#ifndef sieve_h
#define sieve_h
//Put definitions in header code
void Sieve(BitArray& ba)
{
    for(int i = 0; i < ba.Length(); i++) //Sets all the bits to 1s
        ba.Set(i);
    ba.Unset(0); //Unset 0 and 1
    ba.Unset(1);
    
    for(int i = 2; i < sqrt(ba.Length())+1; i++)//Nested for loop to find multiples of primes
    {
        if(ba.Query(i) == true)
        {
            for(int j = 2; j < ba.Length(); j++)
                ba.Unset(i*j);
        }
    }
}

#endif
