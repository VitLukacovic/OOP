#include <iostream>
#include <string>

using namespace std;

class Shape
{
    private:
        string name;

    public:
        Shape(string n);
        virtual ~Shape();

        string GetName();
        
        virtual double Obsah();
        virtual double Obvod();
        virtual void VypisInfo();

        void Identifikace(); 
};

class Obdelnik : public Shape
{
    private:
        double stranaA;
        double stranaB;

    public:
        Obdelnik(string n, double a, double b);
        
        double Obsah() override;
        double Obvod() override;
        void VypisInfo() override;

        void Identifikace(); 
};

class Kruh : public Shape
{
    private:
        static double pi;
        double polomer;

    public:
        Kruh(string n, double r);

        double Obsah() override;
        double Obvod() override;
        void VypisInfo() override;
        void Identifikace(); 
};

double Kruh::pi = 3.14;

class Platno
{
    private:
        Shape** objekty;
        int pocetObjektu;
        int kapacita;

    public:
        Platno(int kapacita);
        ~Platno();

        Shape* CreateObdelnik(string n, double a, double b);
        Shape* CreateKruh(string n, double r);

        void VypisVsechnyObjekty();
};

// Metody třídy Shape
Shape::Shape(string n)
{
    this->name = n;
}

Shape::~Shape()
{

}

string Shape::GetName()
{
    return this->name;
}

double Shape::Obsah()
{
    return 0.0;
}
double Shape::Obvod()
{
    return 0.0;
}

void Shape::VypisInfo()
{
    cout << "Objekt: " << this->name << " ";
}

void Shape::Identifikace()
{
    cout << "obecny tvar" << endl;
}

// Metody třídy Obdelnik 
Obdelnik::Obdelnik(string n, double a, double b) : Shape(n)
{
    this->stranaA = a;
    this->stranaB = b;
}

double Obdelnik::Obsah()
{
    return this->stranaA * this->stranaB;
}

double Obdelnik::Obvod()
{
    return 2 * (this->stranaA + this->stranaB);
}

void Obdelnik::VypisInfo()
{
    Shape::VypisInfo();
    cout << " - Obdelnik\n| Obsah: " << this->Obsah() << "\n| Obvod: " << this->Obvod() << endl;
}

void Obdelnik::Identifikace()
{
    cout << "Obdelnik" << endl;
}

// Metody třídy Kruh
Kruh::Kruh(string n, double r) : Shape(n)
{
    this->polomer = r;
}

double Kruh::Obsah()
{
    return this->pi * this->polomer * this->polomer;
}

double Kruh::Obvod()
{
    return 2 * this->pi * this->polomer;
}

void Kruh::VypisInfo()
{
    Shape::VypisInfo();
    cout << " - Kruh\n| Obsah: " << this->Obsah() << "\n| Obvod: " << this->Obvod() << endl;
}

void Kruh::Identifikace()
{
    cout << "Kruh" << endl;
}

// Metody třídy Platno
Platno::Platno(int kap)
{
    this->pocetObjektu = 0;
    this->kapacita = kap;
    this->objekty = new Shape*[this->kapacita];
}

Platno::~Platno()
{
    for (int i = 0; i < this->pocetObjektu; i++)
    {
        delete this->objekty[i];
    }
    delete[] this->objekty;
}

Shape* Platno::CreateObdelnik(string n, double a, double b)
{
    if(this->pocetObjektu >= this->kapacita)
    {
        return nullptr;
    }
    
    Obdelnik* o = new Obdelnik(n, a, b);
    this->objekty[this->pocetObjektu++] = o;
    return o;
}

Shape* Platno::CreateKruh(string n, double r)
{
    if(this->pocetObjektu >= this->kapacita)
    {
        return nullptr;
    }
    
    Kruh* k = new Kruh(n, r);
    this->objekty[this->pocetObjektu++] = k;
    return k;
}

void Platno::VypisVsechnyObjekty()
{
    for (int i = 0; i < this->pocetObjektu; i++)
    {
        this->objekty[i]->VypisInfo(); 
    }
}

int main()
{
    Platno* mojePlatno = new Platno(5);

    mojePlatno->CreateObdelnik("Nejaky obdelnik", 2.0, 4.0);
    mojePlatno->CreateKruh("Nejaky kruh", 1.5);

    cout << "--- polymorfni struktury ---" << endl;
    mojePlatno->VypisVsechnyObjekty();

    cout << "\n--- Virtualni prekryti vs Obycejne prekryti ---" << endl;
    
    Shape* testovaciObjekt = new Kruh("Testovaci Kruh", 5.0);

    // virtuální metoda (pozdní vazba)
    // Program se za běhu podívá do tabulky virtuálních metod (VMT) a zjistí, že má volat Kruh::Obsah()
    cout << "virtualni Obsah(): " << testovaciObjekt->Obsah() << endl;

    // obyčejné překrytí / zastínění (statická vazba)
    // metoda není virtuální. Kompilátor se rozhoduje striktně podle typu ukazatele (Shape*), Zavolá se kód předka, kód potomka je ignorován.

    cout << "nevirtualni Identifikace(): "; 
    testovaciObjekt->Identifikace(); // Vypíše se chyba

    delete testovaciObjekt;
    delete mojePlatno;

    getchar();
    return 0;
}