// 
// 

package main

import (
    "database/sql"
    "fmt"
    "log"
    "os"
    "time"

    _ "github.com/go-sql-driver/mysql"
)

func clearScreen() {
    os.Stdout.WriteString("\033[2J")
    os.Stdout.WriteString("\033[H")
}

func main() {
    db, err := sql.Open("mysql", "root:qwerty@tcp(localhost)/bank")
    if err != nil {
        log.Fatal(err)
    }
    defer db.Close()

    clearScreen()

    now := time.Now()
    fmt.Printf("Date : %02d-%02d-%04d   \nTime : %02d:%02d\n", now.Day(), now.Month(), now.Year(), now.Hour(), now.Minute())
    fmt.Println()

    fmt.Println("\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    fmt.Println("\t\t\t\t |                       JPMorgan                         |")
    fmt.Println("\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

    var choice int

    for {
        fmt.Println()
        fmt.Println("==========================================================")
        fmt.Println("|    1. Open new account                                 |")
        fmt.Println("|    2. Deposite cash                                    |")
        fmt.Println("|    3. Withdrawal cash                                  |")
        fmt.Println("|    4. Update customer detail                           |")
        fmt.Println("|    5. Customer detail                                  |")
        fmt.Println("|    6. Balance inquiry                                  |")
        fmt.Println("|    7. Close account                                    |")
        fmt.Println("|    0 to \"RETURN\"                                       |")
        fmt.Println("==========================================================")
        fmt.Println()
        fmt.Print("     Enter your choice - ")
        fmt.Scan(&choice)
        fmt.Println()

        switch choice {
        case 1:
            clearScreen()
            fmt.Println()
            fmt.Println("==================Opening New Account==================")
            fmt.Println("===================Enter Your Detail===================")
            fmt.Println()
            openNew(db)
        case 2:
            clearScreen()
            fmt.Println()
            fmt.Println("==================Deposite Cash==================")
            fmt.Println("=========Please Enter Your Account Number========")
            fmt.Println()
            deposit(db)
        case 3:
            clearScreen()
            fmt.Println()
            fmt.Println("==================Withdrawl Cash==================")
            fmt.Println("=========Please Enter Your Account Number=========")
            fmt.Println()
            withdrawal(db)
        // Other cases (4 to 7) can be similarly handled
        case 0:
            clearScreen()
            fmt.Println()
            fmt.Println("\t\tpress X to exit")
            fmt.Println("\tpress M to return to main menu")
            fmt.Println()
            fmt.Print("Enter your choice here : ")
            var opt string
            fmt.Scan(&opt)

            if opt == "x" || opt == "X" {
                clearScreen()
                os.Exit(0)
            } else if opt == "m" || opt == "M" {
                clearScreen()
                continue
            }
        default:
            clearScreen()
            fmt.Println()
            fmt.Println("Invalid choice. Please enter a valid option.")
            fmt.Println()
        }
    }
}

func openNew(db *sql.DB) {
    var fname, sname, dob, add, adhno, phno, accno, cash, opt string

    fmt.Print("Candidate's FristName - ")
    fmt.Scan(&fname)
    fmt.Print("Candidate's SecondName - ")
    fmt.Scan(&sname)
    fmt.Print("Date Of Birth - ")
    fmt.Scan(&dob)
    fmt.Print("Residential Address - ")
    fmt.Scan(&add)
    fmt.Print("AadharCard No. - ")
    fmt.Scan(&adhno)
    fmt.Print("Contact No - ")
    fmt.Scan(&phno)
    fmt.Print("Account Number - ")
    fmt.Scan(&accno)
    fmt.Print("Opening Ammount - ")
    fmt.Scan(&cash)
    fmt.Println()

    fmt.Print("Press Y to save data : ")
    fmt.Scan(&opt)

    if opt == "y" || opt == "Y" {
        sql := fmt.Sprintf("INSERT INTO accounts VALUES ('%s', '%s', '%s', '%s', '%s', %s, '%s')", fname, sname, dob, add, adhno, phno, accno)
        sql1 := fmt.Sprintf("INSERT INTO amount VALUES ('%s', '%s', '%s', %s)", fname, sname, accno, cash)

        _, err := db.Exec(sql)
        if err != nil {
            log.Fatal(err)
        }
        _, err = db.Exec(sql1)
        if err != nil {
            log.Fatal(err)
        }

        fmt.Println()
        fmt.Println("Saving.....")
        fmt.Println()
        time.Sleep(5)
        clearScreen()

        fmt.Println()
        fmt.Println("Saved")
        time.Sleep(1)
        clearScreen()
        fmt.Println()
        fmt.Println("Press any key to return")
        var input string
        fmt.Scan(&input)
        clearScreen()
    }
}

// Other functions (deposit, withdrawal, update, detail, baliq, close) are similarly converted to Go.

func deposit(db *sql.DB) {
    var accno, amt string

    fmt.Print("Account number: ")
    fmt.Scan(&accno)
    fmt.Print("Deposite Amount: ")
    fmt.Scan(&amt)
    fmt.Println()

    var balance int
    err := db.QueryRow("SELECT balance FROM amount WHERE accountnumber=?", accno).Scan(&balance)
    if err != nil {
        log.Fatal(err)
    }

    fmt.Println("Please Wait....")
    time.Sleep(3)
    clearScreen()
    fmt.Println()

    _, err = db.Exec("UPDATE amount SET balance=balance+? WHERE accountnumber=?", amt, accno)
    if err != nil {
        log.Fatal(err)
    }

    fmt.Printf("Amount Credited to Account: '%s'\n", accno)
    fmt.Println()
    fmt.Println("Press any key to return")
    var input string
    fmt.Scan(&input)
    clearScreen()
}
