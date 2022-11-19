// Using the this pointer to refer to object members.
#include <iostream>
using namespace std;

class Test 
{
    public:
        explicit Test(int);
        void print() const;
    private:
        int x{0};
};

// constructor
Test::Test(int value) : x{value} {} // initialize x to value

// print x using implicit then explicit this pointers;
// the parentheses around *this are required
void Test::print() const {
    // implicitly use the this pointer to access the member x
    cout << "        x = " << x;

    // explicitly use the this pointer and the arrow operator
    // to access the member x                                
    cout << "\n  this->x = " << this->x;

    // explicitly use the dereferenced this pointer and
    // the dot operator to access the member x 
    // parenthesis are required bc the dor operator has preference        
    cout << "\n(*this).x = " << (*this).x << endl;
}

int main() {
    Test testObject{12}; // instantiate and initialize testObject
    testObject.print();
}
