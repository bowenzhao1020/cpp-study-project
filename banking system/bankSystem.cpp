#include<iostream>
#include<map>

using namespace std;
#define MIN_BALANCE 500

class InsufficientFunds{};

class Account
{
    private:
        long accountNumber;
        string firstName;
        string lastName;
        float balance;
        static long NextAccountNumber;
    public:
        Account(){}
        Account(string fname, string lname, float balance);

        long getAccNo(){return accountNumber;}
        string getFirstName(){return firstName;}
        string getLastName(){return lastName;}
        float getBalance(){return balance;}

        void deposit(float amount);
        void withdraw(float amount);
        static void setLastAccountNumber(long accountNumber);
        static long getLastAccountNumber();
        friend ofstream & operator<<(ofstream &ofs, Account &acc);
        friend ifstream & operator>>(ifstream &ifs, Account &acc);
        friend ostream & operator<<(ostream &os, Account &acc);

        ~Account(){}
};

long Account::NextAccountNumber = 0;

class Bank
{
    private:
        map<long, Account> accounts;
    public:
        Bank(){}
        Account openAccount(string fname, string lname, float balance);
        Account balanceEnquiry(long accountNumber);
        Account deposit(long accountNumber, float amount);
        Account withdraw(long accountNumber, float amount);
        void closeAccount(long accountNumber);
        void showAllAccounts();

        ~Bank(){}
};

int main()
{
    Bank b;
    Account acc;

    int choice;
    string fname, lname;
    long accountNumber;
    float balance;
    float amount;

    do
    {
        cout << "***Banking System***\n\n"
            << "\tSelect your service options below:\n"
            << "\t1. Open an account\n"
            << "\t2. Balance Enquiry\n"
            << "\t3. Deposit\n"
            << "\t4. Withdraw\n"
            << "\t5. Close an Account\n"
            << "\t6. Show All Accounts\n"
            << "\t7. Quit\n"
            << "Enter your choice: ";
        // do
        // {
            cin >> choice;
        // } while (choice < 1 || choice > 7);
        
        switch (choice)
        {
            case 1:
                cout << "Enter First Name: " << endl;
                cin >> fname;
                cout << "Enter Last Name: " << endl;
                cin >> lname;
                cout << "Enter Initial Balance: " << endl;
                cin >> balance;
                acc = b.openAccount(fname, lname, balance);

                cout << endl << "Your Account Has Been Successfully Created" << endl;
                cout << acc;
                break;
                
            case 2:
                cout << "Enter Account Number: " << endl;
                cin >> accountNumber;
                acc = b.balanceEnquiry(accountNumber);

                cout << endl << "Your Account Details" << endl;
                cout << acc;
                break;

            case 3:
                cout << "Enter Account Number: " << endl;
                cin >> accountNumber;
                cout << "Enter Balance: ";
                cin >> amount;
                acc = b.deposit(accountNumber, amount);

                cout << endl << "Amount is Deposited" << endl;
                cout << acc;
                break;

            // case 4:
            //     cout << "Enter Account Number: " << endl;
            //     cin >> accountNumber;
            //     cout << "Enter Balance: ";
            //     cin >> amount;
            //     acc = b.withdraw(accountNumber, amount);

            //     cout << endl << "Amount Withdrawn" << endl;
            //     cout << acc;
            //     break;

            // case 5:
            //     cout << "Enter Account Number: " << endl;
            //     cin >> accountNumber;
            //     b.closeAccount(accountNumber);
                
            //     cout << endl << "Account is Closed" << endl;
            //     cout<< acc;
            //     break;
            
            case 6:
                b.showAllAccounts();
                break;

            case 7:
                exit(0);
                break;

            default:
                cout << "Invalid Input, Please Enter Again" << endl;
                break;
        }
    }while(true);
}

Account::Account(string fname, string lname, float balance)
{
    this->firstName = fname;
    this->lastName = lname;
    this->balance = balance > MIN_BALANCE ? balance : MIN_BALANCE;
    accountNumber = NextAccountNumber + 1;
    setLastAccountNumber(accountNumber);
}

void Account::deposit(float amount)
{
    balance += amount;
}

void Account::withdraw(float amount)
{
    if(amount > balance)
    {
        cout << "You don't have enough money" << endl;
    }
    else
    {
        balance -= amount;
    }
}

void Account::setLastAccountNumber(long accountNumber)
{
    NextAccountNumber = accountNumber;
}

long Account::getLastAccountNumber()
{
    return NextAccountNumber;
}

ofstream & operator<<(ofstream &ofs, Account &acc)
{
    return ofs;
}

ifstream & operator>>(ifstream &ifs, Account &acc)
{
    return ifs;
}

ostream & operator<<(ostream &os, Account &acc)
{
    os << "Customer " << acc.accountNumber << endl 
       << "Name: " << acc.firstName << " " << acc.lastName << endl
       << "Balance: " << acc.balance << endl << endl;
    return os;
}

Account Bank::openAccount(string fname, string lname, float balance)
{
    Account temp(fname, lname, balance);
    accounts[temp.getLastAccountNumber()] = temp;
    
    return temp;
}

Account Bank::balanceEnquiry(long accountNumber)
{
    Account temp = accounts[accountNumber];

    return temp;
}

Account Bank::deposit(long accountNumber, float amount)
{
    Account temp = accounts[accountNumber];
    temp.deposit(amount);

    return temp;
}

Account Bank::withdraw(long accountNumber, float amount)
{
    Account temp;

    return temp;
}

void Bank::closeAccount(long accountNumber)
{

}

void Bank::showAllAccounts()
{
    cout << "Here's all the accounts in the bank system" << endl;
    for(auto item : accounts)
    {
        cout << "Customer " << item.first << endl
             << "Name: " << item.second.getFirstName() << " " << item.second.getLastName() << endl
             << "Balance: " << item.second.getBalance() << endl << endl;
    }
}