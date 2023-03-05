# include <iostream>

using namespace std;

int main ()
{   
    //create a character array to store the name

    char name[20];
    
    cout << "Enter your name: ";
    cin >> name;

    cout << "Hello, " << name << "!!!" << endl;

    return 0;
}