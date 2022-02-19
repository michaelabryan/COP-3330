/*Name: Michael Bryan
 Date : April 4, 2019
 Section : 1
 Assignment : HW #6
 Due Date : April 10, 2019 */

//-------------------------studentlist.h--------------------
#include "students.h"

class StudentList
{
public:
   StudentList();		// starts out empty
   ~StudentList();		// cleanup (destructor)

   bool ImportFile(const char* filename);
   bool CreateReportFile(const char* filename);
   void ShowList() const;	// print basic list data

private:
    Student ** list;
    int currentListSize;
    void GrowArray(int sizetoGrow);
    ofstream& stuHeader(ofstream& out) const;
    ofstream& printStuInfo(ofstream& out, Student ** array, int courseNum) const;
};
