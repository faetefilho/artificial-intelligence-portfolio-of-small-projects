# include <iostream>
# include <fstream>
# include <string>
# include <cstdlib>
using namespace std;

int main()
{
    // create ofstream object, ofstream constructor opens file
    // ios::out is the default mode for ofstream
    ofstream outClientFile( "clients.txt", ios::out );

    // exit program if ofstream could not open file
    if ( !outClientFile )   // overloaded ! operator
    {
        cerr << "File could not be opened" << endl;
        exit( 1 );
    } // end if

    cout << "Enter the account, name, and balance." << endl
        << "Enter end-of-file to end input." << endl << "? ";

    int account;
    string name;
    double balance;

    // read account, name and balance from user
    // overloaded >> operator, return bool value
    while ( cin >> account >> name >> balance )
    {
        // write account, name and balance to file
        outClientFile << account << ' ' << name << ' ' << balance << endl;
        cout << "? ";
    } // end while

    return 0;
} // end main