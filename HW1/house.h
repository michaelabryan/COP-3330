/*Name: Michael Bryan
 Date : January 18, 2019
 Section : 1
 Assignment : HW #1
 Due Date : January 25, 2019 */

//-------------------------House.h--------------------

class House
{
    friend int SetBaseSize(int bSize);
    
public:
    House(int bSize, char border = 'X', char fill = '*');
    
    int GetSize();
    int Perimeter();
    double Area();
    
    void Grow();
    void Shrink();
    
    char SetBorder(char newBorder);
    char SetFill(char newFill);
    
    void Draw();
    void Summary();
    
    
private:
    int SquarebaseSize;
    int TribaseSize;
    char BorderChar;
    char FillChar;
};
