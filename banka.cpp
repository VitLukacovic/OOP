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
        static double defaultInterestRate;
        int number;
        double balance;
        double interestRate;

        Client *owner;

    public:
        static int GetObjectsCount();
        static double GetDefaultInterestRate();
        static void SetDefaultInterestRate(double ir);
        Account(int n, Client *c);
        Account(int n, Client *c, double ir);
        virtual ~Account();

        int GetNumber();
        double GetBalance();
        double GetInterestRate();
        Client *GetOwner();
        bool CanWithdraw(double a);

        void Deposit(double a);
        bool Withdraw(double a);
        void AddInterest();

        void SetInterestRate(double ir);
};

class PartnerAccount : public Account
{
    private:
        Client *partner;

    public:
        PartnerAccount(int n, Client *c, Client *p);
        PartnerAccount(int n, Client *c, Client *p, double ir);

        Client *GetPartner();
};

int Account::objectsCount = 0;
double Account::defaultInterestRate = 0.01;

int Account::GetObjectsCount()
{
    return Account::objectsCount;
}

double Account::GetDefaultInterestRate()
{
    return Account::defaultInterestRate;
}

void Account::SetDefaultInterestRate(double ir)
{
    Account::defaultInterestRate = ir;
}

Account::Account(int n, Client *c)
{
    this->number = n;
    this->owner = c;
    this->balance = 0.0;
    this->interestRate = -1.0;

    Account::objectsCount += 1;
}

Account::Account(int n, Client *c, double ir) : Account(n, c)
{
    this->interestRate = ir;
}

PartnerAccount::PartnerAccount(int n, Client *c, Client *p) : Account(n, c)
{
    this->partner = p;
}

PartnerAccount::PartnerAccount(int n, Client *c, Client *p, double ir) : Account(n, c, ir)
{
    this->partner = p;
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
    if(this->interestRate < 0.0)
    {
        return Account::defaultInterestRate;
    }
    return this->interestRate;
}

Client* Account::GetOwner()
{ 
    return this->owner; 
}

Client* PartnerAccount::GetPartner()
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
    this->balance += this->balance * this->GetInterestRate();
}

void Account::SetInterestRate(double ir)
{
    this->interestRate = ir;
}

class Bank
{
    private:
        Client** clients;
        int clientsCount;

        Account** accounts;
        int accountsCount;

    public:
        Bank(int c, int a);
        ~Bank();

        Client* GetClient(int c);
        Account* GetAccount(int n);

        Client* CreateClient(int c, string n);
        Account* CreateAccount(int n, Client *c);
        Account* CreateAccount(int n, Client *c, double ir);
        PartnerAccount* CreateAccount(int n, Client *c, Client *p);
        PartnerAccount* CreateAccount(int n, Client *c, Client *p, double ir);

        void AddInterest();
};

Bank::Bank(int c, int a)
{
    this->clientsCount = 0;
    this->clients = new Client*[c];

    this->accountsCount = 0;
    this->accounts = new Account*[a];
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

PartnerAccount* Bank::CreateAccount(int n, Client *c, Client *p)
{
    PartnerAccount* acc = new PartnerAccount(n, c, p);
    accounts[accountsCount++] = acc;
    return acc;
}

PartnerAccount* Bank::CreateAccount(int n, Client *c, Client *p, double ir)
{
    PartnerAccount* acc = new PartnerAccount(n, c, p, ir);
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
    Bank *myBank = new Bank(100, 1000);

    // Vytvoření klientů
    Client* clients[10];
    for(int i = 0; i < 10; i++)
    {
        string name = "Client_" + to_string(i+1);
        clients[i] = myBank->CreateClient(1000 + i, name);
    }

    // Vytvoření účtů
    Account* accounts[10];
    for(int i = 0; i < 10; i++)
    {
        // každý klient má účet s počátečním zůstatkem 0 a úrokem 2%
        accounts[i] = myBank->CreateAccount(2000 + i, clients[i], 0.02);
    }

    // Simulace vkladů
    for(int i = 0; i < 10; i++)
    {
        accounts[i]->Deposit(1000.0 + i*100); // každý klient trochu jiný vklad
    }

    // Simulace výběrů
    for(int i = 0; i < 5; i++) // prvních 5 klientů vybírá
    {
        bool success = accounts[i]->Withdraw(200.0);
        cout << "Vyber klienta " << accounts[i]->GetOwner()->GetName();
        if(success)
        {
            cout << " uspesny " << endl;
        }
        else
        {
            cout << " neuspesny " << endl;
        }
    }

    // Přidání úroku všem účtům
    myBank->AddInterest();

    // Výpis zůstatků všech účtech
    cout << "\n--- Vypis zustatku na uctech ---\n";
    for(int i = 0; i < 10; i++)
    {
        cout << accounts[i]->GetOwner()->GetName() << ": "
             << accounts[i]->GetBalance() << " CZK" << endl;
    }

    // Test hledání účtu a klienta
    Account* accSearch = myBank->GetAccount(2003);
    if(accSearch)
    {
        cout << "\nUcet 2003 nalezen, vlastnik: " << accSearch->GetOwner()->GetName() << endl;
    }


    Client* clientSearch = myBank->GetClient(1005);
    if(clientSearch)
    {
        cout << "Klient 1005 nalezen: " << clientSearch->GetName() << endl;
    }

    // Test statické úrokové sazby
    Client* c1 = myBank->CreateClient(10, "Jan Novak");
    Client* c2 = myBank->CreateClient(11, "Petr Pavel");

    Account* acc1 = myBank->CreateAccount(1, c1);
    Account* acc2 = myBank->CreateAccount(2, c2, 0.05);

    acc1->Deposit(1000);
    acc2->Deposit(1000);

    cout << "\n--- Vychozi stav (Sazba tridy nastaveni na 1 %) ---" << endl;
    cout << "Ucet 1: " << acc1->GetInterestRate() * 100 << " %" << endl;
    cout << "Ucet 2: " << acc2->GetInterestRate() * 100 << " %" << endl;

    Account::SetDefaultInterestRate(0.03);

    cout << "\n--- Stav po zmene sazby tridy na 3 % ---" << endl;
    cout << "Ucet 1: " << acc1->GetInterestRate() * 100 << " %" << endl;
    cout << "Ucet 2: " << acc2->GetInterestRate() * 100 << " %" << endl;

    myBank->AddInterest();
    cout << "\n--- Zustatky po pripsani uroku ---" << endl;
    cout << "Ucet 1: " << acc1->GetBalance() << " CZK (pripsano 3 % z 1000)" << endl;
    cout << "Ucet 2: " << acc2->GetBalance() << " CZK (pripsano 5 % z 1000)\n" << endl;

    // test dědičnost
    Account *a;
    PartnerAccount *pa;
    Client *o = myBank->CreateClient(0, "Smith");
    Client *p = myBank->CreateClient(1, "Jones");
    a = myBank->CreateAccount(0, o);
    pa = myBank->CreateAccount(1, o, p);

    cout << a->GetOwner()->GetName() << endl;
    //cout << a->GetPartner()->GetName() << endl;
    cout << pa->GetPartner()->GetName() << endl;

    cout << myBank->GetClient(1)->GetName() << endl;
    //cout << myBank->GetClient(1)->GetPartner() << endl;

    delete myBank;

    getchar();
    return 0;
}