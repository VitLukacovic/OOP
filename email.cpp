#include <iostream>
#include <string>
using namespace std;

class Email 
{
    private:
        string adresa;

    public:
        Email();
        Email(string a);
        string GetAdresa();
};

Email::Email()
{
    adresa = "";
}

Email::Email(string a)
{
    this->adresa = a;
}

string Email::GetAdresa()
{
    return this->adresa;
}

class Osoba
{
    private:
        string Jmeno;
        string Prijmeni;
        Email email;

    public:
        Osoba(string j, string p);
        Osoba(string j, string p, Email e);
        string GetJmeno();
        string GetPrijmeni();
        string GetEmail();
        
};

Osoba::Osoba(string j, string p)
{
    this->Jmeno = j;
    this->Prijmeni = p;
}

Osoba::Osoba(string j, string p, Email e)
{
    this->Jmeno = j;
    this->Prijmeni = p;
    this->email = e;
}

string Osoba::GetJmeno()
{
    return this->Jmeno;
}

string Osoba::GetPrijmeni()
{
    return this->Prijmeni;
}

string Osoba::GetEmail()
{
    return this->email.GetAdresa();
}

class Dokument 
{
    private:
        string nazev;
        Osoba autor;

    public:
        Dokument(string n, string j, string p);
        string GetNazev();
        string GetOsoba();
};

Dokument::Dokument(string n, string j, string p) : autor(j, p)
{
    this->nazev = n;
}

string Dokument::GetNazev()
{
    return this->nazev;
}

string Dokument::GetOsoba()
{
    return this->autor.GetJmeno() + " " + this->autor.GetPrijmeni();
}

int main()
{
    Email e("test@email.cz");
    Osoba o("Jan", "Novak", e);
    Dokument d("Muj dokument", "Petr", "Svoboda");

    cout << o.GetJmeno() << " " << o.GetPrijmeni() << " " << o.GetEmail() << endl;
    cout << d.GetNazev() << " " << d.GetOsoba() << endl;

    return 0;
}