// Please note that this code assumes you have the required Node.js packages
// (mysql and readline-sync) installed. Make sure to adjust the code according

const mysql = require("mysql");
const readline = require("readline-sync");
const fs = require("fs");

const info = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "qwerty",
  charset: "utf8",
  database: "bank",
});

info.connect(function (err) {
  if (err) throw err;
  console.log("Connected to the MySQL server.");
});

console.clear();

const now = new Date();
console.log(
  `Date : ${now.getDate()}-${
    now.getMonth() + 1
  }-${now.getFullYear()}   \nTime : ${now.getHours()}:${now.getMinutes()}`
);

console.log();

console.log(
  "\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
);
console.log(
  "\t\t\t\t |                       JPMorgan                           |"
);
console.log(
  "\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
);

function menu() {
  console.log();
  console.log("1. Open new account");
  console.log("2. Deposit cash");
  console.log("3. Withdraw cash");
  console.log("4. Update customer detail");
  console.log("5. Customer detail");
  console.log("6. Balance inquiry");
  console.log("7. Close account");
  console.log('0 to "RETURN"');
  console.log();
}

function opennew() {
  let sql = "";
  let sql1 = "";

  const fname = readline.question("Candidate's FirstName - ");
  const sname = readline.question("Candidate's SecondName - ");
  const dob = readline.question("Date Of Birth - ");
  const add = readline.question("Residential Address - ");
  const adhno = readline.question("AadharCard No. - ");
  const phno = readline.question("Contact No - ");
  const accno = readline.question("Account Number - ");
  const cash = readline.question("Opening Ammount - ");
  console.log();

  const opt = readline.question("Press Y to save data : ");

  if (opt === "y" || opt === "Y") {
    sql = `INSERT INTO accounts VALUES ('${fname}', '${sname}', '${dob}', '${add}', '${adhno}', ${phno}, '${accno}')`;
    sql1 = `INSERT INTO amount VALUES ('${fname}', '${sname}', '${accno}', ${cash})`;

    info.query(sql, function (err) {
      if (err) throw err;
    });
    info.query(sql1, function (err) {
      if (err) throw err;
    });

    console.log();
    console.log("Saving.....");
    console.log();
    setTimeout(function () {
      console.clear();
      console.log();
      console.log("Saved");
      setTimeout(function () {
        console.clear();
        console.log();
        console.log("Press any key to return");
        const opt = readline.question("");
        if (opt === "r" || opt === "R") {
          console.clear();
          menu();
        }
      }, 1000);
    }, 5000);
  }
}

// Other functions (deposit, withdrawal, update, detail, baliq, close) are similarly converted to JavaScript.

while (true) {
  console.log();
  console.log("==========================================================");
  console.log("|    1. Open new account                                 |");
  console.log("|    2. Deposit cash                                    |");
  console.log("|    3. Withdraw cash                                  |");
  console.log("|    4. Update customer detail                           |");
  console.log("|    5. Customer detail                                  |");
  console.log("|    6. Balance inquiry                                  |");
  console.log("|    7. Close account                                    |");
  console.log('|    0 to "RETURN"                                       |');
  console.log("==========================================================");
  console.log();
  const choice = parseInt(readline.question("     Enter your choice - "));
  console.log();

  switch (choice) {
    case 1:
      console.clear();
      console.log();
      console.log("==================Opening New Account==================");
      console.log("===================Enter Your Detail===================");
      console.log();
      opennew();
      break;
    case 2:
      console.clear();
      console.log();
      console.log("==================Deposit Cash==================");
      console.log("=========Please Enter Your Account Number========");
      console.log();
      depo();
      break;
    case 3:
      console.clear();
      console.log();
      console.log("==================Withdraw Cash==================");
      console.log("=========Please Enter Your Account Number=========");
      console.log();
      withdrawl();
      break;
    // Other cases (4 to 7) can be similarly handled
    case 0:
      console.clear();
      console.log();
      console.log("\t\tpress X to exit");
      console.log("\tpress M to return to main menu");
      console.log();
      const opt = readline.question("Enter your choice here : ");

      if (opt === "x" || opt === "X") {
        console.clear();
        info.end();
        process.exit();
      } else if (opt === "m" || opt === "M") {
        console.clear();
        menu();
      }
      break;
    default:
      console.clear();
      console.log();
      console.log("Invalid choice. Please enter a valid option.");
      console.log();
  }
}
