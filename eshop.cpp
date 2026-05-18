#include <iostream>
#include <string>
using namespace std;

class Produkt
{
    protected:
        string nazev;
        double cena;

    public:
        Produkt(string nazev, double cena);
        virtual ~Produkt();

        string GetNazev();
        double GetCena();
        virtual string GetDetaily(); // polymorfní metoda pro textové detaily
};

// --- Potomek: Telefon ---
class Telefon : public Produkt
{
    private:
        string operacniSystem;

    public:
        Telefon(string nazev, double cena, string os);
        string GetDetaily() override;
};

// --- Potomek: Notebook ---
class Notebook : public Produkt
{
    private:
        int kapacitaRAM;

    public:
        Notebook(string nazev, double cena, int ram);
        string GetDetaily() override;
};

class Zakaznik
{
    protected:
        string jmeno;

    public:
        Zakaznik(string jmeno);
        virtual ~Zakaznik();

        string GetJmeno();
        virtual string GetInfo(); // polymorfní metoda pro informace o zákazníkovi
};

// --- Potomek: Neregistrovaný uživatel ---
class NeregistrovanyZakaznik : public Zakaznik
{
    private:
        string email;

    public:
        NeregistrovanyZakaznik(string jmeno, string email);
        string GetInfo() override;
};

// --- Potomek: Registrovaný uživatel ---
class RegistrovanyZakaznik : public Zakaznik
{
    private:
        int cisloKarty;

    public:
        RegistrovanyZakaznik(string jmeno, int cisloKarty);
        string GetInfo() override;
};

// --- Potomek: Firma ---
class Firma : public Zakaznik
{
    private:
        string ico;

    public:
        Firma(string jmeno, string ico);
        string GetInfo() override;
};

class PolozkaObjednavky
{
    private:
        Produkt* produkt; // ukazatel na polymorfní produkt
        int pocetKusu;

    public:
        PolozkaObjednavky(Produkt* p, int kusy);
        ~PolozkaObjednavky();

        Produkt* GetProdukt();
        int GetPocetKusu();
        double SpoctuCenuPolozky();
};

class Objednavka
{
    private:
        Zakaznik* zakaznik;          // ukazatel na polymorfního zákazníka
        PolozkaObjednavky** polozky; // dynamické pole ukazatelů na položky
        int pocetPolozek;
        int kapacita;

    public:
        Objednavka(Zakaznik* z, int kapacita);
        ~Objednavka();

        void PridejPolozku(Produkt* p, int kusy);
        double SpoctuCelkovouCenu();
        void VypisSouhrn();
};

// --- Metody: Produkt ---
Produkt::Produkt(string nazev, double cena)
{
    this->nazev = nazev;
    this->cena = cena;
}

Produkt::~Produkt()
{

}

string Produkt::GetNazev()
{
    return this->nazev;
}

double Produkt::GetCena()
{
    return this->cena;
}

string Produkt::GetDetaily()
{
    return "Obecny produkt: " + this->nazev + " | Cena: " + to_string(this->cena) + " Kc";
}

// --- Metody: Telefon ---
Telefon::Telefon(string nazev, double cena, string os) : Produkt(nazev, cena)
{
    this->operacniSystem = os;
}

string Telefon::GetDetaily()
{
    return "Telefon: " + this->nazev + " (OS: " + this->operacniSystem + ") | Cena: " + to_string(this->cena) + " Kc";
}

// --- Metody: Notebook ---
Notebook::Notebook(string nazev, double cena, int ram) : Produkt(nazev, cena)
{
    this->kapacitaRAM = ram;
}

string Notebook::GetDetaily()
{
    return "Notebook: " + this->nazev + " (" + to_string(this->kapacitaRAM) + "GB RAM) | Cena: " + to_string(this->cena) + " Kc";
}

// --- Metody: Zakaznik ---
Zakaznik::Zakaznik(string jmeno)
{
    this->jmeno = jmeno;
}

Zakaznik::~Zakaznik()
{

}

string Zakaznik::GetJmeno()
{
    return this->jmeno;
}

string Zakaznik::GetInfo()
{
    return "Zakaznik: " + this->jmeno;
}

// --- Metody: NeregistrovanyZakaznik ---
NeregistrovanyZakaznik::NeregistrovanyZakaznik(string jmeno, string email) : Zakaznik(jmeno)
{
    this->email = email;
}
string NeregistrovanyZakaznik::GetInfo()
{
    return "Jednorazovy nakup bez registrace | Jmeno: " + this->jmeno + " (Kontakt: " + this->email + ")";
}

// --- Metody: RegistrovanyZakaznik ---
RegistrovanyZakaznik::RegistrovanyZakaznik(string jmeno, int cisloKarty) : Zakaznik(jmeno)
{
    this->cisloKarty = cisloKarty;
}

string RegistrovanyZakaznik::GetInfo()
{
    return "Registrovany uzivatel | Jmeno: " + this->jmeno + " (ID Karty: " + to_string(this->cisloKarty) + ")";
}

// --- Metody: Firma ---
Firma::Firma(string jmeno, string ico) : Zakaznik(jmeno)
{
    this->ico = ico;
}
string Firma::GetInfo()
{
    return "Firemni zakaznik | Nazev: " + this->jmeno + " (ICO: " + this->ico + ")";
}

// --- Metody: PolozkaObjednavky ---
PolozkaObjednavky::PolozkaObjednavky(Produkt* p, int kusy)
{
    this->produkt = p;
    this->pocetKusu = kusy;
}

PolozkaObjednavky::~PolozkaObjednavky()
{

}

Produkt* PolozkaObjednavky::GetProdukt()
{
    return this->produkt;
}

int PolozkaObjednavky::GetPocetKusu()
{
    return this->pocetKusu;
}

double PolozkaObjednavky::SpoctuCenuPolozky()
{
    return this->produkt->GetCena() * this->pocetKusu;
}


// --- Metody: Objednavka ---
Objednavka::Objednavka(Zakaznik* z, int kapacita)
{
    this->zakaznik = z;
    this->pocetPolozek = 0;
    this->kapacita = kapacita;
    this->polozky = new PolozkaObjednavky*[this->kapacita];
}

Objednavka::~Objednavka()
{
    for(int i = 0; i < this->pocetPolozek; i++)
    {
        delete this->polozky[i];
    }
    delete[] this->polozky;
}

void Objednavka::PridejPolozku(Produkt* p, int kusy)
{
    if(this->pocetPolozek >= this->kapacita)
    {
        return;
    }

    this->polozky[this->pocetPolozek++] = new PolozkaObjednavky(p, kusy);
}

double Objednavka::SpoctuCelkovouCenu()
{
    double celkem = 0.0;
    for (int i = 0; i < this->pocetPolozek; i++)
    {
        celkem += this->polozky[i]->SpoctuCenuPolozky();
    }
    return celkem;
}

void Objednavka::VypisSouhrn()
{
    cout << "Informace o zakaznikovi:" << endl;
    cout << "  " << this->zakaznik->GetInfo() << endl;
    cout << "\nPolozky objednavky:" << endl;
    
    for(int i = 0; i < this->pocetPolozek; i++)
    {
        Produkt* p = this->polozky[i]->GetProdukt();
        cout << " - " << p->GetNazev() 
             << " | Cena/ks: " << p->GetCena() << " Kc"
             << " | Pocet: " << this->polozky[i]->GetPocetKusu() << " ks"
             << " | Celkem: " << this->polozky[i]->SpoctuCenuPolozky() << " Kc" << endl;
    }
    cout << "\n";
    cout << "Celkova cena objednavky: " << this->SpoctuCelkovouCenu() << " Kc" << endl;
    cout << "---------------------------------------------------------\n";
}

int main()
{
    // vytvoření katalogu produktů (Polymorfní datová struktura)
    Produkt* p1 = new Telefon("iPhone 15", 23990.0, "iOS");
    Produkt* p2 = new Telefon("Samsung Galaxy S24", 21490.0, "Android");
    Produkt* p3 = new Notebook("MacBook Air M3", 37990.0, 16);
    Produkt* p4 = new Notebook("Lenovo ThinkPad", 28500.0, 32);

    // získání textových detailů z katalogu
    cout << "--- UKAZKA KATALOGU PRODUKTU ---" << endl;
    cout << p1->GetDetaily() << endl;
    cout << p2->GetDetaily() << endl;
    cout << p3->GetDetaily() << endl;
    cout << p4->GetDetaily() << endl;
    cout << "--------------------------------" << endl << endl;

    // vytvoření různých typů zákazníků
    Zakaznik* z1 = new NeregistrovanyZakaznik("Jan Maly", "jan.maly@email.cz");
    Zakaznik* z2 = new RegistrovanyZakaznik("Petr Velky", 458712);
    Zakaznik* z3 = new Firma("Banska soft s.r.o.", "CZ12345678");

    // vytváření a plnění objednávek
    // neregistrovaný zákazník
    Objednavka* obj1 = new Objednavka(z1, 5);
    obj1->PridejPolozku(p1, 1); // 1x iPhone

    // registrovaný zákazníkp
    Objednavka* obj2 = new Objednavka(z2, 5);
    obj2->PridejPolozku(p2, 2); // 2x Samsung
    obj2->PridejPolozku(p3, 1); // 1x MacBook

    // firma
    Objednavka* obj3 = new Objednavka(z3, 5);
    obj3->PridejPolozku(p4, 5); // 5x ThinkPad

    // výpis obsahu vytvořených objednávek
    cout << "--- VYPIS VYTVORENYCH OBJEDNAVEK ---" << endl << endl;
    obj1->VypisSouhrn();
    obj2->VypisSouhrn();
    obj3->VypisSouhrn();

    // vyčištění dynamické paměti
    delete obj1;
    delete obj2;
    delete obj3;

    delete z1;
    delete z2;
    delete z3;

    delete p1;
    delete p2;
    delete p3;
    delete p4;

    getchar();
    return 0;
}