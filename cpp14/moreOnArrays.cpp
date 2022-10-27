// static array initialization and automatic array initialization.
#include <iostream>
#include <array>
using namespace std;

void staticArrayInit(); // function prototype
void automaticArrayInit(); // function prototype
const size_t arraySize{3};

int main() {
   cout << "First call to each function:\n";
   staticArrayInit();
   automaticArrayInit();

   cout << "\n\nSecond call to each function:\n";
   staticArrayInit();
   automaticArrayInit();
   cout << endl;
}

// function to demonstrate a static local array
void staticArrayInit(void) 
{   // static local variable: exists for the program duration but only 
    // visible in the function body. 
    // static: initializes elements to 0 first time function is called  
    // this is not the case for other local variables
    static array<int, arraySize> array1; // static local array

    cout << "\nValues on entering staticArrayInit:\n";

    // output contents of array1
    for (size_t i{0}; i < array1.size(); ++i) {
       cout << "array1[" << i << "] = " << array1[i] << "  ";
    }

    cout << "\nValues on exiting staticArrayInit:\n";

    // modify and output contents of array1
    for (size_t j{0}; j < array1.size(); ++j) {
       cout << "array1[" << j << "] = " << (array1[j] += 5) << "  ";
    }
}

// function to demonstrate an automatic local array
void automaticArrayInit(void) {
    // initializes elements each time function is called 
    // local variables are sometimes called automatic variables bc they are 
    // automatically destroyed when the function finishes executing                 
    array<int, arraySize> array2{1, 2, 3}; // automatic local array
    int cnt{0};

    cout << "\n\nValues on entering automaticArrayInit:\n";

    // range-based for statement
    for (int item : array2)
    {
        cout << "array2[" << cnt++ << "] = " << item << "  ";
        //cnt++;
    }

    cout << "\nValues on exiting automaticArrayInit:\n";

    cnt=0;
    // range based for to modify array, 
    for (int& itemRef : array2)
    {
        itemRef += 5;
        cout << "array2[" << cnt << "] = " << array2[cnt++] << "  ";
    }

}
