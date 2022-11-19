#include <iostream>
using namespace std;

void cubeByReference(int*); //prototype

int main()
{
    // declaring a pointer: countPrt is a pointer to a int value, count is not 
    // a pointer. * only applies to first
    int* countPrt, count{0};

    // initialize all pointers to prevent pointing to unknown areas of memory
    cout << "value of count is " << count << endl;
    cout << "value of countPrt is " << countPrt << endl;

    // address operator (&) to obtain the memory address
    // this is deferent than variable reference declaration when & was preceded by
    // data type to pass by reference
    int y{5};
    int* yPrt{nullptr};
    cout << "Value in null pointer is " << yPrt << endl; 
    yPrt = &y; // the address of y
    cout << "address of y (Prt) is " << yPrt << endl;
    // dereferencing operator *
    cout << "the value pointed by Prt (*Prt) is " << *yPrt << endl <<endl;
    // dereferencing an unitialized pointer results in undefined behavior and
    // possible fatal execution-time error. endure pointer is not null

    int a{42};
    int* aPrt = &a;
    cout << "the address of a is " << &a << endl;
    cout << "the value of aPrt is " << aPrt << endl;
    cout << "the value of a is " << a << endl;
    cout << "the value of *aPrt is " << *aPrt << endl << endl;

    int number{10};
    cout << "the original number is " << number << endl;
    cubeByReference(&number);
    cout << "the new number is " << number << endl;

}
// calculate cube a changes variable name in main
void cubeByReference(int* nPrt)
{
    *nPrt = *nPrt * *nPrt * *nPrt;
}