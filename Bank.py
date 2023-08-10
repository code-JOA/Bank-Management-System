#pylint: disable=unused-variable
# make sure to have installed all the required node models


from os import system
system('cls')
import mysql.connector
import datetime
now = datetime.datetime.now()
print (now.strftime('Date : '"%d-%m-%Y   \nTime : %H:%M"))
import time
print()

info=mysql.connector.connect(
    host="localhost",
    user="root",
    password="qwerty",
    charset="utf8",
    database="bank",
)



print('\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')
print('\t\t\t\t |                       JPMorgan                          |')
print('\t\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~')

#main function 
def menu():
    print()
    print('1. Open new account')
    print('2. Deposite cash')
    print('3. Withdrawal cash')
    print('4. Update customer detail')
    print('5. Customer detail')
    print('6. Balance inquiry')
    print('7. Close account')
    print('0 to "RETURN"')
    print()

#funtion for opening new account
def opennew():
    
    mycursor = info.cursor()

    fname=input("Candidate's FristName - ")
    sname=input("Candidate's SecondName - ")
    dob=input("Date Of Birth - ")
    add=input("Residential Address - ")
    adhno=input("AadharCard No. - ")
    phno=input("Contact No - ")
    accno=input("Account Number - ")
    cash=input("Opening Ammount - ")
    print()
    
    opt=input('Press Y to save data : ')
    #condition for executing insert command 
    #execute only when user prees y
    if opt=='y':      
    
        sql="insert into accounts values('"+fname+"','"+sname+"','"+dob+"','"+add+"','"+adhno+"',"+phno+",'"+accno+"')"
        sql1="insert into amount values('"+fname+"','"+sname+"','"+accno+"',"+cash+")"
        
        mycursor.execute(sql)
        mycursor.execute(sql1)
        
        #commit method for updateing changes in sql database 
        info.commit()
        info.close()
        
        print()
        print('Saving.....')
        print()
        #time sleep method for some delay 
        time.sleep(5)
        system('cls')
        
        print()
        print('Saved')
        time.sleep(1)
        system('cls')
        print()
        print('press any key to return')
        opt=input('')
        system('cls')
        #if opt=='r':
        menu()
        system('cls')
        print()

#Cash deposite Function 
def depo():

    info=mysql.connector.connect(
    host="localhost",
    user="root",
    password="qwerty",
    charset="utf8",
    database="bank",
    )

    mycursor = info.cursor()

    accno=input('Acount number : ')
    amt=input('Deposite Amount : ')

    mycursor.execute("select balance from amount where accountnumber='"+accno+"'")
    myresult=mycursor.fetchall()

    print()
    print('Please Wait....')
    time.sleep(3)
    system('cls')
    print()

    sql="update amount set balance=balance+'"+amt+"' where accountnumber='"+accno+"'"
    mycursor.execute(sql)
    info.commit()
    info.close()
    print("Amount Credited to Account :'"+accno+"'")
    print()
    print('press any key to return')
    opt=input('')
    system('cls')
    #if opt=='r':
    menu()
    system('cls')
    print()

#cash withdrawal function 
def withdrawl():

    info=mysql.connector.connect(
    host="localhost",
    user="root",
    password="qwerty",
    charset="utf8",
    database="bank",
    )

    mycursor = info.cursor()

    accno=input('Acount number : ')
    amt=input('Withdrawal Amount : ')

    mycursor.execute("select balance from amount where accountnumber='"+accno+"'")
    myresult=mycursor.fetchall()

    print()
    print('Please Wait....')
    time.sleep(3)
    system('cls')
    print()

    sql="update amount set balance=balance-'"+amt+"' where accountnumber='"+accno+"'"
    mycursor.execute(sql)
    info.commit()
    info.close()
    print("Amount Ddebited From Account : '"+accno+"'")

    print('press any key to return')
    opt=input('')
    system('cls')
    #if opt=='r':
    menu()
    system('cls')
    print()

#update function declaretion    
def update():

    info=mysql.connector.connect(
    host="localhost",
    user="root",
    password="qwerty",
    charset="utf8",
    database="bank",
    )

    mycursor=info.cursor()
    
    accno=input('Enter account number : ')
    print()
    mycursor.execute("select firstname,secondname,contactno,residentialaddress from accounts where accountnumber='"+accno+"'")
    myresult=mycursor.fetchall()

    system('cls')

    for x in myresult:   
        print("FristName - ",x[0])
        print("SecondName - ",x[1])
        print("Residential Address - ",x[2])
        print("Contact No - ",x[3])
        print()
    

        print('a. Update Name')
        print('b. Update Residential Address')
        print('c. Update Contact Number')
        print()                                                                             

        opt=input('Enter a,b,c according changes :')
        print()
        
        if opt=='a':
            fname=input('Enter New Frist Name : ')
            sname=input('Enter New Second Name : ')
            sql=("update accounts set secondname='"+sname+"' where accountnumber='"+accno+"'" )
            sql1=("update amount set secondname='"+sname+"' where accountnumber='"+accno+"'" )
            mycursor.execute(sql)
            mycursor.execute(sql1)
            info.commit()
            info.close()
            print()
            print('Changes Done')
            
            print()
            print('Prees u to return on update menu')
            print('Prees r to return on main menu')    
            print()
            
            opt=input('Enter your choice here : ')

            if opt=="u":
                update()
            elif opt=="r": 
                menu()
                system('cls')
