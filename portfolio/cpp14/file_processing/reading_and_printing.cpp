#include <iostream>
#include <fstream> // file stream
#include <iomanip> // parameterized stream manipulators
#include <string>
#include <cstdlib> // exit function prototype
using namespace std;

void outputLine( int, const string &, double ); // prototype

int main()
{
    // ifstream constructor opens the file
    ifstream inClientFile( "clients.txt", ios::in );

    // exit program if ifstream could not open file
    if ( !inClientFile )  // overloaded ! operator
    {
        cerr << "File could not be opened" << endl;
        exit( 1 );
    } // end if

    cout << left << setw( 10 ) << "Account" << setw( 13 )
        << "Name" << "Balance" << endl;

    int account;
    string name;
    double balance;

    // read account, name and balance from file
    // eof function returns true when the end-of-file
    // character is read from the input or when the
    // end-of-file indicator is set for the stream
    while ( inClientFile >> account >> name >> balance )
    {
        // display record
        outputLine( account, name, balance );
    } // end while
    return 0;
} // end main

    void outputLine( int account, const string &name, double balance )
    {
        cout << left << setw( 10 ) << account << setw( 13 ) << name
            << setw( 7 ) << setprecision( 2 ) << right << balance << endl;
    } // end function outputLine

