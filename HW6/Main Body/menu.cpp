/*Name: Michael Bryan
 Date : April 4, 2019
 Section : 1
 Assignment : HW #6
 Due Date : April 10, 2019 */

//-------------------------menu.cpp--------------------
#include <iostream>
#include "studentlist.h"
#include "students.h"
using namespace std;

void printMenu();

int main()
{
    char userMenuSelection = '\0';
    bool skipBeginning = false, invalidMenuChoice;
    StudentList StudentDatabase;
    
    do
    {
        if (skipBeginning == false) //Prints the menu only if the user has already gone through an option
        {
            if(userMenuSelection != 'M')
                printMenu();
            cout << "Choice: ";
            cin >> userMenuSelection;
            userMenuSelection = toupper(userMenuSelection);
        }
        switch (userMenuSelection) //My switch code used in previous homeworks
        {
            case 'I': //
            {
                char filename[30];
                cout << "Enter a file name to import: ";
                cin >> filename;
                if (StudentDatabase.ImportFile(filename) == false)
                    cout << "Unsuccesful Import.\n";
                
                skipBeginning = false;
                
                break;
            }
            case 'S': //
            {
                StudentDatabase.ShowList();
                skipBeginning = false;
                
                break;
            }
            case 'E': //
            {
                char filename[30];
                cout << "Enter a file name to export: ";
                cin >> filename;
                if(StudentDatabase.CreateReportFile(filename) == false)
                    cout << "Unsuccesful Export.\n";
                skipBeginning = false;
                
                break;
            }
            case 'M': //
            {
                printMenu();
                skipBeginning = false;
                
                break;
            }
            case 'Q': //Exits program with a funny* quote (* hiliarity value may vary per user)
            {
                cout << "\nHasta la Vista.......... Baby.\n";    //Arnold will be baaaahck.
                
                break;
            }
            default: //Switch statement defaults if user inputs char that is not one of the options
            {
                do
                {
                    cout << "\nInvalid Choice.\nYou can try Again: ";
                    invalidMenuChoice = true;
                    cin >> userMenuSelection;
                    userMenuSelection = toupper(userMenuSelection);
                    
                    if (userMenuSelection == 'I' || userMenuSelection == 'S' || userMenuSelection == 'E' || userMenuSelection == 'M'|| userMenuSelection == 'O')
                    {
                        invalidMenuChoice = false;
                        
                        break;
                    }
                } while (invalidMenuChoice == true);
                skipBeginning = true;
                invalidMenuChoice = false;
            }
        }
        
        if (userMenuSelection == 'Q')
        {
            break;
        }
        invalidMenuChoice = false;
        
    } while (userMenuSelection == 'I' || userMenuSelection == 'S' || userMenuSelection == 'E' || userMenuSelection == 'M');
    
    return 0;
}

void printMenu()
{
    cout << " \t\t*** Student List menu ***\n";
    cout << " \t\t                         \n";
    cout << "I\t\tImport students from a file\n";
    cout << "S\t\tShow student list (brief)\n";
    cout << "E\t\tExport a grade report (to file)\n";
    cout << "M\t\tShow this Menu\n";
    cout << "Q\t\tQuit Program\n";
}
