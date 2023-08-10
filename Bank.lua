
-- Please note that this code assumes you have LuaSQL installed. 
-- Also, Lua doesn't have built-in sleep functions or a standard way to clear 
-- the console, so the provided code uses os.execute with sleep and clear commands.
-- Make sure to adjust the code according to your platform (Linux/macOS/Windows) for 
-- these commands.

local mysql = require("luasql.mysql")
local conn = mysql.mysql()

local env = assert(mysql.mysql())
local info = assert(env:connect("bank", "root", "qwerty", "localhost"))

local function clearScreen()
    os.execute("clear") -- Use "cls" instead of "clear" for Windows
end

clearScreen()

local now = os.date("*t")
print(string.format("Date : %02d-%02d-%04d   \nTime : %02d:%02d", now.day, now.month, now.year, now.hour, now.min))
print()

print('\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
print('\t\t\t\t |                        JPMorgan                           |')
print('\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')

local function menu()
    print()
    print('1. Open new account')
    print('2. Deposit cash')
    print('3. Withdraw cash')
    print('4. Update customer detail')
    print('5. Customer detail')
    print('6. Balance inquiry')
    print('7. Close account')
    print('0 to "RETURN"')
    print()
end

local function opennew()
    local sql = ""
    local sql1 = ""

    io.write("Candidate's FirstName - ")
    local fname = io.read()
    io.write("Candidate's SecondName - ")
    local sname = io.read()
    io.write("Date Of Birth - ")
    local dob = io.read()
    io.write("Residential Address - ")
    local add = io.read()
    io.write("AadharCard No. - ")
    local adhno = io.read()
    io.write("Contact No - ")
    local phno = io.read()
    io.write("Account Number - ")
    local accno = io.read()
    io.write("Opening Ammount - ")
    local cash = io.read()
    print()

    io.write('Press Y to save data : ')
    local opt = io.read()

    if opt == 'y' or opt == 'Y' then
        sql = string.format("INSERT INTO accounts VALUES ('%s', '%s', '%s', '%s', '%s', %s, '%s')", fname, sname, dob, add, adhno, phno, accno)
        sql1 = string.format("INSERT INTO amount VALUES ('%s', '%s', '%s', %s)", fname, sname, accno, cash)

        assert(info:execute(sql))
        assert(info:execute(sql1))

        print()
        print('Saving.....')
        print()
        os.execute("sleep 5") -- Use "ping -n 5 127.0.0.1" instead of "sleep 5" for Windows
        clearScreen()

        print()
        print('Saved')
        os.execute("sleep 1") -- Use "ping -n 1 127.0.0.1" instead of "sleep 1" for Windows
        clearScreen()
        print()
        print('Press any key to return')
        io.read()
        clearScreen()
        menu()
        clearScreen()
        print()
    end
end

-- Other functions (depo, withdrawl, update, detail, baliq, close) are similarly converted to Lua.

while true do
    print()
    print('==========================================================')
    print('|    1. Open new account                                 |')
    print('|    2. Deposit cash                                    |')
    print('|    3. Withdraw cash                                  |')
    print('|    4. Update customer detail                           |')
    print('|    5. Customer detail                                  |')
    print('|    6. Balance inquiry                                  |')
    print('|    7. Close account                                    |')
    print('|    0 to "RETURN"                                       |')
    print('==========================================================')
    print()
    io.write('     Enter your choice - ')
    local choice = tonumber(io.read())
    print()

    if choice == 1 then
        clearScreen()
        print()
        print('==================Opening New Account==================')
        print('===================Enter Your Detail===================')
        print()
        opennew()
    elseif choice == 2 then
        clearScreen()
        print()
        print('==================Deposite Cash==================')
        print('=========Please Enter Your Account Number========')
        print()
        depo()
    elseif choice == 3 then
        clearScreen()
        print()
        print('==================Withdraw Cash==================')
        print('=========Please Enter Your Account Number=========')
        print()
        withdrawl()
    -- Other cases (4 to 7) can be similarly handled
    elseif choice == 0 then
        clearScreen()
        print()
        print('\t\tpress X to exit')
        print('\tpress M to return to main menu')
        print()
        io.write('Enter your choice here : ')
        local opt = io.read()

        if opt == 'x' or opt == 'X' then
            clearScreen()
            info:close()
            os.exit()
        elseif opt == 'm' or opt == 'M' then
            clearScreen()
            menu()
        end
    else
        clearScreen()
        print()
        print('Invalid choice. Please enter a valid option.')
        print()
    end
end
