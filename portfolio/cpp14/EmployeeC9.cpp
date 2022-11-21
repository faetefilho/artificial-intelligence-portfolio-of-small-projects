// Employee class member-function definitions.
#include <iostream>
#include "EmployeeC9.h" // Employee class definition 
using namespace std;

// define and initialize static data member at global namespace scope
// The static keyword cannot be applied to a memeber definition that appears
// outside a class definition
unsigned int Employee::count{0}; // cannot include keyword static

// define static member function that returns number of         
// Employee objects instantiated (declared static in EmployeeC9.h)
// The static keyword cannot be applied to a memeber definition that appears
// outside a class definition
unsigned int Employee::getCount() { return count; }

// constructor initializes non-static data members and 
// increments static data member count
Employee::Employee(const string& first, const string& last)
    : firstName(first), lastName(last) {
    ++count; // increment static count of employees
    cout << "Employee constructor for " << firstName
        << ' ' << lastName << " called." << endl;
}

// destructor decrements the count
Employee::~Employee() {
    cout << "~Employee() called for " << firstName
        << ' ' << lastName << endl;
    --count; // decrement static count of employees
}

// return first name of employee
string Employee::getFirstName() const { return firstName; }

// return last name of employee
string Employee::getLastName() const { return lastName; }