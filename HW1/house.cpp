/*Name: Michael Bryan
 Date : January 19, 2019
 Section : 1
 Assignment : HW #1
 Due Date : January 25, 2019 */

//-------------------------House.cpp---------------------
#include <iostream>
#include <iomanip>
#include <cmath>
#include "house.h"
using namespace std;

//Constructor
House::House(int bSize, char border, char fill)
{
    if (bSize < 3 || bSize > 37)
    {
        if (bSize < 3)
        {
            bSize = 3;
            SquarebaseSize = 3;
        }
        else
        {
            bSize = 37;
            SquarebaseSize = 37;
        }
    }
    else
        SquarebaseSize = bSize;
    TribaseSize = bSize + 2;
    BorderChar = SetBorder(border);
    FillChar = SetFill(fill);
}

//Member Functions
int House::GetSize()
{
    return SquarebaseSize;
}
int House::Perimeter()
{
    return ((SquarebaseSize * 3) + (TribaseSize * 2 + 2));
}
double House::Area()
{
    return ((SquarebaseSize*SquarebaseSize) + ((.5*TribaseSize) * (TribaseSize*sin(60))));
}

void House::Grow()
{
    if (SquarebaseSize < 37)
    {
        SquarebaseSize += 1;
        TribaseSize +=1;
    }
    else
    {
        SquarebaseSize = 37;
    }
}
void House::Shrink()
{
    if (SquarebaseSize > 3)
    {
        SquarebaseSize -= 1;
        TribaseSize -=1;
    }
    else
    {
        SquarebaseSize = 3;
    }
}

char House::SetBorder(char newBorder)
{
    if (newBorder >= '!' && newBorder <= '~')
    {
        BorderChar = newBorder;
        return newBorder;
    }
    else
        return 'X';
}
char House::SetFill(char newFill)
{
    if (newFill >= '!' && newFill <= '~')
    {
        FillChar = newFill;
        return newFill;
    }
    else
        return '*';
}

void House::Draw()
{
    int counter;
    //Nested for loop for Triangle portion of House
    for(int i = 0; i < TribaseSize; ++i)
    {
        for(counter = (TribaseSize-i-1); counter > 0; counter--)
            cout << " ";
        for(int j = 0; j <= i; ++j)
        {
            if(j==0 || j==i)
                cout << BorderChar << " ";
            else if (i == TribaseSize-1)
            {
                if(j==0 || j==i)
                    cout << BorderChar << " ";
                if (j==1 || j== i-1)
                    cout << BorderChar << " ";
                else
                    cout << FillChar << " ";
            }
            else
                cout << FillChar << " ";
        }
        cout << '\n';
    }
    //Nested for loop for the Square portion of the house
    for (int i = 1; i < SquarebaseSize; i++)
    {
        cout << "  ";
        for(int j = 0; j<SquarebaseSize; j++)
        {
            if (i == SquarebaseSize-1)
            {
                cout << BorderChar << " ";
            }
            else if(j == 0 || j == SquarebaseSize-1)
            {
                cout << BorderChar << " ";
            }
            else
                cout << FillChar << " ";
        }
        cout << endl;
    }
}
void House::Summary()
{
    cout << "House width and height base to roof = " << GetSize() << " units.\n";
    cout << "Perimeter of house = " << Perimeter() << " units.\n";
    cout << "Area of house = " << setprecision(2) << fixed << Area() << " units.\n";
    cout << "House looks like:\n";
    Draw();
}
