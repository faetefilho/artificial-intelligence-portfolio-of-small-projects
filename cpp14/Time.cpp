#include <iomanip>
#include <stdexcept>
#include <sstream>
#include <string>
// to indicate that the member func in Time.cpp are part of class time
#include "Time.h" // include definition of class Time.h

using namespace std;

// Time constructor initializes each data member
Time::Time(int hour, int minute, int second)
{
    setTime(hour, minute, second);
}
// the scope resolution now ties the Time.h class definition
// to its implementation. 
void Time::setTime(int h, int m, int s) //set new time value
{
    if ((h >= 0 && h < 24) && (m >= 0 && m < 60) && (s >= 0 && s < 60)) {
        hour = h;
        minute = m;
        second = s;
    }
    else {
        throw invalid_argument(
        "hour, minute and/or second was out of range");
    }
}

// return time as a string
// when defining a class member function outside that class, omitting the
// class name and scope resolution operator :: is compilation error
string Time::toUniversalString() const {
    ostringstream output;
    output << setfill('0') << setw(2) << hour << ":" << setw(2) 
    << minute << ":" << setw(2) << second;
    return output.str();
}
// const keyword must appear on both func prototype and definition
string Time::toStandardString() const {
    // objects of the class ostringstream, from <sstream>, provide same functionality
    // as cout but write their output to string objects in memory
    ostringstream output;
    // setfill is a sticky value, setw is not (applies only to next)
    output << ((hour == 0 || hour == 12) ? 12 : hour % 12) << ":"
        << setfill('0') << setw(2) << minute << ":" << setw(2)
        << second << (hour < 12 ? " AM" : " PM");
    return output.str(); // returns the formatted string
}
