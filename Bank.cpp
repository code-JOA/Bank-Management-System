// 

// 

#include <iostream>
#include <mysql/mysql.h>
#include <ctime>
#include <unistd.h>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[H";
}

int main() {
    MYSQL* conn = mysql_init(nullptr);
    if (conn == nullptr) {
        cerr << "mysql_init() failed" << endl;
        return 1;
    }

    if (mysql_real_connect(conn, "localhost", "root", "qwerty", "bank", 0, nullptr, 0)
    == nullptr) {
        cerr << "mysql_real_connect() failed" << endl;
        return 1;
    }

    clearScreen();

    time_t now = time(nullptr);
    tm* currentTime = localtime(&now);
    cout << "Date : " << currentTime->tm_mday << "-" << (currentTime->tm_mon + 1) << "-" 
    << (currentTime->tm_year + 1900) << endl;
    cout << "Time : " << currentTime->tm_hour << ":" << currentTime->tm_min << endl;
    cout << endl;

    cout << "\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "\t\t\t\t |                       JPMorgan                           |" << endl;
    cout << "\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    int choice;

    while (true) {
        cout << endl;
        cout << "==========================================================\n";
        cout << "|    1. Open new account                                 |\n";
        cout << "|    2. Deposit cash                                    |\n";
        cout << "|    3. Withdraw cash                                  |\n";
        cout << "|    4. Update customer detail                           |\n";
        cout << "|    5. Customer detail                                  |\n";
        cout << "|    6. Balance inquiry                                  |\n";
        cout << "|    7. Close account                                    |\n";
        cout << "|    0 to \"RETURN\"                                       |\n";
        cout << "==========================================================\n";
        cout << endl;
        cout << "     Enter your choice - ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                clearScreen();
                cout << endl;
                cout << "==================Opening New Account==================" << endl;
                cout << "===================Enter Your Detail===================" << endl;
                cout << endl;
                // Call openNew() function
                break;
            case 2:
                clearScreen();
                cout << endl;
                cout << "==================Deposite Cash==================" << endl;
                cout << "=========Please Enter Your Account Number========" << endl;
                cout << endl;
                // Call deposit() function
                break;
            case 3:
                clearScreen();
                cout << endl;
                cout << "==================Withdrawl Cash==================" << endl;
                cout << "=========Please Enter Your Account Number=========" << endl;
                cout << endl;
                // Call withdrawal() function
                break;
            // Other cases (4 to 7) can be similarly handled
            case 0:
                clearScreen();
                cout << endl;
                cout << "\t\tpress X to exit" << endl;
                cout << "\tpress M to return to main menu" << endl;
                cout << endl;
                cout << "Enter your choice here : ";
                char opt;
                cin >> opt;

                if (opt == 'x' || opt == 'X') {
                    clearScreen();
                    mysql_close(conn);
                    return 0;
                } else if (opt == 'm' || opt == 'M') {
                    clearScreen();
                    continue;
                }
            default:
                clearScreen();
                cout << endl;
                cout << "Invalid choice. Please enter a valid option." << endl;
                cout << endl;
        }
    }

    mysql_close(conn);
    return 0;
}

// Define other functions (openNew, deposit, withdrawal, etc.) similarly
