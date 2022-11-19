#include <iostream>
using namespace std;
// 
// Count class definition 
class Count 
{
    friend void setX(Count&, int); // friend declaration
public:
    int getX() const { return x; }
private:
    int x{0}; 
};
// setX is a standalone global function of class count, it isnt a member
// function of class count
// function setX can modify private data of Count         
// because setX is declared as a friend of Count (line 8)
void setX(Count& c, int val) 
{
    c.x = val; // allowed because setX is a friend of Count
}

int main() {

    Count counter; // create Count object

    cout << "counter.x after instantiation: " << counter.getX() << endl;
    // allowed to access private data member x bc is friend
    setX(counter, 8); // set x using a friend function
    cout << "counter.x after call to setX friend function: "
        << counter.getX() << endl;
    // counter.setX(8) is an error as setX is not a member function
}
