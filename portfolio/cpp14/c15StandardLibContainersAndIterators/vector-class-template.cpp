#include <iostream>
#include <vector>
using namespace std;

// vector: continuous memory allocation, most commonly used when data needs must be easily acceible
// and number of elements needs to grow and shrink dynamically
// choose vector for the best random access performance in a container that needs to grow

// prototype for function template printVector
template <typename T> void printVector(const vector<T>& integers2);

int main() {
    vector<int> integers; // create vector of ints, 0 elements, 0 capacity

    cout << "The initial size of integers is: " << integers.size()
        << "\nThe initial capacity of integers is: " << integers.capacity(); //return the number of elements that can be held in currently allocated storage

    // function push_back is in vector, deque and list
    // push_back adds a new element at the end of the vector, after its current last element
    integers.push_back(2);                            
    integers.push_back(3);                            
    integers.push_back(4);                            

    cout << "\nThe size of integers is: " << integers.size()
        << "\nThe capacity of integers is: " << integers.capacity();
    cout << "\n\nOutput built-in array using pointer notation: ";
    const size_t SIZE{6}; // define array size
    int values[SIZE]{1, 2, 3, 4, 5, 6}; // initialize values

    // display array using pointer notation
    for (const int* ptr = cbegin(values); ptr != cend(values); ++ptr) {
        cout << *ptr << ' ';
    }

    cout << "\nOutput vector using iterator notation: ";
    printVector(integers);
    cout << "\nReversed contents of vector integers: ";

    // display vector in reverse order using const_reverse_iterator
    for (auto reverseIterator = integers.crbegin();               
        reverseIterator != integers.crend(); ++reverseIterator) {    
        cout << *reverseIterator << ' ';                            
    }                                                              

    cout << endl;
}

// function template for outputting vector elements  
template <typename T> void printVector(const vector<T>& integers2) {
    // display vector elements using const_iterator         
    for (auto constIterator = integers2.cbegin();            
        constIterator != integers2.cend(); ++constIterator) {
        cout << *constIterator << ' ';                       
    }                                                       
}
