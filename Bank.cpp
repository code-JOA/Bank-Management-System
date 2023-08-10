// 
Please note that you will need to have the MySQL C API library installed and properly 
configured in your C++ development environment. Also, the code provided above only 
includes the structure and flow. You need to define the individual functions (openNew,
 deposit, withdrawal, etc.) and their functionality according to the original Python code. 
 The input/output in C++ is done using cin and cout. 
Adjustments can be made based on your specific requirements and MySQL configuration.
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
                cout << "==================Deposit Cash==================" << endl;
                cout << "=========Please Enter Your Account Number========" << endl;
                cout << endl;
                // Call deposit() function
                break;
            case 3:
                clearScreen();
                cout << endl;
                cout << "==================Withdraw Cash==================" << endl;
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


using namespace std;

void clearScreen() {
    cout << "\033[2J\033[H";
}

// Define openNew function
void openNew(MYSQL* conn) {
    string fname, sname, dob, add, adhno, phno, accno, cash;
    cout << "Candidate's FirstName - ";
    cin >> fname;
    cout << "Candidate's SecondName - ";
    cin >> sname;
    cout << "Date Of Birth - ";
    cin >> dob;
    cout << "Residential Address - ";
    cin.ignore();
    getline(cin, add);
    cout << "AadharCard No. - ";
    cin >> adhno;
    cout << "Contact No - ";
    cin >> phno;
    cout << "Account Number - ";
    cin >> accno;
    cout << "Opening Amount - ";
    cin >> cash;

    cout << endl;
    char opt;
    cout << "Press Y to save data: ";
    cin >> opt;

    if (opt == 'y' || opt == 'Y') {
        string sql = "INSERT INTO accounts VALUES('" + fname + "','" + sname + "','" + dob + "','" + add + "','" + adhno + "'," + phno + ",'" + accno + "')";
        string sql1 = "INSERT INTO amount VALUES('" + fname + "','" + sname + "','" + accno + "'," + cash + ")";

        if (mysql_query(conn, sql.c_str()) != 0 || mysql_query(conn, sql1.c_str()) != 0) {
            cerr << "Failed to execute SQL query" << endl;
            return;
        }

        cout << endl;
        cout << "Saving....." << endl;
        sleep(5);
        clearScreen();

        cout << endl;
        cout << "Saved" << endl;
        sleep(1);
        clearScreen();
        cout << endl;
        cout << "Press any key to return";
        cin.ignore();
    }
}

// Define deposit function
void deposit(MYSQL* conn) {
    string accno, amt;
    cout << "Account number: ";
    cin >> accno;
    cout << "Deposit Amount: ";
    cin >> amt;

    string selectQuery = "SELECT balance FROM amount WHERE accountnumber='" + accno + "'";
    if (mysql_query(conn, selectQuery.c_str()) != 0) {
        cerr << "Failed to execute SQL query" << endl;
        return;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    string currentBalance = row[0];

    cout << endl;
    cout << "Please Wait...." << endl;
    sleep(3);
    clearScreen();
    cout << endl;

    string updateQuery = "UPDATE amount SET balance=balance+'" + amt + "' WHERE accountnumber='" + accno + "'";
    if (mysql_query(conn, updateQuery.c_str()) != 0) {
        cerr << "Failed to execute SQL query" << endl;
        return;
    }

    cout << "Amount Credited to Account: '" << accno << "'" << endl;
    cout << endl;
    cout << "Press any key to return";
    cin.ignore();
}

// Define withdrawCash function
void withdrawCash(MYSQL* conn) {
    string accno, amt;
    cout << "Account number: ";
    cin >> accno;
    cout << "Withdrawal Amount: ";
    cin >> amt;

    string selectQuery = "SELECT balance FROM amount WHERE accountnumber='" + accno + "'";
    if (mysql_query(conn, selectQuery.c_str()) != 0) {
        cerr << "Failed to execute SQL query" << endl;
        return;
    }
    
    MYSQL_RES* result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    string currentBalance = row[0];

    cout << endl;
    cout << "Please Wait...." << endl;
    sleep(3);
    clearScreen();
    cout << endl;

    string updateQuery = "UPDATE amount SET balance=balance-'" + amt + "' WHERE accountnumber='" + accno + "'";
    if (mysql_query(conn, updateQuery.c_str()) != 0) {
        cerr << "Failed to execute SQL query" << endl;
        return;
    }

    cout << "Amount Debited From Account: '" << accno << "'" << endl;
    cout << endl;
    cout << "Press any key to return";
    cin.ignore();
}

int main() {
    MYSQL* conn = mysql_init(nullptr);
    if (conn == nullptr) {
        cerr << "mysql_init() failed" << endl;
        return 1;
    }

    if (mysql_real_connect(conn, "localhost", "root", "qwerty", "bank", 0, nullptr, 0) == nullptr) {
        cerr << "mysql_real_connect() failed" << endl;
        return 1;
    }

    // Rest of the main function remains the same

    mysql_close(conn);
    return 0;
}
