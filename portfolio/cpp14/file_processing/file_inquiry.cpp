#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

// function prototypes
enum class RequestType {
    ZERO_BALANCE = 1, CREDIT_BALANCE, DEBIT_BALANCE, END
};

RequestType getRequest();
bool shouldDisplay(RequestType, double);
void outputLine(int, const string &, double);

int main(){
    // create ifstream object for file client.txt
    ifstream inClientFile{"clients.txt", ios::in};

    // exit program if ifstream cannot open file
    if (!inClientFile) {
        cerr << "File could not be opened" << endl;
        exit(EXIT_FAILURE);
    }

    // get user's request
    RequestType request{getRequest()};

    // process user's request
    while (request != RequestType::END) {
        // process user's request
        switch (request) {
            case RequestType::ZERO_BALANCE:
                cout << "\nAccounts with zero balances:"
                        << endl;
                break;
            case RequestType::CREDIT_BALANCE:
                cout << "\nAccounts with credit balances:"
                        << endl;
                break;
            case RequestType::DEBIT_BALANCE:
                cout << "\nAccounts with debit balances:"
                        << endl;
                break;
            case RequestType::END:
                cout << "\nEnd of run." << endl;
                break;
        }

        int account;
        string name;
        double balance;

        // read account, name and balance from file (first record)
        inClientFile >> account >> name >> balance;

        // display header
        cout << left << setw(10) << "Account" << setw(13) << "Name" << "Balance" << endl;

        // displays file contents (until eof)
        while (!inClientFile.eof()) {
            // display record
            if (shouldDisplay(request, balance)) {
                outputLine(account, name, balance);
            }

            // read account, name and balance from file
            inClientFile >> account >> name >> balance;
        }

        inClientFile.clear(); // reset end-of-file indicator for next request
        inClientFile.seekg(0); // position to beginning of file for next request
        request = getRequest(); // get next request
    }

    cout << "End of run." << endl;

}

// get user's request
RequestType getRequest(){
    // display request options
    cout << "\nEnter request" << endl
            << " 1 - List accounts with zero balances" << endl
            << " 2 - List accounts with credit balances" << endl
            << " 3 - List accounts with debit balances" << endl
            << " 4 - End of run" << endl << "? ";

    int request;

    do {
        // input user's request
        cin >> request;
    } while (request < static_cast<int>(RequestType::ZERO_BALANCE) || request > static_cast<int>(RequestType::END));

    // return static_cast<RequestType>(request);
    return static_cast<RequestType>(request);
}

// determine if account should be displayed
bool shouldDisplay(RequestType request, double balance){
    // determine if account should be displayed
    if ((request == RequestType::ZERO_BALANCE && balance == 0) ||
            (request == RequestType::CREDIT_BALANCE && balance < 0) ||
            (request == RequestType::DEBIT_BALANCE && balance > 0)) {
        return true;
    } else {
        return false;
    }
}

// display single record from file
void outputLine(int account, const string &name, double balance){
    cout << left << setw(10) << account << setw(13) << name << setw(7) << setprecision(2) << right << fixed << showpoint << balance << endl;
}