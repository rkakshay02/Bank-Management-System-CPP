#include <iostream>
#include <vector>
#include <limits>
#include <random>
using namespace std;

enum AccountType
{
    Savings,
    Current
};

class BankAccount
{
private:
    int accountNumber;
    string Name;
    double Balance;
    AccountType accounttype;

public:
    BankAccount(int accountNumber, string Name, double Balance, AccountType accounttype)
    {
        this->accountNumber = accountNumber;
        this->Name = Name;
        this->Balance = Balance;
        this->accounttype = accounttype;
    }

    string getAccountType()
    {
        if (accounttype == Savings)
        {
            return "Savings";
        }
        else
        {
            return "Current";
        }
    }

    void display()
    {
        cout << "Account Number : " << accountNumber << endl;
        cout << "Name           : " << Name << endl;
        cout << "Balance        : " << Balance << endl;
        cout << "Account Type   : " << getAccountType() << endl << endl;
    }

    int getaccountnumber()
    {
        return accountNumber;
    }

    void deposit(double money)
    {
        Balance += money;
    }

    void withdraw(double money)
    {
        if (Balance < money)
        {
            cout << "Insufficient balance\n";
            return;
        }
        Balance -= money;
    }

    double getBalance()
    {
        return Balance;
    }
};

class BankManagement
{
private:
    vector<BankAccount> customer;

public:
    void createAccount(const BankAccount &cust)
    {
        customer.push_back(cust);
    }

    bool isAccountNumberTaken(int accountNumber)
    {
        for (size_t i = 0; i < customer.size(); i++)
        {
            if (customer[i].getaccountnumber() == accountNumber)
            {
                return true;
            }
        }
        return false;
    }

    // Generates a random, unique 9-digit account number (100000000 - 999999999)
    int generateAccountNumber()
    {
        static random_device rd;
        static mt19937 gen(rd());
        static uniform_int_distribution<int> dist(100000000, 999999999);

        int accNum;
        do
        {
            accNum = dist(gen);
        } while (isAccountNumberTaken(accNum));

        return accNum;
    }

    void displayObjects()
    {
        if (customer.empty())
        {
            cout << "There are no accounts\n";
            return;
        }
        for (size_t i = 0; i < customer.size(); i++)
        {
            customer[i].display();
        }
    }

    void Search(int accountNumber)
    {
        for (size_t i = 0; i < customer.size(); i++)
        {
            if (customer[i].getaccountnumber() == accountNumber)
            {
                cout << "The account number you have entered is confirmed\n";
                customer[i].display();
                return;
            }
        }
        cout << "Account not found\n";
    }

    void AddMoney(int accountNumber, double Money)
    {
        if (Money <= 0)
        {
            cout << "Please enter a valid amount.\n";
            return;
        }
        for (size_t i = 0; i < customer.size(); i++)
        {
            if (customer[i].getaccountnumber() == accountNumber)
            {
                customer[i].deposit(Money);
                cout << "The current balance is: " << customer[i].getBalance() << endl;
                return;
            }
        }
        cout << "Unable to verify the account number.\n";
    }

    void RemoveMoney(int accountNumber, double Money)
    {
        if (Money <= 0)
        {
            cout << "Please enter the valid amount\n";
            return;
        }
        for (size_t i = 0; i < customer.size(); i++)
        {
            if (customer[i].getaccountnumber() == accountNumber)
            {
                customer[i].withdraw(Money);
                cout << "The current balance is: " << customer[i].getBalance() << endl;
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void DeleteAccount(int accountNumber)
    {
        if (customer.empty())
        {
            cout << "There are no accounts.\n";
            return;
        }
        for (size_t i = 0; i < customer.size(); i++)
        {
            if (customer[i].getaccountnumber() == accountNumber)
            {
                customer.erase(customer.begin() + i);
                cout << "Account deleted successfully.\n";
                return;
            }
        }
        cout << "Account not found.\n";
    }
};

void showMenu()
{
    cout << "\n===== BANK MANAGEMENT SYSTEM =====\n";
    cout << "1. Create Account\n";
    cout << "2. Display All Accounts\n";
    cout << "3. Search Account\n";
    cout << "4. Deposit Money\n";
    cout << "5. Withdraw Money\n";
    cout << "6. Delete Account\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    BankManagement Customer;
    int choice;

    do
    {
        showMenu();
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            int typeChoice;
            string name;
            double balance;

            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Account Type (0 - Savings, 1 - Current): ";
            cin >> typeChoice;

            AccountType type = (typeChoice == 0) ? Savings : Current;
            int accNum = Customer.generateAccountNumber();
            BankAccount newAccount(accNum, name, balance, type);
            Customer.createAccount(newAccount);
            cout << "Account created successfully.\n";
            cout << "Your Account Number is: " << accNum << " (keep this safe)\n";
            break;
        }
        case 2:
            Customer.displayObjects();
            break;
        case 3:
        {
            int accNum;
            cout << "Enter Account Number to search: ";
            cin >> accNum;
            Customer.Search(accNum);
            break;
        }
        case 4:
        {
            int accNum;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            Customer.AddMoney(accNum, amount);
            break;
        }
        case 5:
        {
            int accNum;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            Customer.RemoveMoney(accNum, amount);
            break;
        }
        case 6:
        {
            int accNum;
            cout << "Enter Account Number to delete: ";
            cin >> accNum;
            Customer.DeleteAccount(accNum);
            break;
        }
        case 7:
            cout << "Exiting... Thank you!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}