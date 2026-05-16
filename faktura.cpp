#include <iostream>
#include <string>
using namespace std;

class Osoba
{
    private:
        string Jmeno;
        string Adresa;

    public:
        Osoba();
        Osoba(string j, string a);
        string GetJmeno();
        string GetAdresa();
};

Osoba::Osoba()
{
    this->Jmeno = "";
    this->Adresa = "";
}

Osoba::Osoba(string j, string a)
{
    this->Jmeno = j;
    this->Adresa = a;
}

string Osoba::GetJmeno()
{
    return this->Jmeno;
}

string Osoba::GetAdresa()
{
    return this->Adresa;
}

class PolozkaFaktury
{
    private:
        string nazev;
        int pocet;
        double jednotkova_cena;

    public:
        PolozkaFaktury(string n, int p, double c);
        string GetNazev();
        int GetPocet();
        double GetCena();
};

PolozkaFaktury::PolozkaFaktury(string n, int p, double c)
{
    this->nazev = n;
    this->pocet = p;
    this->jednotkova_cena = c;
}

string PolozkaFaktury::GetNazev()
{
    return this->nazev;
}

int PolozkaFaktury::GetPocet()
{
    return this->pocet;
}

double PolozkaFaktury::GetCena()
{
    return this->jednotkova_cena;
}

class Faktura
{
    private:
        int cislo;
        Osoba osoba;
        PolozkaFaktury** polozky_faktury;
        int kapacita_polozek;
        int id;

    public:
        Faktura(int c, int n, string j, string a);
        ~Faktura();
        int TotalCount();
        int GetCislo();
        Osoba GetOsoba();
        PolozkaFaktury* CreatePolozka(string n, int p, double c);
        PolozkaFaktury* SearchPolozka(string n);
        PolozkaFaktury* RemovePolozka(string n);
        double TotalPrice();
};

Faktura::Faktura(int c, int n, string j, string a)
{
    this->cislo = c;
    this->osoba = Osoba(j, a);
    this->id = 0;
    this->kapacita_polozek = n;
    this->polozky_faktury = new PolozkaFaktury*[n];
}

Faktura::~Faktura()
{
    for(int i = 0; i < id; i++)
    {
        delete this->polozky_faktury[i];
    }

    delete[] this->polozky_faktury;
}

int Faktura::TotalCount()
{
    int total = 0;

    for(int i = 0; i < id; i++)
    {
        total = total + this->polozky_faktury[i]->GetPocet();
    }

    return total;
}

int Faktura::GetCislo()
{
    return this->cislo;
}

Osoba Faktura::GetOsoba()
{
    return this->osoba;
}

PolozkaFaktury* Faktura::CreatePolozka(string n, int p, double c)
{
    if (this->id >= this->kapacita_polozek) 
    {
        cout << "Faktura je plna, nelze pridat polozku " << n << endl;
        return nullptr;
    }

    PolozkaFaktury *newObject = new PolozkaFaktury(n, p, c);

    this->polozky_faktury[this->id] = newObject;
    this->id += 1;

    return newObject;
}

PolozkaFaktury* Faktura::SearchPolozka(string n)
{
    for(int i = 0; i < this->id; i++)
    {
        if(this->polozky_faktury[i]->GetNazev() == n)
        {
            return this->polozky_faktury[i];
        }
    }

    return nullptr;
}

PolozkaFaktury* Faktura::RemovePolozka(string n)
{
    for(int i = 0; i < this->id; i++)
    {
        if(this->polozky_faktury[i]->GetNazev() == n)
        {
            PolozkaFaktury* for_removal = this->polozky_faktury[i];

            for(int j = i; j < this->id - 1; j++)
            {
                this->polozky_faktury[j] = this->polozky_faktury[j + 1];
            }

            this->id--;
            return for_removal;
        }
    }

    return nullptr;
}

double Faktura::TotalPrice()
{
    double total = 0;
    for(int i = 0; i < id; i++)
    {
        total += this->polozky_faktury[i]->GetCena() * this->polozky_faktury[i]->GetPocet();
    }

    return total;
}

int main()
{
    Faktura faktura1(1, 10, "Jan Novak", "Praha 1");
    cout << "Faktura cislo: " << faktura1.GetCislo() << endl;
    cout << "Jmeno zakaznika: " << faktura1.GetOsoba().GetJmeno() << endl;
    cout << "Adresa zakaznika: " << faktura1.GetOsoba().GetAdresa() << endl;

    faktura1.CreatePolozka("Notebook", 2, 15000.0);
    faktura1.CreatePolozka("Myš", 3, 500.0);
    faktura1.CreatePolozka("Klavesnice", 1, 1200.0);

    cout << "\nPocet vsech kusu: " << faktura1.TotalCount() << endl;
    cout << "Celkova cena: " << faktura1.TotalPrice() << " CZK\n" << endl;

    PolozkaFaktury* p = faktura1.SearchPolozka("Myš");
    if(p != nullptr)
        cout << "Nalezena polozka: " << p->GetNazev() << ", pocet: " 
             << p->GetPocet() << ", cena za kus: " << p->GetCena() << endl;

    PolozkaFaktury* removed = faktura1.RemovePolozka("Notebook");
    if(removed != nullptr)
    {
        cout << "\nOdebrana polozka: " << removed->GetNazev() << endl;
        delete removed;
    }

    cout << "\nPocet vsech kusu po odebrani: " << faktura1.TotalCount() << endl;
    cout << "Celkova cena po odebrani: " << faktura1.TotalPrice() << " CZK" << endl;

    return 0;
}