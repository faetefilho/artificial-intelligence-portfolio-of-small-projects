// member function are defined in Time.cpp
#include <string>

// include guard to prevent from including header more than once
// By convenction use name of the header file in uppercase with 
// period replaced by _
#ifndef TIME_H
#define TIME_H

// Time class definition
// contains function prototype to describe the class public interface without
// revealing the member functions implementations
class Time
{
    public:
        //default constructor
        explicit Time(int = 0, int = 0, int = 0);
        
        void setTime(int, int, int);
        // const member function: this function should not modify the object
        // on which it is called (comp. error)
        std::string toUniversalString() const;
        std::string toStandardString() const;
    private:
        unsigned int hour{0};
        unsigned int minute{0};
        unsigned int second{0};
};

#endif