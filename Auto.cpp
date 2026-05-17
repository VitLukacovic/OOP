#include <iostream>
#include <string>

using namespace std;

class GeometrickyObjekt
{
    protected:
        string nazev;

    public:
        GeometrickyObjekt(string n);
        ~GeometrickyObjekt();

        string GetNazev();
        double Obsah();
        double Obvod();
};

class Obdelnik : public GeometrickyObjekt
{
    private:
        double stranaA;
        double stranaB;

    public:
        Obdelnik(double a, double b);
        
        double Obsah();
        double Obvod();
};

class Kruh : public GeometrickyObjekt
{
    private:
        static double pi;
        double polomer;

    public:
        static double GetPi();
        Kruh(double r);

        double Obsah();
        double Obvod();
};

double Kruh::pi = 3.14;
//Metody třídy GeometrickyObjekt
GeometrickyObjekt::GeometrickyObjekt(string n)
{
    this->nazev = n;
}

GeometrickyObjekt::~GeometrickyObjekt()
{

}

string GeometrickyObjekt::GetNazev()
{
    return this->nazev;
}

double GeometrickyObjekt::Obsah()
{
    return 0.0;
}

double GeometrickyObjekt::Obvod()
{
    return 0.0;
}

// Metody třídy Obdelnik
Obdelnik::Obdelnik(double a, double b) : GeometrickyObjekt("Obdelnik")
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

//Metody třídy Kruh
Kruh::Kruh(double r) : GeometrickyObjekt("Kruh")
{
    this->polomer = r;
}

double Kruh::GetPi()
{
    return Kruh::pi;
}

double Kruh::Obsah()
{
    return Kruh::pi * this->polomer * this->polomer;
}

double Kruh::Obvod()
{
    return 2 * Kruh::pi * this->polomer;
}

int main()
{
    Obdelnik *o = new Obdelnik(4.0, 5.0);
    Kruh *k = new Kruh(3.0);

    cout << o->GetNazev() << " -> Obsah: " << o->Obsah() << ", Obvod: " << o->Obvod() << endl;
    cout << k->GetNazev() << " (vyuziva pi = " << Kruh::GetPi() << ") -> Obsah: " << k->Obsah() << ", Obvod: " << k->Obvod() << endl;


    cout << "\n--- Vyuziti substitucniho principu ---" << endl;
    
    GeometrickyObjekt* objekt1 = o; 
    GeometrickyObjekt* objekt2 = k;

    cout << objekt1->GetNazev() << " pres ukazatel -> Obsah: " << objekt1->Obsah() << ", Obvod: " << objekt1->Obvod() << endl;
    cout << objekt2->GetNazev() << " pres ukazatel -> Obsah: " << objekt2->Obsah() << ", Obvod: " << objekt2->Obvod() << endl;

    getchar();
    return 0;
}