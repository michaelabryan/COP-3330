/*Name: Michael Bryan
 Date : February 21, 2019
 Section : 1
 Assignment : HW #4
 Due Date : March 4, 2019 */

//-------------------------grid.cpp--------------------
#include "grid.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

Grid::Grid()
{
    curRowSize=0;
    curColSize=0;
    grid[curRowSize][curColSize] = '>';
    curDir = EAST;
    curMoverColPos=0;
    curMoverRowPos=0;
    PathOnOff = true;
}

Grid::Grid(int r, int c)
{
    PathOnOff = true;
    srand(time(0));
    int random = rand();
    
    if(r<3 || c<3)
    {
        curRowSize = 3;
        curColSize = 3;
    }
    else if(r>40 || c>40)
    {
        curRowSize = 40;
        curColSize = 40;
    }
    else
    {
        curRowSize = r;
        curColSize = c;
    }

    
    for (int i = 0; i < curRowSize+1; i++)
    {
        for (int j = 0; j < curColSize+2; j++)
        {
            if(i == 0 || i == curRowSize-1)
                grid[i][j] = '#';
            else if(j == 0 || j == curColSize-1)
                grid[i][j] = '#';
            else
                grid[i][j] = '.';
        }
    }
    
    if(random % 4 == 0)
        curDir = NORTH;
    if(random % 4 == 1)
        curDir = WEST;
    if(random % 4 == 2)
        curDir = SOUTH;
    if(random % 4 == 3)
        curDir = EAST;
    
    random = rand();
    if(random % 4 == NORTH) //North wall for random exit
    {
        if(random % curColSize == 0 || random % curColSize == curColSize-1)
            grid[0][curColSize/2] = '.';
        else
            grid[0][random % curColSize] = '.';
    }
    if(random % 4 == WEST) //West wall for random exit
    {
        if(random % curRowSize == 0 || random % curRowSize == curRowSize - 1)
            grid[curRowSize/2][0] = '.';
        else
            grid[random % curRowSize][0] = '.';
    }
    if(random % 4 == SOUTH) //South wall for random exit
    {
        if(random % curColSize == 0 || random % curColSize == curColSize-1)
            grid[curRowSize-1][curColSize/2] = '.';
        else
            grid[curRowSize-1][random % curColSize] = '.';
    }
    if(random % 4 == EAST) //East wall for random exit
    {
        if(random % curRowSize == 0 || random % curRowSize == curRowSize - 1)
            grid[curRowSize/2][curColSize-1] = '.';
        else
            grid[random % curRowSize][curColSize-1] = '.';
    }
    
    random = rand();
    if(curDir == NORTH) //Randomly places mover in a north facing location
    {
        if(random % curRowSize != 0 && random % curColSize != 0 && random % curRowSize != curRowSize - 1 && random % curColSize != curColSize-1)
        {
            grid[random % curRowSize][random % curColSize] = '^';
            curMoverRowPos = random % curRowSize;
            curMoverColPos = random % curColSize;
        }
        else
        {
            grid[curRowSize/2][curColSize/2] = '^';
            curMoverRowPos = curRowSize/2;
            curMoverColPos = curColSize/2;
        }
    }
    if(curDir == WEST) //Randomly places mover in a west facing location
    {
        if(random % curRowSize != 0 && random % curColSize != 0 && random % curRowSize != curRowSize - 1 && random % curColSize != curColSize-1)
        {
            grid[random % curRowSize][random % curColSize] = '<';
            curMoverRowPos = random % curRowSize;
            curMoverColPos = random % curColSize;
        }
        else
        {
            grid[curRowSize/2][curColSize/2] = '<';
            curMoverRowPos = curRowSize/2;
            curMoverColPos = curColSize/2;
        }
    }
    if(curDir == SOUTH) //Randomly places mover in a south facing location
    {
        if(random % curRowSize != 0 && random % curColSize != 0 && random % curRowSize != curRowSize - 1 && random % curColSize != curColSize-1)
        {
            grid[random % curRowSize][random % curColSize] = 'v';
            curMoverRowPos = random % curRowSize;
            curMoverColPos = random % curColSize;
        }
        else
        {
            grid[curRowSize/2][curColSize/2] = 'v';
            curMoverRowPos = curRowSize/2;
            curMoverColPos = curColSize/2;
        }
    }
    if(curDir == EAST) //Randomly places mover in a east facing location
    {
        if(random % curRowSize != 0 && random % curColSize != 0 && random % curRowSize != curRowSize - 1 && random % curColSize != curColSize-1)
        {
            grid[random % curRowSize][random % curColSize] = '>';
            curMoverRowPos = random % curRowSize;
            curMoverColPos = random % curColSize;
        }
        else
        {
            grid[curRowSize/2][curColSize/2] = '>';
            curMoverRowPos = curRowSize/2;
            curMoverColPos = curColSize/2;
        }
    }
}

Grid::Grid(int r, int c, int mr, int mc, int d)
{
    PathOnOff = true;
    if(r < 1 || c < 1)
    {
        curRowSize = 1;
        curColSize = 1;
    }
    else if(r > 40 || c > 40)
    {
        curRowSize = 40;
        curColSize = 40;
    }
    else
    {
        curRowSize = r;
        curColSize = c;
    }
    
    if(d < 0)
        curDir = NORTH;
    else if (d > 3)
        curDir = EAST;
    else
        curDir = d;
    
    for (int i = 0; i < curRowSize+1; i++)
    {
        for (int j = 0; j < curColSize+2; j++)
            grid[i][j] = '.';
    }
    
    if (mr < 0)
        curMoverRowPos = 0;
    else if (mr > curRowSize)
        curMoverRowPos = curRowSize;
    else
        curMoverRowPos = mr;
    if (mc < 0)
        curMoverColPos = 0;
    else if (mc > curColSize)
        curMoverColPos = curColSize;
    else
        curMoverColPos = mc;
    
    if(curDir == NORTH)
        grid[curMoverRowPos][curMoverColPos] = '^';
    if(curDir == WEST)
        grid[curMoverRowPos][curMoverColPos] = '<';
    if(curDir == SOUTH)
        grid[curMoverRowPos][curMoverColPos] = 'v';
    if(curDir == EAST)
        grid[curMoverRowPos][curMoverColPos] = '>';
}

bool Grid::Move(int s)
{
    if(curDir == NORTH)
    {
        for(int i = 0; i < s; i++)
        {
            if(grid[curMoverRowPos-i-1][curMoverColPos] == '#' || curMoverRowPos-i-1 < 0)
                return false;
        }
        for(int i = 0; i < s; i++)
        {
            if(grid[curMoverRowPos-i-1][curMoverColPos] == '.')
                grid[curMoverRowPos-i-1][curMoverColPos] = ' ';
            if(i == s-1 && grid[curMoverRowPos-s][curMoverColPos] == '0')
                grid[curMoverRowPos-s][curMoverColPos] = '@';
            else if(i == s-1)
                grid[curMoverRowPos-s][curMoverColPos] = '^';
        }
        if(grid[curMoverRowPos][curMoverColPos] == '@')
            grid[curMoverRowPos][curMoverColPos] = '0';
        else
            grid[curMoverRowPos][curMoverColPos] = ' ';
        curMoverRowPos -= s;
        return true;
    }
    else if(curDir == WEST)
    {
        for(int i = 0; i < s; i++)
        {
            if(grid[curMoverRowPos][curMoverColPos-i-1] == '#' || curMoverColPos-i-1 < 0)
                return false;
        }
        for(int i = 0; i < s; i++)
        {
            if(grid[curMoverRowPos][curMoverColPos-i-1] == '.')
                grid[curMoverRowPos][curMoverColPos-i-1] = ' ';
            if(i == s-1 && grid[curMoverRowPos][curMoverColPos-s] == '0')
                grid[curMoverRowPos][curMoverColPos-s] = '@';
            else if(i == s-1)
                grid[curMoverRowPos][curMoverColPos-s] = '<';
        }
        if(grid[curMoverRowPos][curMoverColPos] == '@')
            grid[curMoverRowPos][curMoverColPos] = '0';
        else
            grid[curMoverRowPos][curMoverColPos] = ' ';
        curMoverColPos -= s;
        return true;
    }
    else if(curDir == SOUTH)
    {
        for(int i = 0; i < s; i++)
        {
            if(grid[curMoverRowPos+i+1][curMoverColPos] == '#' || curMoverRowPos+i+1 > curRowSize)
                return false;
        }
        for(int i = 0; i < s; i++)
        {
            if(grid[curMoverRowPos+i+1][curMoverColPos] == '.')
                grid[curMoverRowPos+i+1][curMoverColPos] = ' ';
            if(i == s-1 && grid[curMoverRowPos+s][curMoverColPos] == '0')
                grid[curMoverRowPos+s][curMoverColPos] = '@';
            else if(i == s-1)
                grid[curMoverRowPos+s][curMoverColPos] = 'v';
        }
        if(grid[curMoverRowPos][curMoverColPos] == '@')
            grid[curMoverRowPos][curMoverColPos] = '0';
        else
            grid[curMoverRowPos][curMoverColPos] = ' ';
        curMoverRowPos += s;
        return true;
    }
    else if(curDir == EAST)
    {
        for(int i = 0; i < s; i++)
        {
            if(grid[curMoverRowPos][curMoverColPos+i+1] == '#' || curMoverColPos+i+1 > curColSize)
                return false;
        }
        for(int i = 0; i < s; i++)
        {
            if(grid[curMoverRowPos][curMoverColPos+i+1] == '.')
                grid[curMoverRowPos][curMoverColPos+i+1] = ' ';
            if(i == s-1 && grid[curMoverRowPos][curMoverColPos+s] == '0')
                grid[curMoverRowPos][curMoverColPos+s] = '@';
            else if(i == s-1)
                grid[curMoverRowPos][curMoverColPos+s] = '>';
            
        }
        if(grid[curMoverRowPos][curMoverColPos] == '@')
            grid[curMoverRowPos][curMoverColPos] = '0';
        else
            grid[curMoverRowPos][curMoverColPos] = ' ';
        curMoverColPos += s;
        return true;
    }
    
    return false;
}

void Grid::TogglePath()
{
    if(PathOnOff == true)
        PathOnOff = false;
    else if(PathOnOff == false)
        PathOnOff = true;
}

void Grid::TurnLeft()
{
    if(grid[curMoverRowPos][curMoverColPos] == '^')
    {
        grid[curMoverRowPos][curMoverColPos] = '<';
        curDir = WEST;
    }
    else if(grid[curMoverRowPos][curMoverColPos] == '<')
    {
        grid[curMoverRowPos][curMoverColPos] = 'v';
        curDir = SOUTH;
    }
    else if(grid[curMoverRowPos][curMoverColPos] == 'v')
    {
        grid[curMoverRowPos][curMoverColPos] = '>';
        curDir = EAST;
    }
    else if(grid[curMoverRowPos][curMoverColPos] == '>')
    {
        grid[curMoverRowPos][curMoverColPos] = '^';
        curDir = NORTH;
    }
    if(grid[curMoverRowPos][curMoverColPos] == '@')
    {
        if(curDir == NORTH)
            curDir = WEST;
        else if(curDir == WEST)
            curDir = SOUTH;
        else if(curDir == SOUTH)
            curDir = EAST;
        else if(curDir == EAST)
            curDir = NORTH;
    }
}

void Grid::PutDown()
{
    if(grid[curMoverRowPos][curMoverColPos] == '@')
        return;
    else
        grid[curMoverRowPos][curMoverColPos] = '@';
}

bool Grid::PutDown(int r, int c)
{
    if(r > curRowSize || r < 0 || c > curColSize || c < 0)
        return false;
    else
    {
        if(grid[r][c] == '#' || grid[r][c] == '0')
            return false;
        else
        {
            if(grid[r][c] == '^' || grid[r][c] == '<' ||grid[r][c] == 'v' || grid[r][c] == '>')
            {
                grid[r][c] = '@';
                return true;
            }
            else
            {
                grid[r][c] = '0';
                return true;
            }
        }
    }
}

bool Grid::PickUp()
{
    if(grid[curMoverRowPos][curMoverColPos] == '@')
    {
        if(curDir == NORTH)
            grid[curMoverRowPos][curMoverColPos] = '^';
        if(curDir == WEST)
            grid[curMoverRowPos][curMoverColPos] = '<';
        if(curDir == SOUTH)
            grid[curMoverRowPos][curMoverColPos] = 'v';
        if(curDir == EAST)
            grid[curMoverRowPos][curMoverColPos] = '>';
        return true;
    }
    
    return false;
}

bool Grid::PlaceBlock(int r, int c)
{
    if(r < 0 || r > curRowSize)
        return false;
    if(c < 0 || c > curColSize)
        return false;
    
    if(grid[r][c] == '.' || grid[r][c] == ' ')
    {
        grid[r][c] = '#';
        return true;
    }
    else
        return false;
}

void Grid::Grow(int gr, int gc)
{
    int tempRow = curRowSize;
    int tempCol = curColSize;
    
    if(gr + curRowSize >= 40 && gc + curColSize < 40)
    {
        curRowSize = 40;
        curColSize += gc;
        for(int i = 0; i < curRowSize; i++)
        {
            for(int j = 0; j < curColSize; j++)
            {
                if(j >= curColSize - gc)
                    grid[i][j] = '.';
                if(i >= tempRow)
                    grid[i][j] = '.';
            }
        }
    }
    else if(gc + curColSize >= 40 && gr + curRowSize < 40)
    {
        curRowSize += gr;
        curColSize = 40;
        for(int i = 0; i < curRowSize; i++)
        {
            for(int j = 0; j < curColSize; j++)
            {
                if(j >= tempCol)
                    grid[i][j] = '.';
                if(i >= curRowSize - gr)
                    grid[i][j] = '.';
            }
        }
    }
    else if(gc + curColSize >= 40 && gc + curColSize >= 40)
    {
        curRowSize = 40;
        curColSize = 40;
        
        for(int i = 0; i < curRowSize; i++)
        {
            for(int j = 0; j < curColSize; j++)
            {
                if(j >= tempCol)
                    grid[i][j] = '.';
                if(i >= tempRow)
                    grid[i][j] = '.';
            }
        }
    }
    else
    {
        curRowSize += gr;
        curColSize += gc;
        for(int i = 0; i < curRowSize; i++)
        {
            for(int j = 0; j < curColSize; j++)
            {
                if(j >= curColSize - gc)
                    grid[i][j] = '.';
                if(i >= curRowSize - gr)
                    grid[i][j] = '.';
            }
        }
    }
}

void Grid::Display() const
{
    if(curRowSize == 0 && curColSize == 0)
        cout << grid[curRowSize][curColSize] << '\n';
    else if(PathOnOff == true)
    {
        cout << "The Grid:\n";
        for(int i = 0; i < curRowSize; i++)
        {
            for(int j = 0; j < curColSize; j++)
            {
                cout << grid[i][j];
                if(j != curColSize-1)
                    cout << ' ';
            }
            cout << '\n';
        }
    }
    else if(PathOnOff == false)
    {
        cout << "The Grid:\n";
        for(int i = 0; i < curRowSize; i++)
        {
            for(int j = 0; j < curColSize; j++)
            {
                if(grid[i][j] == ' ')
                    cout << '.';
                else
                    cout << grid[i][j];
                if(j != curColSize-1)
                    cout << ' ';
            }
            cout << '\n';
        }
    }
}
bool Grid::FrontIsClear() const
{
    if(curDir == NORTH)
    {
        if(grid[curMoverRowPos-1][curMoverColPos] == '#' || curMoverRowPos - 1 < 0)
            return false;
        else
            return true;
    }
    if(curDir == WEST)
    {
        if(grid[curMoverRowPos][curMoverColPos-1] == '#' || curMoverColPos - 1 < 0)
            return false;
        else
            return true;
    }
    if(curDir == SOUTH)
    {
        if(grid[curMoverRowPos+1][curMoverColPos] == '#' || curMoverRowPos + 1 >= curRowSize)
            return false;
        else
            return true;
    }
    if(curDir == EAST)
    {
        if(grid[curMoverRowPos][curMoverColPos+1] == '#' || curMoverColPos + 1 >= curColSize)
            return false;
        else
            return true;
    }
    
    return false;
}

bool Grid::RightIsClear() const
{
    if(curDir == NORTH)
    {
        if(grid[curMoverRowPos][curMoverColPos+1] == '#' || curMoverColPos + 1 > curColSize)
            return false;
        else
            return true;
    }
    if(curDir == WEST)
    {
        if(grid[curMoverRowPos-1][curMoverColPos] == '#' || curMoverRowPos - 1 < 0)
            return false;
        else
            return true;
    }
    if(curDir == SOUTH)
    {
        if(grid[curMoverRowPos][curMoverColPos-1] == '#' || curMoverColPos - 1 < 0)
            return false;
        else
            return true;
    }
    if(curDir == EAST)
    {
        if(grid[curMoverRowPos+1][curMoverColPos] == '#' || curMoverRowPos + 1 > curRowSize)
            return false;
        else
            return true;
    }
    
    return false;
}

int Grid::GetRow() const
{
    return curMoverRowPos;
}

int Grid::GetCol() const
{
    return curMoverColPos;
}

int Grid::GetNumRows() const
{
    return curRowSize;
}

int Grid::GetNumCols() const
{
    return curColSize;
}
