#include <array>
#include "GradeBook.h" // GradeBook class definition
using namespace std;

int main() {
    // array of student grades, GradeBook::students access static data member
    const array<array<int, GradeBook::tests>, GradeBook::students> grades{
        {87, 96, 70, 68, 87, 90, 94, 100, 90, 100, 81, 82, 83, 65, 85,
        78, 87, 65, 85, 75, 83, 91, 94, 100, 76, 72, 84, 87, 93, 73}};

    string courseName{"CS101 Introduction to C++ Programming"};

    GradeBook myGradeBook(courseName, grades);
    myGradeBook.displayMessage();
    myGradeBook.processGrades();

    
}