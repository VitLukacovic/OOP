#include <iostream>
#include <string>
using namespace std;

class Client
{
    private:
        static int objectsCount;
        int code;
        string name;

    public:
        static int GetObjectsCount();
        Client(int c, string n);
        ~Client();
        int GetCode();
        string GetName();
};

int Client::objectsCount = 0;

Client::Client(int c, string n)
{
    this->code = c;
    this->name = n;
    Client::objectsCount += 1;
}

Client::~Client()
{
    Client::objectsCount -= 1;
}

int Client::GetObjectsCount()
{
    return Client::objectsCount;
}

int Client::GetCode()
{
    return this->code;
}

string Client::GetName()
{
    return this->name;
}

class Account
{
    private:
        static int objectsCount;
        int number;
        double balance;
        double interestRate;

        Client *owner;
        Client *partner;

    public:
        static int GetObjectsCount();
        Account(int n, Client *c);
        Account(int n, Client *c, double ir);
        Account(int n, Client *c, Client *p);
        Account(int n, Client *c, Client *p, double ir);
        ~Account();

        int GetNumber();
        double GetBalance();
        double GetInterestRate();
        Client *GetOwner();
        Client *GetPartner();
        bool CanWithdraw(double a);

        void Deposit(double a);
        bool Withdraw(double a);
        void AddInterest();

        void SetInterestRate(double ir);
};

int Account::objectsCount = 0;

int Account::GetObjectsCount()
{
    return Account::objectsCount;
}

Account::Account(int n, Client *c)
{
    this->number = n;
    this->owner = c;
    this->partner = nullptr;
    this->balance = 0.0;
    this->interestRate = 0.0;

    Account::objectsCount += 1;
}

Account::Account(int n, Client *c, double ir)
    : Account(n, c)
{
    this->interestRate = ir;
}

Account::Account(int n, Client *c, Client *p)
    : Account(n, c)
{
    this->partner = p;
}

Account::Account(int n, Client *c, Client *p, double ir)
    : Account(n, c, p)
{
    this->interestRate = ir;
}

Account::~Account()
{
    Account::objectsCount -= 1;
}

int Account::GetNumber()
{ 
    return this->number;
}

double Account::GetBalance() 
{ 
    return this->balance; 
}

double Account::GetInterestRate() 
{ 
    return this->interestRate;
}

Client* Account::GetOwner()
{ 
    return this->owner; 
}

Client* Account::GetPartner()
{ 
    return this->partner;
}

bool Account::CanWithdraw(double a)
{
    return this->balance >= a;
}

void Account::Deposit(double a)
{
    if(a > 0)
    {
        this->balance += a;
    }
}

bool Account::Withdraw(double a)
{
    if(CanWithdraw(a))
    {
        this->balance -= a;
        return true;
    }
    return false;
}

void Account::AddInterest()
{
    this->balance += this->balance * this->interestRate;
}

void Account::SetInterestRate(double ir)
{
    this->interestRate = ir;
}

class Bank
{
    private:
        static double interestRate;
        Client** clients;
        int clientsCount;

        Account** accounts;
        int accountsCount;

    public:
        static double GetInterestRate();
        Bank(int c, int a);
        ~Bank();

        Client* GetClient(int c);
        Account* GetAccount(int n);

        Client* CreateClient(int c, string n);
        Account* CreateAccount(int n, Client *c);
        Account* CreateAccount(int n, Client *c, double ir);
        Account* CreateAccount(int n, Client *c, Client *p);
        Account* CreateAccount(int n, Client *c, Client *p, double ir);

        void ChangeInterestRate();

        void AddInterest();
};

double Bank::interestRate = 0.03;

double Bank::GetInterestRate()
{
    return Bank::interestRate;
}

Bank::Bank(int c, int a)
{
    this->clientsCount = 0;
    this->clients = new Client*[c];

    this->accountsCount = 0;
    this->accounts = new Account*[a];
}

void Bank::ChangeInterestRate()
{
    for(int i = 0; i < accountsCount; i++)
    {
        if(accounts[i]->GetInterestRate() == 0.00)
        {
            accounts[i]->SetInterestRate(Bank::interestRate);
        }
    }
}

Bank::~Bank()
{
    for(int i = 0; i < clientsCount; i++)
    {
        delete clients[i];
    }

    delete[] clients;

    for(int i = 0; i < accountsCount; i++)
    {
        delete accounts[i];
    }
        
    delete[] accounts;
}

Client* Bank::GetClient(int c)
{
    for(int i = 0; i < clientsCount; i++)
    {
        if(clients[i]->GetCode() == c)
        {
            return clients[i];
        }
    }
    return nullptr;
}

Account* Bank::GetAccount(int n)
{
    for(int i = 0; i < accountsCount; i++)
    {
        if(accounts[i]->GetNumber() == n)
            return accounts[i];
    }
    return nullptr;
}

Client* Bank::CreateClient(int c, string n)
{
    Client* newClient = new Client(c, n);
    clients[clientsCount++] = newClient;
    return newClient;
}

Account* Bank::CreateAccount(int n, Client *c)
{
    Account* acc = new Account(n, c);
    accounts[accountsCount++] = acc;
    return acc;
}

Account* Bank::CreateAccount(int n, Client *c, double ir)
{
    Account* acc = new Account(n, c, ir);
    accounts[accountsCount++] = acc;
    return acc;
}

Account* Bank::CreateAccount(int n, Client *c, Client *p)
{
    Account* acc = new Account(n, c, p);
    accounts[accountsCount++] = acc;
    return acc;
}

Account* Bank::CreateAccount(int n, Client *c, Client *p, double ir)
{
    Account* acc = new Account(n, c, p, ir);
    accounts[accountsCount++] = acc;
    return acc;
}

void Bank::AddInterest()
{
    for(int i = 0; i < accountsCount; i++)
        accounts[i]->AddInterest();
}

int main()
{
    // Vytvoření banky
    Bank myBank(50, 50);

    // Vytvoření klientů
    Client* clients[10];
    for(int i = 0; i < 10; i++)
    {
        string name = "Client_" + to_string(i+1);
        clients[i] = myBank.CreateClient(1000 + i, name);
    }

    // Vytvoření účtů
    Account* accounts[10];
    for(int i = 0; i < 10; i++)
    {
        // každý klient má účet s počátečním zůstatkem 0 a úrokem 2%
        accounts[i] = myBank.CreateAccount(2000 + i, clients[i], 0.02);
    }

    // Simulace vkladů
    for(int i = 0; i < 10; i++)
    {
        accounts[i]->Deposit(1000.0 + i*100); // každý klient trochu jiný vklad
    }

    // Simulace výběrů
    for(int i = 0; i < 5; i++)
    {
        bool success = accounts[i]->Withdraw(200.0); // první 5 klientů vybírá
        cout << "Withdraw for " << accounts[i]->GetOwner()->GetName()
             << " successful? " << (success ? "Yes" : "No") << endl;
    }

    // Přidání úroku všem účtům
    myBank.AddInterest();

    // Výpis zůstatků všech účtů
    cout << "\n--- Account balances after deposits, withdrawals, and interest ---\n";
    for(int i = 0; i < 10; i++)
    {
        cout << accounts[i]->GetOwner()->GetName() << ": "
             << accounts[i]->GetBalance() << " CZK" << endl;
    }

    // Test hledání účtu a klienta
    Account* accSearch = myBank.GetAccount(2003);
    if(accSearch)
        cout << "\nFound account 2003, owner: " << accSearch->GetOwner()->GetName() << endl;

    Client* clientSearch = myBank.GetClient(1005);
    if(clientSearch)
        cout << "Found client 1005: " << clientSearch->GetName() << endl;

    return 0;
}