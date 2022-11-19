// This program test class time
#include <iostream>
#include <stdexcept> //invalid arg exception class
#include "Time.h" //definition of class time from time.h
using namespace std;

// display time
void displayTime(const string& message, const Time& time)
{
    cout << message << "\nUniversal time: " << time.toUniversalString()
    << "\nStandard time: " << time.toStandardString() << "\n\n";
}

int main()
{
    // class t does not have a constructor, initialized according to class
    // time definition
    Time t; // instantiate object t of class Time

    displayTime("Initial time:", t);
    t.setTime(13, 27, 6);

    displayTime("After Settime:", t);

    try // attemp to use invalid numbers
    {
        t.setTime(99, 99, 99);
    }
    catch(invalid_argument& e)
    {
        cout << "Exception: " << e.what() << "\n\n";      
    }

    displayTime("After attempting to set an invalid time:", t);

    Time t2{2};
    Time t3{21, 34};
    Time t4{12, 25, 42};

    cout << "\nConstructd with:\n\n";
    displayTime("t2: hour specified, other default", t2);
    displayTime("t3: hour/minute specified, other default", t3);
    displayTime("t4: hour/minute/second specified, other default", t4);


}