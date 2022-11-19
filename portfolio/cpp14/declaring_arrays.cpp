#include <iostream>
#include <iomanip>
#include <array>
using namespace std;

int main() 
{   
    // non-static local variables are not implicitly initialized to zero
    array<int, 5> n; // n is an array of 5 int values
    // declaring with initializer list
    array<int, 6> n2{23, 43, 54, 54, 43, 54};
    // fewer initializers than array elements => initialize to zero
    array<int, 4> n3{};  // initalize all elements to zero
    // constant variable can be used to specify array size
    // constant vars must be initialized when declared and cannot be modified
    const size_t arraySize{5};  //must initialize in declaration
    array<int, arraySize> values;

    // initialize elements of array n to 0 
    // size_t represents unsigned integral type, recommended for elements that
    // represents arrays size/subscript, add #include <cstddef> if getting errors       
    for (size_t i{0}; i < n.size(); ++i) {
        n[i] = 0; // set element at location i to 0
    }

    cout << "Element" << setw(10) << "Value" << endl;

    // output each array element's value                
    for (size_t j{0}; j < n.size(); ++j) {
        cout << setw(7) << j << setw(10) << n[j] << endl;
    }

    cout << "Element" << setw(10) << "Value" << endl;

    // output each array element's value                
    for (size_t j{0}; j < n2.size(); ++j) {
        cout << setw(7) << j << setw(10) << n2[j] << endl;
    }
}