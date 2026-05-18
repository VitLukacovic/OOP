#include <iostream>
#include <string>

using namespace std;

// 
// abstraktní třída - nemá žádné proměnné, všechny metody (kromě destruktoru) jsou čistě virtuální (= 0)
class GeometrickyObjekt
{
    public:
        virtual ~GeometrickyObjekt() {}

        virtual double Obsah() = 0;
        virtual double Obvod() = 0;
        virtual void VypisInfo() = 0;
};

// 2. abstraktní třída - dědí z GeometrickyObjekt
// - Přidává data (name) a částečně implementuje chování
// - stále je abstraktní, protože neimplementuje Obsah() a Obvod()
class Shape : public GeometrickyObjekt
{
    private:
        string name;

    public:
        Shape(string n);
        virtual ~Shape();

        string GetName();
        void Identifikace(); // nevirtuální metoda
        
        // Implementujeme pouze jednu čistě virtuální metodu z předka
        void VypisInfo() override; 
};

class Obdelnik : public Shape
{
    private:
        double stranaA;
        double stranaB;

    public:
        Obdelnik(string n, double a, double b);
        
        // implementace chybějících čistě virtuálních metod
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


// --- metody třídy Shape ---
Shape::Shape(string n)
{
    this->name = n;
}

Shape::~Shape() {}

string Shape::GetName()
{
    return this->name;
}

void Shape::VypisInfo()
{
    cout << "Objekt: " << this->name << " ";
}

void Shape::Identifikace()
{
    cout << "obecny tvar" << endl;
}

// metody Obsah() a Obvod() pro Shape se už neimplemetnují


// --- Metody třídy Obdelnik ---
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
    Shape::VypisInfo(); //  částečná implementace z abstraktní třídy
    cout << " - Obdelnik\n| Obsah: " << this->Obsah() << "\n| Obvod: " << this->Obvod() << endl;
}

void Obdelnik::Identifikace()
{
    cout << "Obdelnik" << endl;
}

// --- metody třídy Kruh ---
Kruh::Kruh(string n, double r) : Shape(n)
{
    this->polomer = r;
}

double Kruh::Obsah()
{
    return Kruh::pi * this->polomer * this->polomer; // použití statické proměnné
}

double Kruh::Obvod()
{
    return 2 * Kruh::pi * this->polomer;
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

// --- metody třídy Platno ---
Platno::Platno(int kap)
{
    this->pocetObjektu = 0;
    this->kapacita = kap;
    this->objekty = new Shape*[this->kapacita];
}

Platno::~Platno()
{
    for(int i = 0; i < this->pocetObjektu; i++)
    {
        delete this->objekty[i];
    }
    delete[] this->objekty;
}

Shape* Platno::CreateObdelnik(string n, double a, double b)
{
    if(this->pocetObjektu >= this->kapacita) return nullptr;
    
    Obdelnik* o = new Obdelnik(n, a, b);
    this->objekty[this->pocetObjektu++] = o;
    return o;
}

Shape* Platno::CreateKruh(string n, double r)
{
    if(this->pocetObjektu >= this->kapacita) return nullptr;
    
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
    
    // třída Shape je abstraktní, ale můžeme vytvářet ukazatele jejího typu
    Shape* testovaciObjekt = new Kruh("Testovaci Kruh", 5.0);

    // virtuální metoda (pozdní vazba)
    cout << "virtualni Obsah(): " << testovaciObjekt->Obsah() << endl;

    // obyčejné překrytí / zastínění (statická vazba)
    cout << "nevirtualni Identifikace(): "; 
    testovaciObjekt->Identifikace(); // vypíše se chyba (obecný tvar místo Kruh)

    // pokus o vytvoření instance abstraktní třídy by selhal při kompilaci - Shape* s = new Shape("Tvar")

    delete testovaciObjekt;
    delete mojePlatno;

    getchar();
    return 0;
}