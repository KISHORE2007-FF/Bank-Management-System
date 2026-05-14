#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class BankAccount
{
private:
    int accountNumber;
    char name[50];
    char accountType;
    float balance;

public:
    void createAccount();
    void showAccount() const;
    void deposit(float);
    void withdraw(float);
    int getAccountNumber() const;
    float getBalance() const;
};

void BankAccount::createAccount()
{
    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    cin.ignore();

    cout << "Enter Account Holder Name: ";
    cin.getline(name, 50);

    cout << "Enter Account Type (S for Saving / C for Current): ";
    cin >> accountType;

    cout << "Enter Initial Deposit Amount: ";
    cin >> balance;

    cout << "\nAccount Created Successfully!\n";
}

void BankAccount::showAccount() const
{
    cout << "\nAccount Number : " << accountNumber;
    cout << "\nAccount Holder : " << name;
    cout << "\nAccount Type   : " << accountType;
    cout << "\nBalance        : " << balance << endl;
}

void BankAccount::deposit(float amount)
{
    balance += amount;
}

void BankAccount::withdraw(float amount)
{
    if (amount <= balance)
    {
        balance -= amount;
        cout << "\nWithdrawal Successful!\n";
    }
    else
    {
        cout << "\nInsufficient Balance!\n";
    }
}

int BankAccount::getAccountNumber() const
{
    return accountNumber;
}

float BankAccount::getBalance() const
{
    return balance;
}

// Function to write account to file
void writeAccount()
{
    BankAccount acc;

    ofstream outFile("bank.dat", ios::binary | ios::app);

    acc.createAccount();

    outFile.write(reinterpret_cast<char *>(&acc), sizeof(BankAccount));

    outFile.close();
}

// Function to display account details
void displayAccount(int accNo)
{
    BankAccount acc;
    bool found = false;

    ifstream inFile("bank.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char *>(&acc), sizeof(BankAccount)))
    {
        if (acc.getAccountNumber() == accNo)
        {
            acc.showAccount();
            found = true;
        }
    }

    inFile.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

// Deposit or Withdraw
void modifyAccount(int accNo, int option)
{
    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    bool found = false;

    while (!file.eof() && !found)
    {
        streampos pos = file.tellg();

        file.read(reinterpret_cast<char *>(&acc), sizeof(BankAccount));

        if (acc.getAccountNumber() == accNo)
        {
            float amt;

            if (option == 1)
            {
                cout << "\nEnter Amount to Deposit: ";
                cin >> amt;
                acc.deposit(amt);
            }
            else
            {
                cout << "\nEnter Amount to Withdraw: ";
                cin >> amt;
                acc.withdraw(amt);
            }

            file.seekp(pos);
            file.write(reinterpret_cast<char *>(&acc), sizeof(BankAccount));

            cout << "\nTransaction Updated Successfully!\n";

            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "\nAccount Not Found!\n";
}

int main()
{
    int choice, accNo;

    do
    {
        cout << "\n\n====== BANK MANAGEMENT SYSTEM ======";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Amount";
        cout << "\n3. Withdraw Amount";
        cout << "\n4. Balance Inquiry";
        cout << "\n5. Exit";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            writeAccount();
            break;

        case 2:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            modifyAccount(accNo, 1);
            break;

        case 3:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            modifyAccount(accNo, 2);
            break;

        case 4:
            cout << "\nEnter Account Number: ";
            cin >> accNo;
            displayAccount(accNo);
            break;

        case 5:
            cout << "\nThank You for Using the Bank Management System!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}
