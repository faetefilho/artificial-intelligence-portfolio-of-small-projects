// get put and eof member functions
# include <iostream>
using namespace std;

int main()
{
    int character; // use int because char cannot represent EOF

    // prints the value of EOF

    cout << "EOF in this system is: " << EOF << endl;
    
    // prompt user to enter line of text
   cout << "Before input, cin.eof() is " << cin.eof()
      << "\nEnter a sentence followed by Enter and end-of-file:\n";

   // use get to read each character; use put to display it
   while ((character = cin.get()) != EOF) {
      cout.put(character);
   }

   // display end-of-file character
   cout << "\nEOF in this system is: " << character
      << "\nAfter input of EOF, cin.eof() is " << cin.eof() << endl;
}