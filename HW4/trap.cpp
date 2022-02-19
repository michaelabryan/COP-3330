/*Name: Michael Bryan
 Date : February 24, 2019
 Section : 1
 Assignment : HW #4
 Due Date : March 4, 2019 */

//-------------------------trap.cpp--------------------

#include "grid.h"
#include <iostream>
using namespace std;

int main()
{
    bool incorrectFlag;
    int rows, columns;
    Grid g;
    cout << "Please type a number (3-40) for the number of Rows and Columns.\n";
    
    do //Have keyboard monkey type in the correct number of rows and columns
    {
        cout << "Rows: ";
        cin >> rows;
        cout << "Columns: ";
        cin >> columns;
        if(rows > 40 || columns > 40 || rows < 3 || columns < 3)
        {
            cout << "Incorrect. Please try again. \n\n";
            incorrectFlag = true;
        }
        else
        {
            g = Grid(rows, columns);
            incorrectFlag = false;
        }
    } while (incorrectFlag == true);
    
    g.Display();
    
    //Begin trying to exit the underground dungeon
    do
    {
        g.Move(1);
    } while (g.FrontIsClear() == true);
    g.TurnLeft();
    do
    {
        g.Move(1);
        if(g.GetRow() == 0 || g.GetRow() == g.GetNumRows() - 1 || g.GetCol() == 0 || g.GetCol() == g.GetNumCols() - 1)
        {
            g.Display();
            cout << "We escaped!!\n";
            return 0;
        }
        if(g.RightIsClear() == true)
        {
            g.TurnLeft();
            g.TurnLeft();
            g.TurnLeft();
            g.Move(1);
            g.Display();
            cout << "We escaped!!\n";
            return 0;
        }
        if(g.FrontIsClear() == false)
            g.TurnLeft();
    } while (g.RightIsClear() == false);
    
    return 0;
}
