#include <iostream>
#include <string>

using namespace std;

class Auto
{
    private:
        string znacka;
        string model;
        int rokVyroby;

    public:
        Auto(string z, string m, int r);
        virtual ~Auto(); // Virtuální kvůli polymorfismu

        void UjedVzdalenost(double km);
        virtual void VypisInfo();

        string GetZnacka();
        string GetModel();
};

class OsobniAuto : public Auto
{
    private:
        int pocetMist; 

    public:
        OsobniAuto(string z, string m, int r, int mista);

        void VypisInfo();
};

class NakladniAuto : public Auto
{
    private:
        double maxNosnost;     
        double aktualniNaklad; 

    public:
        NakladniAuto(string z, string m, int r, double nosnost);

        bool NalozNaklad(double tuny);
        void SlozNaklad(double tuny);
        void VypisInfo();
};

Auto::Auto(string z, string m, int r)
{
    this->znacka = z;
    this->model = m;
    this->rokVyroby = r;
}

Auto::~Auto()
{

}

void Auto::VypisInfo()
{
    cout << "Vozidlo: " << this->znacka << " " << this->model << " (" << this->rokVyroby << ")" << endl;
}

string Auto::GetZnacka()
{
    return this->znacka;
}

string Auto::GetModel()
{
    return this->model;
}

// Metody třídy OsobniAuto
OsobniAuto::OsobniAuto(string z, string m, int r, int mista) : Auto(z, m, r)
{
    this->pocetMist = mista;
}

void OsobniAuto::VypisInfo()
{
    Auto::VypisInfo(); // Volání metody předka
    cout << " | Typ: Osobni, Pocet mist: " << this->pocetMist << "\n" << endl;
}


// Metody třídy NakladniAuto
NakladniAuto::NakladniAuto(string z, string m, int r, double nosnost) : Auto(z, m, r)
{
    this->maxNosnost = nosnost;
    this->aktualniNaklad = 0.0;
}

bool NakladniAuto::NalozNaklad(double tuny)
{
    if(this->aktualniNaklad + tuny <= this->maxNosnost)
    {
        this->aktualniNaklad += tuny;
        return true;
    }
    return false; 
}

void NakladniAuto::SlozNaklad(double tuny)
{
    this->aktualniNaklad = this->aktualniNaklad - tuny;
    cout << "Nakladni auto" << this->GetZnacka() << " vylozilo " << tuny << " tun" << endl;
}

void NakladniAuto::VypisInfo()
{
    Auto::VypisInfo(); // Volání metody předka
    cout << " | Typ: Nakladni, Nosnost: " << this->maxNosnost 
         << "\n | Aktualne nalozeno: " << this->aktualniNaklad << "\n" << endl;
}

int main()
{    
    OsobniAuto skodovka("Skoda", "Octavia", 2020, 5);
    NakladniAuto tatra("Tatra", "Phoenix", 2018, 15.5);

    tatra.NalozNaklad(10.0);

    cout << "\n--- Vypis informaci o vozidlech ---" << endl;
    skodovka.VypisInfo();
    tatra.VypisInfo();

    return 0;
}